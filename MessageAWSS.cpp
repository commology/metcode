/* 
 * File:   MessageAWSS.cpp
 * Author: kavlar
 * 
 * Created on 20140914
 */

#include "MessageAWSS.h"
#include "ITA.h"

MetCode::MessageAWSS::MessageAWSS()
{
    tagBEGIN = std::string(AWSS_BEGIN);
    tagEND = std::string(AWSS_END);
}

MetCode::MessageAWSS::MessageAWSS(const MessageAWSS& orig)
{
}

MetCode::MessageAWSS::~MessageAWSS()
{
}

bool MetCode::MessageAWSS::canIdentify(const std::string& headFragment) const throw ()
{
    if (headFragment.find(tagBEGIN) != std::string::npos)
        return true;
    else
        return false;
}

bool is_digits(const std::string& s);

bool MetCode::MessageAWSS::onHEAD(std::string& head) const throw ()
{
    std::cerr << "MessageAWSS - onHEAD : " << head << std::endl;
    return true;
}

bool MetCode::MessageAWSS::onHEAD(std::string& head, StreamWriter& streamwriter) throw ()
{
    // delayed to StreamWriter::flush
    return true;
}

bool MetCode::MessageAWSS::onBEGIN(std::string& begin) const throw ()
{
    std::cerr << "MessageAWSS - onBEGIN : " << begin << std::endl;
    return true;
}

bool MetCode::MessageAWSS::onBEGIN(std::string& begin, StreamWriter& streamwriter) throw ()
{
    begin = tagBEGIN;
    return streamwriter.put(begin, o_group, o_line, false, true);
}

bool MetCode::MessageAWSS::onSEQ(std::string& seq) const throw ()
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

    //std::cerr << "MessageAWSS - onSEQ : " << seq << std::endl;
    return true;
}

bool MetCode::MessageAWSS::onSEQ(std::string& seq, StreamWriter& streamwriter) throw ()
{
    static unsigned long seqnum = 0;
    char buf[10];

    seqnum++;
    if (seqnum > 999)
        seqnum = 1;

    ::sprintf(buf, "%03d\0", seqnum);
    seq = buf;

    return streamwriter.put(seq, o_group, o_line, false, true);
}

bool MetCode::MessageAWSS::onBulletin(std::string& bulletinFragment) const throw ()
{
    return true;
}

bool MetCode::MessageAWSS::onBulletin(std::string& bulletinFragment, StreamWriter& streamwriter) throw ()
{
    return true;
}

bool MetCode::MessageAWSS::onEND(std::string& end) const throw ()
{
    return true;
}

bool MetCode::MessageAWSS::onEND(std::string& end, StreamWriter& streamwriter) throw ()
{
    bool result = false;
    end = tagEND;

    result = streamwriter.put(end, o_group, o_line, false, false);

    if (!result)
        return result;

    return streamwriter.flush(true, "00");
}
