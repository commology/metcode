/* 
 * File:   FMCode.h
 * Author: kavlar
 *
 * Created on 20140821
 */

#ifndef METCODE_FMCODE_H
#define	METCODE_FMCODE_H

#include "Processor.h"

namespace MetCode
{

class FMCode : public Processor<FMCode>
{
public:

    FMCode();

    virtual ~FMCode();

private:

    FMCode(const FMCode& orig);

public:
    
    bool process(std::string& data, StreamWriter& streamwriter);
    
protected:

    /*
     * Name:        onMiMiMjMj
     * Function:    dispatch to instance to process MiMiMjMj
     * Returns:     true if the instance can process; false if otherwise
     * Parameters:  MIMIMJMJ
     *              is next group YYGG
     * Throws:      (none)
     */

    // when read/input
    virtual bool onMiMiMjMj(std::string& mimimjmj, bool& isNextGroupYYGG) const throw ();

    // when write/output
    virtual bool onMiMiMjMj(std::string& mimimjmj, StreamWriter& streamwriter) throw ();

    /*
     * Name:        onYYGG
     * Function:    dispatch to instance to process YYGG
     * Returns:     true if the instance can process; false if otherwise
     * Parameters:  YYGG
     * Throws:      (none)
     */

    // when read/input
    virtual bool onYYGG(std::string& yygg) const throw ();

    // when write/output
    virtual bool onYYGG(std::string& yygg, StreamWriter& streamwriter) throw ();

    /*
     * Name:        onGroup
     * Function:    dispatch to instance to process the report group
     * Returns:     true if the instance can process; false if otherwise
     * Parameters:  report group
     * Throws:      (none)
     */

    // when read/input
    virtual bool onGroup(std::string& reportGroup) const throw ();

    // when write/output
    virtual bool onGroup(std::string& reportGroup, StreamWriter& streamwriter) throw ();

    /*
     * Name:        onHeadGroup
     * Function:    dispatch to instance to process the report head group
     * Returns:     true if the instance can process; false if otherwise
     * Parameters:  report head group
     * Throws:      (none)
     */

    // when read/input
    virtual bool onHeadGroup(std::string& reportHeadGroup) const throw ();

    // when write/output
    virtual bool onHeadGroup(std::string& reportHeadGroup, StreamWriter& streamwriter) throw ();

    /*
     * Name:        onEndGroup
     * Function:    dispatch to instance to process the report end group
     * Returns:     true if the instance can process; false if otherwise
     * Parameters:  report end group
     * Throws:      (none)
     */

    // when read/input
    virtual bool onEndGroup(std::string& reportEndGroup) const throw ();

    // when write/output
    virtual bool onEndGroup(std::string& reportEndGroup, StreamWriter& streamwriter) throw ();

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

    enum FMCODE_STATE
    {
        UNKNOWN     = 0,
        ASSIGNED    = 1,
        MIMIMJMJ    = 2,
        YYGG        = 3,
        GROUP_HEAD  = 4,
        GROUP       = 5,
        END         = 6,
        HALT        = 15
    } state;

};

};

#endif	/* METCODE_FMCODE_H */

