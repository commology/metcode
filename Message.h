/* 
 * File:   Message.h
 * Author: kavlar
 *
 * Created on 20140821
 */

#ifndef METCODE_MESSAGE_H
#define	METCODE_MESSAGE_H

#include <string>

#include "Processor.h"
#include "Bulletin.h"

namespace MetCode
{

class Message : public Processor<Message>
{
public:

    Message();

    virtual ~Message();

private:
    
    Message(const Message& orig);

private:
    
    static Bulletin* pbulletin;
    
protected:
    
    unsigned char seqlength;
    
    unsigned long seqmax;
    
    unsigned long seqmin;
    
public:
    
    /*
     * Name:        setBulletin
     * Function:    set bulletin instance
     * Returns:     false if already registered; true if otherwise
     * Parameters:  bulletin instance
     * Throws:      (none)
     */

    bool setBulletin(Bulletin& bulletin) throw ();
    
    /*
     * Name:        setSEQLength
     * Function:    set SEQ length
     * Returns:     false if specified SEQ length is not supported; true if otherwise
     * Parameters:  SEQ length [1, 9]; otherwise, use default length = 3;
     *              SEQ value in [1, 10 ^ length - 1]
     * Throws:      (none)
     */

    bool setSEQLength(const unsigned char length) throw ();
    
    /*
     * Name:        setSEQInitial
     * Function:    set SEQ initial value
     * Returns:     false if specified SEQ initial value is not supported; true if otherwise
     * Parameters:  SEQ initial value in [0, 10 ^ SEQlength - 1]
     * Throws:      (none)
     */

    bool setSEQInitial(const unsigned long initial) throw ();
    
public:
    
    bool main(StreamReader& streamreader, StreamWriter& streamwriter);
    
    bool process(std::string& data, StreamWriter& streamwriter);
    
protected:

    /*
     * Name:        onHEAD
     * Function:    dispatch to instance to process the head segment
     * Returns:     true if the instance can process; false if otherwise
     * Parameters:  head
     * Throws:      (none)
     */

    // when read/input
    virtual bool onHEAD(std::string& head) const throw ();

    // when write/output
    virtual bool onHEAD(std::string& head, StreamWriter& streamwriter) throw ();

    /*
     * Name:        onBEGIN
     * Function:    dispatch to instance to process BEGIN
     * Returns:     true if the instance can process; false if otherwise
     * Parameters:  BEGIN
     * Throws:      (none)
     */

    // when read/input
    virtual bool onBEGIN(std::string& begin) const throw ();

    // when write/output
    virtual bool onBEGIN(std::string& begin, StreamWriter& streamwriter) throw ();

    /*
     * Name:        onSEQ
     * Function:    dispatch to instance to process sequence number
     * Returns:     true if the instance can process; false if otherwise
     * Parameters:  sequence number
     * Throws:      (none)
     */

    // when read/input
    virtual bool onSEQ(std::string& seq) const throw ();

    // when write/output
    virtual bool onSEQ(std::string& seq, StreamWriter& streamwriter) throw ();

    /*
     * Name:        onBulletin
     * Function:    dispatch to instance to process the bulletin fragment
     * Returns:     true if the instance can process; false if otherwise
     * Parameters:  bulletin fragment
     * Throws:      (none)
     */

    // when read/input
    virtual bool onBulletin(std::string& bulletinFragment) const throw ();

    // when write/output
    virtual bool onBulletin(std::string& bulletinFragment, StreamWriter& streamwriter) throw ();

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

protected:

    std::string tagBEGIN;

    std::string tagEND;

private:

    enum MESSAGE_STATE
    {
        UNKNOWN     = 0,
        ASSIGNED    = 1,
        BEGIN       = 2,
        SEQ         = 3,
        BULLETIN    = 4,
        END         = 5,
        HALT        = 15
    } state;

};

};

#endif	/* METCODE_MESSAGE_H */

