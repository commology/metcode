/* 
 * File:   MessageITA5.cpp
 * Author: kavlar
 * 
 * Created on 20140821
 */

#include "MessageITA5.h"
#include "ITA.h"

MetCode::MessageITA5::MessageITA5()
{
    tagBEGIN = std::string(1, SOH);
    tagEND = std::string(1, ETX);
}

MetCode::MessageITA5::MessageITA5(const MessageITA5& orig)
{
}

MetCode::MessageITA5::~MessageITA5()
{
}

bool MetCode::MessageITA5::canIdentify(const std::string& headFragment) const throw ()
{
    if (headFragment.find(tagBEGIN) != std::string::npos)
        return true;
    else
        return false;
}

bool is_digits(const std::string& s);

bool MetCode::MessageITA5::onHEAD(std::string& head) const throw ()
{
    if (head.size() > 8 + 2)
    {
        log("W", i_line, i_group, "ITA5 size+type is incorrect format; use rightmost 10 bytes.", head);
        head = head.substr(head.size() - 10);
    }

    if (head.size() < 8)
    {
        log("W", i_line, i_group, "ITA5 size+type is incorrect format; reset to 0000000000", head);
        head = "0000000000";
    }

    if (head.size() == 8)
    {
        log("W", i_line, i_group, "ITA5 size+type is incorrect format; appending 00.", head);
        head += "00";
    }

    if (head.size() == 9)
    {
        log("W", i_line, i_group, "ITA5 size+type is incorrect format; appending 0.", head);
        head += "0";
    }

    std::string size = head.substr(0, 8);
    std::string type = head.substr(8, 2);

    if (::is_digits(size))
    {
    }
    else
    {
        log("W", i_line, i_group, "ITA5 size is incorrect format; reset to 00000000.", size);
        size = "00000000";
    }

    if (::is_digits(type))
    {
    }
    else
    {
        log("W", i_line, i_group, "ITA5 size is incorrect format; reset to 00000000.", type);
        type = "00";
    }

    head = size + type;

    //std::cerr << "MessageITA5 - onHEAD : " << head << std::endl;
    return true;
}

bool MetCode::MessageITA5::onHEAD(std::string& head, StreamWriter& streamwriter) throw ()
{
    // delayed to StreamWriter::flush
    return true;
}

bool MetCode::MessageITA5::onBEGIN(std::string& begin) const throw ()
{
    //std::cerr << "MessageITA5 - onBEGIN : " << begin << std::endl;
    return true;
}

bool MetCode::MessageITA5::onBEGIN(std::string& begin, StreamWriter& streamwriter) throw ()
{
    begin = tagBEGIN;
    return streamwriter.put(begin, o_group, o_line, false, false);
}

bool MetCode::MessageITA5::onSEQ(std::string& seq) const throw ()
{
    if (seq.size() > 5)
    {
        log("W", i_line, i_group, "ITA5 sequence number is incorrect format; use rightmost 5 bytes.", seq);
        seq = seq.substr(seq.size() - 5);
    }

    if (seq.size() == 4)
    {
        log("W", i_line, i_group, "ITA5 sequence number is incorrect format; appending 0.", seq);
        seq += "0";
    }

    if (seq.size() == 2)
    {
        log("W", i_line, i_group, "ITA5 sequence number is incorrect format; appending 0.", seq);
        seq += "0";
    }

    if (seq.size() == 1)
    {
        log("W", i_line, i_group, "ITA5 sequence number is incorrect format; appending 00.", seq);
        seq += "00";
    }

    if (seq.size() == 0)
    {
        log("W", i_line, i_group, "ITA5 size+type is incorrect format; reset to 001", seq);
        seq = "001";
    }

    if (::is_digits(seq))
    {
    }
    else
    {
        if (seq.size() == 5)
        {
            log("W", i_line, i_group, "ITA5 size is incorrect format; reset to 00001.", seq);
            seq = "00001";
        }
        else
        {
            log("W", i_line, i_group, "ITA5 size is incorrect format; reset to 001.", seq);
            seq = "001";
        }
    }

    //std::cerr << "MessageITA5 - onSEQ : " << seq << std::endl;
    return true;
}

bool MetCode::MessageITA5::onSEQ(std::string& seq, StreamWriter& streamwriter) throw ()
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

    return streamwriter.put(seq, o_group, o_line, false, true);
}

bool MetCode::MessageITA5::onBulletin(std::string& bulletinFragment) const throw ()
{
    //std::cerr << "MessageITA5 - onBulletin : " << bulletinFragment << std::endl;
    return true;
}

bool MetCode::MessageITA5::onBulletin(std::string& bulletinFragment, StreamWriter& streamwriter) throw ()
{
    return true;
}

bool MetCode::MessageITA5::onEND(std::string& end) const throw ()
{
    //std::cerr << "MessageITA5 - onEND : " << end << std::endl;
    return true;
}

bool MetCode::MessageITA5::onEND(std::string& end, StreamWriter& streamwriter) throw ()
{
    bool result = false;
    end = tagEND;

    result = streamwriter.put(end, o_group, o_line, false, false);

    if (!result)
        return result;

    return streamwriter.flush(true, "00");
}
