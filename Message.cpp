/* 
 * File:   Message.cpp
 * Author: kavlar
 * 
 * Created on 20140821
 */

#include "Message.h"
#include <math.h>

std::set<MetCode::Message*> MetCode::Processor<MetCode::Message>::setInstance;
MetCode::Message* MetCode::Processor<MetCode::Message>::workingInstance = NULL;
MetCode::Message* MetCode::Processor<MetCode::Message>::defaultInstance = NULL;
MetCode::Message* MetCode::Processor<MetCode::Message>::writerInstance = NULL;

MetCode::Bulletin* MetCode::Message::pbulletin = NULL;

MetCode::Message::Message()
{
    seqlength = 3;
    seqmax = pow((float)10, seqlength) - 1;
    seqmin = 1;
    module = "Message";
    registerInstance(this);
    state = UNKNOWN;
}

MetCode::Message::Message(const Message& orig)
{
}

MetCode::Message::~Message()
{
}

bool MetCode::Message::setBulletin(Bulletin& bulletin) throw ()
{
    if (pbulletin == &bulletin)
    {
        return false;
    }
    else
    {
        pbulletin = &bulletin;
        return true;
    }
}

bool MetCode::Message::setSEQLength(const unsigned char length) throw ()
{
    if (length < 1 || length > 9)
    {
        return false;
    }
    else
    {
        seqlength = length;
        seqmax = pow((float)10, length) - 1;
        return true;
    }
}

bool MetCode::Message::setSEQInitial(const unsigned long initial) throw ()
{
    if (initial > seqmax)
    {
        seqmin = 1;
        return false;
    }
    else
    {
        seqmin = initial;
        return true;
    }
}

bool MetCode::Message::main(StreamReader& streamreader, StreamWriter& streamwriter)
{
    static bool running = false;

    // single entrance
    if (running)
    {
        log("F", 0, 0, "multiple entrance in main is not allowed.", "");
    }

    running = true;

    std::string cache;

    while (1)
    {
        if (cache.size() == 0)
        {
            if (streamreader.get(cache, i_group, i_line))
            {
                //std::cout << "READ (" << i_line << "," << i_group << ") : " << cache.size() << "[" << cache << "]" << std::endl;
            }
            else
            {
                break;
            }
        }
        else
        {
            //std::cout << "NEXT (" << i_line << "," << i_group << ") : " << cache << std::endl;
        }

        if (process(cache, streamwriter))
        {

        }
        else
        {
            log("E", i_line, i_group, "processing aborted.", cache);
            return false;
        }
    }

    running = false;

    return true;
}

