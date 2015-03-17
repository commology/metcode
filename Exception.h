/* 
 * File:   Exception.h
 * Author: kavlar
 *
 * Created on 20140821
 */

#ifndef METCODE_EXCEPTION_H
#define	METCODE_EXCEPTION_H

#include <exception>

namespace MetCode
{

class Exception : public std::exception
{
public:
    Exception();
    Exception(const Exception& orig);
    virtual ~Exception() throw ();
private:

};

};

#endif	/* METCODE_EXCEPTION_H */

