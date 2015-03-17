/* 
 * File:   Bulletin.h
 * Author: kavlar
 *
 * Created on 20140821
 */

#ifndef METCODE_BULLETIN_H
#define	METCODE_BULLETIN_H

#include <string>

#include "Processor.h"
#include "FMCode.h"

namespace MetCode
{

class Bulletin : public Processor<Bulletin>
{
public:
    
    Bulletin();
    
    virtual ~Bulletin();
    
private:
    
    Bulletin(const Bulletin& orig);

private:
    
    static FMCode* pfmcode;
    
public:
    
    /*
     * Name:        setFMCode
     * Function:    set fmcode instance
     * Returns:     false if already registered; true if otherwise
     * Parameters:  fmcode instance
     * Throws:      (none)
     */

    bool setFMCode(FMCode& fmcode) throw ();
    
public:
    
    bool process(std::string& data, StreamWriter& streamwriter);
    
protected:

    /*
     * Name:        onTTAAii
     * Function:    dispatch to instance to process TTAAii
     * Returns:     true if the instance can process; false if otherwise
     * Parameters:  head
     * Throws:      (none)
     */

    // when read/input
    virtual bool onTTAAii(std::string& TTAAii) const throw ();

    // when write/output
    virtual bool onTTAAii(std::string& TTAAii, StreamWriter& streamwriter) throw ();

    /*
     * Name:        onCCCC
     * Function:    dispatch to instance to process CCCC
     * Returns:     true if the instance can process; false if otherwise
     * Parameters:  CCCC
     * Throws:      (none)
     */

    // when read/input
    virtual bool onCCCC(std::string& CCCC) const throw ();

    // when write/output
    virtual bool onCCCC(std::string& CCCC, StreamWriter& streamwriter) throw ();

    /*
     * Name:        onYYGGgg
     * Function:    dispatch to instance to process YYGGgg
     * Returns:     true if the instance can process; false if otherwise
     * Parameters:  YYGGgg
     * Throws:      (none)
     */

    // when read/input
    virtual bool onYYGGgg(std::string& YYGGgg) const throw ();

    // when write/output
    virtual bool onYYGGgg(std::string& YYGGgg, StreamWriter& streamwriter) throw ();

    /*
     * Name:        onBBB
     * Function:    dispatch to instance to process BBB
     * Returns:     true if the instance can process; false if otherwise
     * Parameters:  BBB
     * Throws:      (none)
     */

    // when read/input
    virtual bool onBBB(std::string& BBB) const throw ();

    // when write/output
    virtual bool onBBB(std::string& BBB, StreamWriter& streamwriter) throw ();

    /*
     * Name:        onFMCode
     * Function:    dispatch to instance to process the FM code
     * Returns:     true if the instance can process; false if otherwise
     * Parameters:  FM code
     * Throws:      (none)
     */

    // when read/input
    virtual bool onFMCode(std::string& group) const throw ();

    // when write/output
    virtual bool onFMCode(std::string& group, StreamWriter& streamwriter) throw ();

    /*
     * Name:        onEND
     * Function:    dispatch to instance to process the END
     * Returns:     true if the instance can process; false if otherwise
     * Parameters:  END
     * Throws:      (none)
     */

    // when read/input
    virtual bool onEND(std::string& end) const throw ();

    // when write/output
    virtual bool onEND(std::string& end, StreamWriter& streamwriter) throw ();

private:

    enum BULLETIN_STATE
    {
        UNKNOWN     = 0,
        ASSIGNED    = 1,
        AHL_TTAAii  = 2,
        AHL_CCCC    = 3,
        AHL_YYGGgg  = 4,
        AHL_BBB     = 5,
        FMCODE      = 6,
        END         = 7,
        HALT        = 15
    } state;

};

};

#endif	/* METCODE_BULLETIN_H */

