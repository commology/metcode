/* 
 * File:   MessageITA2.cpp
 * Author: kavlar
 * 
 * Created on 20140821
 */

#include "MessageITA2.h"
#include "ITA.h"

MetCode::MessageITA2::MessageITA2()
{
    tagBEGIN = ITA2_BEGIN;
    tagEND = ITA2_END;
}

MetCode::MessageITA2::MessageITA2(const MessageITA2& orig)
{
}

MetCode::MessageITA2::~MessageITA2()
{
}

bool MetCode::MessageITA2::canIdentify(const std::string& headFragment) const throw ()
{
    if (headFragment.find(tagBEGIN) != std::string::npos)
       return true;
    else
       return false;
}

bool MetCode::MessageITA2::onHEAD(std::string& head) const throw ()
{
    //std::cerr << "MessageITA2 - onHEAD : " << head << std::endl;
    return true;
}

bool MetCode::MessageITA2::onHEAD(std::string& head, StreamWriter& streamwriter) throw ()
{
    return true;
}

bool MetCode::MessageITA2::onBEGIN(std::string& begin) const throw ()
{
    //std::cerr << "MessageITA2 - onBEGIN : " << begin << std::endl;
    return true;
}

bool MetCode::MessageITA2::onBEGIN(std::string& begin, StreamWriter& streamwriter) throw ()
{
    begin = tagBEGIN;
    return streamwriter.put(begin, o_group, o_line, false, true);
}

bool is_digits(const std::string& s);

bool MetCode::MessageITA2::onSEQ(std::string& seq) const throw ()
{
    if (seq.size() > 5)
    {
        log("W", i_line, i_group, "ITA2 sequence number is incorrect format; use rightmost 5 bytes.", seq);
        seq = seq.substr(seq.size() - 5);
    }

    if (seq.size() == 4)
    {
        log("W", i_line, i_group, "ITA2 sequence number is incorrect format; appending 0.", seq);
        seq += "0";
    }

    if (seq.size() == 2)
    {
        log("W", i_line, i_group, "ITA2 sequence number is incorrect format; appending 0.", seq);
        seq += "0";
    }

    if (seq.size() == 1)
    {
        log("W", i_line, i_group, "ITA2 sequence number is incorrect format; appending 00.", seq);
        seq += "00";
    }

    if (seq.size() == 0)
    {
        log("W", i_line, i_group, "ITA2 size+type is incorrect format; reset to 001", seq);
        seq = "001";
    }

    if (::is_digits(seq))
    {
    }
    else
    {
        if (seq.size() == 5)
        {
            log("W", i_line, i_group, "ITA2 size is incorrect format; reset to 00001.", seq);
            seq = "00001";
        }
        else
        {
            log("W", i_line, i_group, "ITA2 size is incorrect format; reset to 001.", seq);
            seq = "001";
        }
    }

    //std::cerr << "MessageITA2 - onSEQ : " << seq << std::endl;
    return true;
}

bool MetCode::MessageITA2::onSEQ(std::string& seq, StreamWriter& streamwriter) throw ()
{
    static unsigned long seqnum = 0;
    char buf[10];
    char fmt[10];
    
    seqnum++;
    if (seqnum > seqmax)
        seqnum = seqmin;
    
    ::sprintf(fmt, "%%0%dd\0", seqlength);
    ::sprintf(buf, fmt, seqnum);
    seq = buf;
    
    return streamwriter.put(seq, o_group, o_line, true, false);
}

bool MetCode::MessageITA2::onBulletin(std::string& bulletinFragment) const throw ()
{
    //std::cerr << "MessageITA2 - onBulletin : " << bulletinFragment << std::endl;
    return true;
}

bool MetCode::MessageITA2::onBulletin(std::string& bulletinFragment, StreamWriter& streamwriter) throw ()
{
    return true;
}

bool MetCode::MessageITA2::onEND(std::string& end) const throw ()
{
    //std::cerr << "MessageITA2 - onEND : " << end << std::endl;
    return true;
}

bool MetCode::MessageITA2::onEND(std::string& end, StreamWriter& streamwriter) throw ()
{
    bool result = false;
    end = tagEND;
    
    result = streamwriter.put("\n\n\n" + end, o_group, o_line, false, true, false, false);
    
    if (!result)
        return result;
    
    return streamwriter.flush(false);
}
