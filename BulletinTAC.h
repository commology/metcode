/* 
 * File:   BulletinTAC.h
 * Author: kavlar
 *
 * Created on 20140821
 */

#ifndef METCODE_BULLETINTAC_H
#define	METCODE_BULLETINTAC_H

#include "Bulletin.h"

namespace MetCode
{

class BulletinTAC : public Bulletin
{
public:

    BulletinTAC();

    virtual ~BulletinTAC();

private:

    BulletinTAC(const BulletinTAC& orig);

protected:

    virtual bool canIdentify(const std::string& headFragment) const throw ();

    virtual bool onTTAAii(std::string& TTAAii) const throw ();

    virtual bool onTTAAii(std::string& TTAAii, StreamWriter& streamwriter) throw ();

    virtual bool onCCCC(std::string& CCCC) const throw ();

    virtual bool onCCCC(std::string& CCCC, StreamWriter& streamwriter) throw ();

    virtual bool onYYGGgg(std::string& YYGGgg) const throw ();

    virtual bool onYYGGgg(std::string& YYGGgg, StreamWriter& streamwriter) throw ();

    virtual bool onBBB(std::string& BBB) const throw ();

    virtual bool onBBB(std::string& BBB, StreamWriter& streamwriter) throw ();

    virtual bool onFMCode(std::string& group) const throw ();

    virtual bool onFMCode(std::string& group, StreamWriter& streamwriter) throw ();

    virtual bool onEND(std::string& end) const throw ();

    virtual bool onEND(std::string& end, StreamWriter& streamwriter) throw ();

};

};

#endif	/* METCODE_BULLETINTAC_H */

