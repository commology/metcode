/* 
 * File:   MessageITA5.h
 * Author: kavlar
 *
 * Created on 20140821
 */

#ifndef METCODE_MESSAGEITA5_H
#define	METCODE_MESSAGEITA5_H

#include "Message.h"

namespace MetCode
{

class MessageITA5 : public Message
{
public:

    MessageITA5();

    virtual ~MessageITA5();

private:
    
    MessageITA5(const MessageITA5& orig);

private:
    
    std::string message_type;
    
protected:

    virtual bool canIdentify(const std::string& headFragment) const throw ();

    virtual bool onHEAD(std::string& head) const throw ();

    virtual bool onHEAD(std::string& head, StreamWriter& streamwriter) throw ();

    virtual bool onBEGIN(std::string& begin) const throw ();

    virtual bool onBEGIN(std::string& begin, StreamWriter& streamwriter) throw ();

    virtual bool onSEQ(std::string& seq) const throw ();

    virtual bool onSEQ(std::string& seq, StreamWriter& streamwriter) throw ();

    virtual bool onBulletin(std::string& bulletinFragment) const throw ();

    virtual bool onBulletin(std::string& bulletinFragment, StreamWriter& streamwriter) throw ();

    virtual bool onEND(std::string& end) const throw ();

    virtual bool onEND(std::string& end, StreamWriter& streamwriter) throw ();

};

};

#endif	/* METCODE_MESSAGEITA5_H */

