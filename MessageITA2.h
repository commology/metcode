/* 
 * File:   MessageITA2.h
 * Author: kavlar
 *
 * Created on 20140821
 */

#ifndef METCODE_MESSAGEITA2_H
#define	METCODE_MESSAGEITA2_H

#include "Message.h"

namespace MetCode
{

class MessageITA2 : public Message
{
public:

    MessageITA2();

    virtual ~MessageITA2();

private:
    
    MessageITA2(const MessageITA2& orig);

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

private:


};

};

#endif	/* METCODE_MESSAGEITA2_H */

