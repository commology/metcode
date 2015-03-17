/* 
 * File:   FMCodeAny.cpp
 * Author: kavlar
 * 
 * Created on 20140821
 */

#include "FMCodeAny.h"

MetCode::FMCodeAny::FMCodeAny()
{
}

MetCode::FMCodeAny::FMCodeAny(const FMCodeAny& orig)
{
}

MetCode::FMCodeAny::~FMCodeAny()
{
}

bool MetCode::FMCodeAny::canIdentify(const std::string& headFragment) const throw ()
{
    // TODO: FM list
    return true;
}

bool MetCode::FMCodeAny::onMiMiMjMj(std::string& mimimjmj, bool& isNextGroupYYGG) const throw ()
{
    isNextGroupYYGG = false;
    if (mimimjmj == "AAXX")
        isNextGroupYYGG = true;
    if (mimimjmj == "CLIMAT")
        isNextGroupYYGG = true;
    //std::cerr << "FMCodeAny - onMiMiMjMj : " << mimimjmj << std::endl;
    return true;
}

bool MetCode::FMCodeAny::onMiMiMjMj(std::string& mimimjmj, StreamWriter& streamwriter) throw ()
{
    return streamwriter.put(mimimjmj, o_group, o_line, false, true);
}

bool MetCode::FMCodeAny::onYYGG(std::string& yygg) const throw ()
{
    //std::cerr << "FMCodeAny - onYYGG : " << yygg << std::endl;
    return true;
}

bool MetCode::FMCodeAny::onYYGG(std::string& yygg, StreamWriter& streamwriter) throw ()
{
    return streamwriter.put(yygg, o_group, o_line, true, false);
}

bool MetCode::FMCodeAny::onGroup(std::string& reportGroup) const throw ()
{
    //std::cerr << "FMCodeAny - onGroup : " << reportGroup << std::endl;
    return true;
}

bool MetCode::FMCodeAny::onGroup(std::string& reportGroup, StreamWriter& streamwriter) throw ()
{
    return streamwriter.put(reportGroup, o_group, o_line, true, false);
}

bool MetCode::FMCodeAny::onHeadGroup(std::string& reportHeadGroup) const throw ()
{
    //std::cerr << "FMCodeAny - onHeadGroup : " << reportHeadGroup << std::endl;
    return true;
}

bool MetCode::FMCodeAny::onHeadGroup(std::string& reportHeadGroup, StreamWriter& streamwriter) throw ()
{
    return streamwriter.put(reportHeadGroup, o_group, o_line, false, true);
}

bool MetCode::FMCodeAny::onEndGroup(std::string& reportEndGroup) const throw ()
{
    //std::cerr << "FMCodeAny - onEndGroup : " << reportEndGroup << std::endl;
    return true;
}

bool MetCode::FMCodeAny::onEndGroup(std::string& reportEndGroup, StreamWriter& streamwriter) throw ()
{
    return streamwriter.put(reportEndGroup, o_group, o_line, true, false);
}

bool MetCode::FMCodeAny::onEND(std::string& end) const throw ()
{
    return true;
}

bool MetCode::FMCodeAny::onEND(std::string& end, StreamWriter& streamwriter) throw ()
{
    return streamwriter.put(end, o_group, o_line, false, true, false, false);
}
