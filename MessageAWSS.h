/* 
 * File:   MessageAWSS.h
 * Author: kavlar
 *
 * Created on 20140914
 */

#ifndef METCODE_MESSAGEAWSS_H
#define	METCODE_MESSAGEAWSS_H

#include "Message.h"

namespace MetCode
{

class MessageAWSS : public Message
{
public:
    MessageAWSS();

    virtual ~MessageAWSS();

public:
    MessageAWSS(const MessageAWSS& orig);

private:

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

#endif	/* METCODE_MESSAGEAWSS_H */

