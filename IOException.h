/* 
 * File:   IOException.h
 * Author: kavlar
 *
 * Created on 20140821
 */

#ifndef METCODE_IOEXCEPTION_H
#define	METCODE_IOEXCEPTION_H

#include "Exception.h"

namespace MetCode
{

class IOException : public Exception
{
public:
    IOException();
    IOException(const IOException& orig);
    virtual ~IOException() throw ();
private:

};

};

#endif	/* METCODE_IOEXCEPTION_H */

