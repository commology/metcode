/* 
 * File:   FMCodeFM12.h
 * Author: kavlar
 *
 * Created on 20140821
 */

#ifndef METCODE_FMCODEFM12_H
#define	METCODE_FMCODEFM12_H

#include "FMCode.h"

namespace MetCode
{

class FMCodeFM12 : public FMCode
{
public:
    FMCodeFM12();

    virtual ~FMCodeFM12();

private:

    FMCodeFM12(const FMCodeFM12& orig);

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

#endif	/* METCODE_FMCODEFM12_H */

