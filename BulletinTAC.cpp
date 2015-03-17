/* 
 * File:   BulletinTAC.cpp
 * Author: kavlar
 * 
 * Created on 20140821
 */

#include "BulletinTAC.h"

MetCode::BulletinTAC::BulletinTAC()
{
}

MetCode::BulletinTAC::BulletinTAC(const BulletinTAC& orig)
{
}

MetCode::BulletinTAC::~BulletinTAC()
{
}

bool MetCode::BulletinTAC::canIdentify(const std::string& headFragment) const throw ()
{
    // TODO: AHL list
    return true;
}

bool is_digits(const std::string& s);

bool MetCode::BulletinTAC::onTTAAii(std::string& TTAAii) const throw ()
{
    /*
    if (seq.size() > 5)
    {
        log("W", i_line, i_group, "ITA5 sequence number is incorrect format; use rightmost 5 bytes.", head);
        seq = seq.substr(seq.size() - 5);
    }*/

    //std::cerr << "BulletinTAC - onTTAAii : " << TTAAii << std::endl;
    return true;
}

bool MetCode::BulletinTAC::onTTAAii(std::string& TTAAii, StreamWriter& streamwriter) throw ()
{
    return streamwriter.put(TTAAii, o_group, o_line, false, true);
}

bool MetCode::BulletinTAC::onCCCC(std::string& CCCC) const throw ()
{
    //std::cerr << "BulletinTAC - onCCCC : " << CCCC << std::endl;
    return true;
}

bool MetCode::BulletinTAC::onCCCC(std::string& CCCC, StreamWriter& streamwriter) throw ()
{
    return streamwriter.put(CCCC, o_group, o_line, true, false);
}

bool MetCode::BulletinTAC::onYYGGgg(std::string& YYGGgg) const throw ()
{
    //std::cerr << "BulletinTAC - onYYGGgg : " << YYGGgg << std::endl;
    return true;
}

bool MetCode::BulletinTAC::onYYGGgg(std::string& YYGGgg, StreamWriter& streamwriter) throw ()
{
    return streamwriter.put(YYGGgg, o_group, o_line, true, false);
}

bool MetCode::BulletinTAC::onBBB(std::string& BBB) const throw ()
{
    //std::cerr << "BulletinTAC - onBBB : " << BBB << std::endl;
    return true;
}

bool MetCode::BulletinTAC::onBBB(std::string& BBB, StreamWriter& streamwriter) throw ()
{
    return streamwriter.put(BBB, o_group, o_line, true, false);
}

bool MetCode::BulletinTAC::onFMCode(std::string& group) const throw ()
{
    //std::cerr << "BulletinTAC - onFMCode : " << group << std::endl;
    return true;
}

bool MetCode::BulletinTAC::onFMCode(std::string& group, StreamWriter& streamwriter) throw ()
{
    return true;
}

bool MetCode::BulletinTAC::onEND(std::string& end) const throw ()
{
    //std::cerr << "BulletinTAC - onEnd : " << end << std::endl;
    return true;
}

bool MetCode::BulletinTAC::onEND(std::string& end, StreamWriter& streamwriter) throw ()
{
    return true;
}
