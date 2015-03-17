/* 
 * File:   FMCodeFM12.cpp
 * Author: kavlar
 * 
 * Created on 201421
 */

#include "FMCodeFM12.h"

MetCode::FMCodeFM12::FMCodeFM12()
{
}

MetCode::FMCodeFM12::FMCodeFM12(const FMCodeFM12& orig)
{
}

MetCode::FMCodeFM12::~FMCodeFM12()
{
}

bool MetCode::FMCodeFM12::canIdentify(const std::string& headFragment) const throw ()
{
    // TODO: FM list
    if (headFragment.substr(0, 4) == "AAXX")
        return true;
    else
        return false;
}

bool is_digits(const std::string& s);

bool MetCode::FMCodeFM12::onMiMiMjMj(std::string& mimimjmj, bool& isNextGroupYYGG) const throw ()
{
    isNextGroupYYGG = false;
    std::cerr << "FMCodeFM12 - onMiMiMjMj : " << mimimjmj << std::endl;
    return true;
}

bool MetCode::FMCodeFM12::onMiMiMjMj(std::string& mimimjmj, StreamWriter& streamwriter) throw ()
{
    return streamwriter.put(mimimjmj, o_group, o_line, true, false);
}

bool MetCode::FMCodeFM12::onYYGG(std::string& yygg) const throw ()
{
    std::cerr << "FMCodeFM12 - onYYGG : " << yygg << std::endl;
    return true;
}

bool MetCode::FMCodeFM12::onYYGG(std::string& yygg, StreamWriter& streamwriter) throw ()
{
    return streamwriter.put(yygg, o_group, o_line, true, false);
}

bool MetCode::FMCodeFM12::onGroup(std::string& reportGroup) const throw ()
{
    std::cerr << "FMCodeFM12 - onGroup : " << reportGroup << std::endl;
    return true;
}

bool MetCode::FMCodeFM12::onGroup(std::string& reportGroup, StreamWriter& streamwriter) throw ()
{
    return streamwriter.put(reportGroup, o_group, o_line, true, false);
}

bool MetCode::FMCodeFM12::onHeadGroup(std::string& reportHeadGroup) const throw ()
{
    std::cerr << "FMCodeFM12 - onHeadGroup : " << reportHeadGroup << std::endl;
    return true;
}

bool MetCode::FMCodeFM12::onHeadGroup(std::string& reportHeadGroup, StreamWriter& streamwriter) throw ()
{
    return streamwriter.put(reportHeadGroup, o_group, o_line, false, true);
}

bool MetCode::FMCodeFM12::onEndGroup(std::string& reportEndGroup) const throw ()
{
    std::cerr << "FMCodeFM12 - onEndGroup : " << reportEndGroup << std::endl;
    return true;
}

bool MetCode::FMCodeFM12::onEndGroup(std::string& reportEndGroup, StreamWriter& streamwriter) throw ()
{
    return streamwriter.put(reportEndGroup, o_group, o_line, false, true);
}

bool MetCode::FMCodeFM12::onEND(std::string& end) const throw ()
{
    return true;
}

bool MetCode::FMCodeFM12::onEND(std::string& end, StreamWriter& streamwriter) throw ()
{
    return true;
}
