/* 
 * File:   Bulletin.cpp
 * Author: kavlar
 * 
 * Created on 20140821
 */

#include "Bulletin.h"

std::set<MetCode::Bulletin*> MetCode::Processor<MetCode::Bulletin>::setInstance;
MetCode::Bulletin* MetCode::Processor<MetCode::Bulletin>::workingInstance = NULL;
MetCode::Bulletin* MetCode::Processor<MetCode::Bulletin>::defaultInstance = NULL;
MetCode::Bulletin* MetCode::Processor<MetCode::Bulletin>::writerInstance = NULL;

MetCode::FMCode* MetCode::Bulletin::pfmcode = NULL;

MetCode::Bulletin::Bulletin()
{
    module = "Bulletin";
    registerInstance(this);
    workingInstance = NULL;
    defaultInstance = NULL;
    writerInstance = NULL;
    state = UNKNOWN;
}

MetCode::Bulletin::Bulletin(const Bulletin& orig)
{
}

MetCode::Bulletin::~Bulletin()
{
}

bool MetCode::Bulletin::setFMCode(FMCode& fmcode) throw ()
{
    if (pfmcode == &fmcode)
    {
        return false;
    }
    else
    {
        pfmcode = &fmcode;
        return true;
    }
}

bool MetCode::Bulletin::process(std::string& cache, StreamWriter& streamwriter)
{
    std::string group;

    unsigned long pos;

    // 0. (only) if in UNKNOWN state
    //    enquire instances and identify
    if (state == Bulletin::UNKNOWN)
    {
        if (this->enquireInstances(cache))
        {
            // working instance has been re/assigned
            state = Bulletin::ASSIGNED;
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
    //    check TTAAii
    if (state == Bulletin::ASSIGNED)
    {
        if (workingInstance == NULL || writerInstance == NULL)
        {
            log("F", i_line, i_group, "inconsistent state (ASSIGNED & NULL).", cache);
            // try to reset to UNKNOWN state
            state = Bulletin::UNKNOWN;
        }
        else
        {
            if (workingInstance->onTTAAii(cache))
            {
                // transit to TTAAii state
                state = Bulletin::AHL_TTAAii;

                if (writerInstance->onTTAAii(cache, streamwriter))
                {
                }
                else
                {
                    log("W", o_line, o_group, "TTAAii text ignored by target format.", group);
                }
            }
            else
            {
                log("W", i_line, i_group, "un-expected TTAAii text skipped.", group);
            }
        }

        cache.clear();

        return true;
    }

    // 2. (only) if in TTAAii state
    //    check CCCC
    if (state == Bulletin::AHL_TTAAii)
    {
        if (workingInstance == NULL || writerInstance == NULL)
        {
            log("F", i_line, i_group, "inconsistent state (AHL_TTAAii & NULL).", cache);
            // try to reset to UNKNOWN state
            state = Bulletin::UNKNOWN;
        }
        else
        {
            if (workingInstance->onCCCC(cache))
            {
                // transit to CCCC state
                state = Bulletin::AHL_CCCC;

                if (writerInstance->onCCCC(cache, streamwriter))
                {
                }
                else
                {
                    log("W", o_line, o_group, "CCCC text ignored by target format.", group);
                }
            }
            else
            {
                log("W", i_line, i_group, "un-expected CCCC text skipped.", group);
            }
        }

        cache.clear();

        return true;
    }

    // 3. (only) if in CCCC state
    //    check YYGGgg
    if (state == Bulletin::AHL_CCCC)
    {
        if (workingInstance == NULL || writerInstance == NULL)
        {
            log("F", i_line, i_group, "inconsistent state (AHL_CCCC & NULL).", cache);
            // try to reset to UNKNOWN state
            state = Bulletin::UNKNOWN;
        }
        else
        {
            if (workingInstance->onYYGGgg(cache))
            {
                // transit to YYGGgg state
                state = Bulletin::AHL_YYGGgg;

                if (writerInstance->onYYGGgg(cache, streamwriter))
                {
                }
                else
                {
                    log("W", o_line, o_group, "YYGGgg text ignored by target format.", group);
                }
            }
            else
            {
                log("W", i_line, i_group, "un-expected YYGGgg text skipped.", group);
            }
        }

        cache.clear();

        return true;
    }

    // 4. (only) if in YYGGgg state
    //    check BBB
    if (state == Bulletin::AHL_YYGGgg)
    {
        if (workingInstance == NULL || writerInstance == NULL)
        {
            log("F", i_line, i_group, "inconsistent state (AHL_YYGGgg & NULL).", cache);
            // try to reset to UNKNOWN state
            state = Bulletin::UNKNOWN;
        }
        else
        {
            if (cache.size() <= 3)
            {
                if (workingInstance->onBBB(cache))
                {
                    // transit to BBB state
                    state = Bulletin::AHL_BBB;

                    if (writerInstance->onBBB(cache, streamwriter))
                    {
                    }
                    else
                    {
                        log("W", o_line, o_group, "BBB text ignored by target format.", group);
                    }
                }
                else
                {
                    log("W", i_line, i_group, "un-expected BBB text skipped.", group);
                }

                cache.clear();
            }
            else
            {
                // transit to BBB state
                state = Bulletin::AHL_BBB;
            }
        }

        return true;
    }

    // 5. (only) if in BBB state
    if (state == Bulletin::AHL_BBB)
    {
        // transit to FMCODE state
        state = Bulletin::FMCODE;
        return true;
    }

    // 6. (only) if in FMCODE state
    if (state == Bulletin::FMCODE)
    {
        if (workingInstance == NULL || writerInstance == NULL)
        {
            log("F", i_line, i_group, "inconsistent state (FMCODE & NULL).", cache);
            // try to reset to UNKNOWN state
            state = Bulletin::UNKNOWN;
        }
        else if (cache.size() == 0)
        {
            if (workingInstance->onEND(cache))
            {
                // finished the current bulletin, transit to END state
                state = Bulletin::END;

                // inform END
                group = "";
                pfmcode->process(group, streamwriter);

                if (writerInstance->onEND(cache, streamwriter))
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
        }
        else
        {
            if (workingInstance->onFMCode(cache))
            {
                if (pfmcode)
                    pfmcode->process(cache, streamwriter);

                // loop transit to FMCODE state
                if (writerInstance->onFMCode(cache, streamwriter))
                {
                }
                else
                {
                    log("W", o_line, o_group, "FM code text ignored by target format.", group);
                }

                cache.clear();
            }
            else
            {
                log("W", i_line, i_group, "un-expected FM code text skipped.", group);

                cache.clear();
            }
        }

        return true;
    }

    // 5. (only) if in END state
    if (state == Bulletin::END)
    {
        if (workingInstance == NULL || writerInstance == NULL)
        {
            log("F", i_line, i_group, "inconsistent state (END & NULL).", cache);
            // try to reset to UNKNOWN state
            state = Bulletin::UNKNOWN;
        }
        else
        {
            c_object++;

            // transit to UNKNOWN state
            state = Bulletin::UNKNOWN;
            workingInstance = NULL;
        }

        return true;
    }

    return false;
}

bool MetCode::Bulletin::onTTAAii(std::string& TTAAii) const throw ()
{
    return false;
}

bool MetCode::Bulletin::onTTAAii(std::string& TTAAii, StreamWriter& streamwriter) throw ()
{
    return false;
}

bool MetCode::Bulletin::onCCCC(std::string& CCCC) const throw ()
{
    return false;
}

bool MetCode::Bulletin::onCCCC(std::string& CCCC, StreamWriter& streamwriter) throw ()
{
    return false;
}

bool MetCode::Bulletin::onYYGGgg(std::string& YYGGgg) const throw ()
{
    return false;
}

bool MetCode::Bulletin::onYYGGgg(std::string& YYGGgg, StreamWriter& streamwriter) throw ()
{
    return false;
}

bool MetCode::Bulletin::onBBB(std::string& BBB) const throw ()
{
    return false;
}

bool MetCode::Bulletin::onBBB(std::string& BBB, StreamWriter& streamwriter) throw ()
{
    return false;
}

bool MetCode::Bulletin::onFMCode(std::string& group) const throw ()
{
    return false;
}

bool MetCode::Bulletin::onFMCode(std::string& group, StreamWriter& streamwriter) throw ()
{
    return false;
}

bool MetCode::Bulletin::onEND(std::string& end) const throw ()
{
    return false;
}

bool MetCode::Bulletin::onEND(std::string& end, StreamWriter& streamwriter) throw ()
{
    return false;
}

