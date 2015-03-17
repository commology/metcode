/* 
 * File:   FMCodeAny.h
 * Author: kavlar
 *
 * Created on 20140821
 */

#ifndef METCODE_FMCODEANY_H
#define	METCODE_FMCODEANY_H

#include "FMCode.h"

namespace MetCode
{

class FMCodeAny : public FMCode
{
public:
    FMCodeAny();

    virtual ~FMCodeAny();

private:

    FMCodeAny(const FMCodeAny& orig);

protected:

    virtual bool canIdentify(const std::string& headFragment) const throw ();

    virtual bool onMiMiMjMj(std::string& mimimjmj, bool& isNextGroupYYGG) const throw ();

    virtual bool onMiMiMjMj(std::string& mimimjmj, StreamWriter& streamwriter) throw ();

    virtual bool onYYGG(std::string& yygg) const throw ();

    virtual bool onYYGG(std::string& yygg, StreamWriter& streamwriter) throw ();

    virtual bool onGroup(std::string& reportGroup) const throw ();

    virtual bool onGroup(std::string& reportGroup, StreamWriter& streamwriter) throw ();

    virtual bool onHeadGroup(std::string& reportHeadGroup) const throw ();

    virtual bool onHeadGroup(std::string& reportHeadGroup, StreamWriter& streamwriter) throw ();

    virtual bool onEndGroup(std::string& reportEndGroup) const throw ();

    virtual bool onEndGroup(std::string& reportEndGroup, StreamWriter& streamwriter) throw ();

    virtual bool onEND(std::string& end) const throw ();

    virtual bool onEND(std::string& end, StreamWriter& streamwriter) throw ();

};

};

#endif	/* METCODE_FMCODEANY_H */