bool MetCode::Message::process(std::string& cache, StreamWriter& streamwriter)
{
    std::string group;

    unsigned long pos;

    // 0. (only) if in UNKNOWN state
    //    enquire instances and identify
    if (state == Message::UNKNOWN)
    {
        if (this->enquireInstances(cache))
        {
            // working instance has been re/assigned
            state = Message::ASSIGNED;
            // drop to ASSIGNED section
        }
        else
        {
            if (cache.size() > 0)
            {
                log("W", i_line, i_group, "un-identified text skipped.", group);

                cache.clear(); // no instances could identify
            }

            return true;
        }
    }

    // 1. (only) if in ASSIGNED state
    //    search BEGIN
    if (state == Message::ASSIGNED)
    {
        if (workingInstance == NULL || writerInstance == NULL)
        {
            log("F", i_line, i_group, "inconsistent state (ASSIGNED & NULL).", cache);
            // try to reset to UNKNOWN state
            state = Message::UNKNOWN;
        }
        else
        {
            pos = cache.find(workingInstance->tagBEGIN);
            if (pos != std::string::npos)
            {
                // found

                // 1.1 extract HEAD and dispatch
                group = cache.substr(0, pos);

                if (workingInstance->onHEAD(group))
                {
                    if (writerInstance->onHEAD(group, streamwriter))
                    {
                    }
                    else
                    {
                        log("W", o_line, o_group, "HEAD text ignored by target format.", group);
                    }
                }
                else
                {
                    log("W", i_line, i_group, "un-expected HEAD text skipped.", group);
                }

                // 1.2 extract BEGIN and dispatch
                group = cache.substr(pos, workingInstance->tagBEGIN.size());
                if (workingInstance->onBEGIN(group))
                {
                    // transit to BEGIN state
                    state = Message::BEGIN;

                    if (writerInstance->onBEGIN(group, streamwriter))
                    {
                    }
                    else
                    {
                        log("W", o_line, o_group, "BEGIN text ignored by target format.", group);
                    }
                }
                else
                {
                    log("W", i_line, i_group, "un-expected BEGIN text skipped.", group);
                }

                // 1.3 the rest cache can be processed further
                cache = cache.substr(pos + workingInstance->tagBEGIN.size());
            }
            else
            {
                // no BEGIN, the whole cache can be assumed as head
                if (cache.size() > 0)
                {
                    if (workingInstance->onHEAD(cache))
                    {
                        if (writerInstance->onHEAD(cache, streamwriter))
                        {
                        }
                        else
                        {
                            log("W", o_line, o_group, "HEAD text ignored by target format.", group);
                        }
                    }
                    else
                    {
                        log("W", i_line, i_group, "un-expected HEAD text skipped.", group);
                    }
                }
                // however, the next text after this cache is still head
            }
        }

        return true;
    }

    // 2. (only) if in BEGIN state
    //    search BEGIN
    if (state == Message::BEGIN)
    {
        if (workingInstance == NULL || writerInstance == NULL)
        {
            log("F", i_line, i_group, "inconsistent state (BEGIN & NULL).", cache);
            // try to reset to UNKNOWN state
            state = Message::UNKNOWN;
        }
        else
        {
            if (workingInstance->onSEQ(cache))
            {
                // transit to SEQ state
                state = Message::SEQ;

                if (writerInstance->onSEQ(cache, streamwriter))
                {
                }
                else
                {
                    log("W", o_line, o_group, "SEQ text ignored by target format.", group);
                }
            }
            else
            {
                log("W", i_line, i_group, "un-expected HEAD text skipped.", group);
            }
        }

        cache.clear();

        return true;
    }

    // 3. (only) if in SEQ state
    if (state == Message::SEQ)
    {
        // transit to BULLETIN state
        state = Message::BULLETIN;
        // drop to BULLETIN
    }

    // 4. (only) if in BULLETIN state
    //    search END tag, and try to finish message
    if (state == Message::BULLETIN)
    {
        if (workingInstance == NULL || writerInstance == NULL)
        {
            log("F", i_line, i_group, "inconsistent state (BULLETIN & NULL).", cache);
            // try to reset to UNKNOWN state
            state = Message::UNKNOWN;
        }
        else
        {
            pos = cache.find(workingInstance->tagEND);
            if (pos != std::string::npos)
            {
                // found

                // 4.1 extract pre-END and dispatch
                group = cache.substr(0, pos);
                if (group.size() > 0)
                {
                    if (workingInstance->onBulletin(group))
                    {
                        if (pbulletin)
                            pbulletin->process(group, streamwriter);

                        if (writerInstance->onBulletin(group, streamwriter))
                        {
                        }
                        else
                        {
                            log("W", o_line, o_group, "Bulletin text ignored by target format.", group);
                        }
                    }
                    else
                    {
                        log("W", i_line, i_group, "un-expected bulletin text skipped.", group);
                    }
                }

                // 4.2 extract END and dispatch
                group = cache.substr(pos, workingInstance->tagEND.size());
                if (workingInstance->onEND(group))
                {
                    // finished the current message, transit to END state
                    state = Message::END;

                    // inform END
                    group = "";
                    pbulletin->process(group, streamwriter);

                    if (writerInstance->onEND(group, streamwriter))
                    {
                    }
                    else
                    {
                        log("W", o_line, o_group, "END text ignored by target format.", group);
                    }
                }
                else
                {
                    log("W", i_line, i_group, "un-expected END text skipped.", group);
                }

                // 4.3 the rest cache can be processed further
                cache = cache.substr(pos + workingInstance->tagEND.size());
            }
            else
            {
                // no END, the whole cache is still BULLETIN
                if (workingInstance->onBulletin(cache))
                {
                    if (pbulletin)
                        pbulletin->process(cache, streamwriter);

                    // loop transit to BULLETIN state
                    if (writerInstance->onBulletin(cache, streamwriter))
                    {
                    }
                    else
                    {
                        log("W", o_line, o_group, "Bulletin text ignored by target format.", group);
                    }
                }
                else
                {
                    log("W", i_line, i_group, "un-expected bulletin text skipped.", group);

                    cache.clear();
                }
            }
        }

        return true;
    }

    // 5. (only) if in END state
    if (state == Message::END)
    {
        if (workingInstance == NULL || writerInstance == NULL)
        {
            log("F", i_line, i_group, "inconsistent state (END & NULL).", cache);
            // try to reset to UNKNOWN state
            state = Message::UNKNOWN;
        }
        else
        {
            c_object++;

            // transit to UNKNOWN state
            state = UNKNOWN;
            workingInstance = NULL;
        }

        return true;
    }

    return false;
}

bool MetCode::Message::onHEAD(std::string& head) const throw ()
{
    return false;
}

bool MetCode::Message::onHEAD(std::string& head, StreamWriter& streamwriter) throw ()
{
    return false;
}

bool MetCode::Message::onBEGIN(std::string& begin) const throw ()
{
    return false;
}

bool MetCode::Message::onBEGIN(std::string& begin, StreamWriter& streamwriter) throw ()
{
    return false;
}

bool MetCode::Message::onSEQ(std::string& seq) const throw ()
{
    return false;
}

bool MetCode::Message::onSEQ(std::string& seq, StreamWriter& streamwriter) throw ()
{
    return false;
}

bool MetCode::Message::onBulletin(std::string& bulletinFragment) const throw ()
{
    return false;
}

bool MetCode::Message::onBulletin(std::string& bulletinFragment, StreamWriter& streamwriter) throw ()
{
    return false;
}

bool MetCode::Message::onEND(std::string& end) const throw ()
{
    return false;
}

bool MetCode::Message::onEND(std::string& end, StreamWriter& streamwriter) throw ()
{
    return false;
}
