/* 
 * File:   Processor.h
 * Author: kavlar
 *
 * Created on 20140821
 */

#ifndef METCODE_PROCESSOR_H
#define	METCODE_PROCESSOR_H

#include <string>
#include <set>

#include "StreamReader.h"
#include "StreamWriter.h"

namespace MetCode
{

template<class Type> class Processor
{
public:

    Processor();

    virtual ~Processor();

private:

    Processor(const Processor& orig);

protected:

    std::string module;

protected:

    static std::set<Type*> setInstance;

    static Type* workingInstance;

    static Type* defaultInstance;

    static Type* writerInstance;

protected:

    unsigned long i_line;
    unsigned long i_group;
    unsigned long o_line;
    unsigned long o_group;

    unsigned long c_object;

protected:

    /*
     * Name:        registerInstance
     * Function:    insert instance as filter if not registered
     * Returns:     false if already registered; true if otherwise
     * Parameters:  instance this pointer
     * Throws:      (none)
     */

    bool registerInstance(Type* impl) throw ();

    /*
     * Name:        canIdentify
     * Function:    enquire if the instance can identify and process
     * Returns:     true if the instance can identify; false if otherwise
     * Parameters:  head fragment
     * Throws:      (none)
     * Note:        the filters must be mutual exclusive
     */

    virtual bool canIdentify(const std::string& headFragment) const throw ();

    /*
     * Name:        enquireInstances
     * Function:    enquire each instance as filter
     * Returns:     false if no one can identify; true if otherwise
     * Parameters:  head fragment
     * Throws:      (none)
     * Note:        the first found instance in the set will be assigned as
     *              working instance. since it is assumed that the filters
     *              must be mutual exclusive, there should be only one
     *              instance that can identify; if however there are more,
     *              and due to orderless set, the filters registering
     *              order are not guaranteed as their priority.
     */

    bool enquireInstances(const std::string& headFragment) throw ();

public:

    /*
     * Name:        setDefaultInstance
     * Function:    set instance as default instance
     * Returns:     false if already default; true if otherwise
     * Parameters:  default writer flag
     * Note:        when default writer flag = true:
     *              set this instance as default writer.
     *              when default writer flag = false:
     *              release default writer only if this instance is default
     *              if no one are specified as default, the original instance
     *              will be used as writer; if more than one are specified,
     *              the last one will be used as writer
     * Throws:      (none)
     */

    bool setDefaultInstance(const bool default_writer = true) throw ();

protected:

    /*
     * Name:        log
     * Function:    formatted log
     * Returns:     (none)
     * Parameters:  level, line#, group#, text, detail
     * Throws:      IOException
     */

    bool log(const std::string& level, unsigned long line, unsigned group,
             const std::string& text, const std::string& detail) const throw (IOException);

public:

    /*
     * Name:        main
     * Function:    read the stream data, call process
     * Returns:     true if the process successfully completed; false if otherwise
     * Parameters:  stream reader, stream writer
     * Throws:      
     */

    virtual bool main(StreamReader& streamreader, StreamWriter& streamwriter);

    /*
     * Name:        process
     * Function:    read the stream data, check each data fragment,
     *              enquire each instance, find the instance that can
     *              process the Type according to head fragment;
     *              write the stream data, using default writer instance,
     *              or using original reader instance
     * Returns:     true if the process successfully completed; false if otherwise
     * Parameters:  stream data, stream writer
     * Note:        if data is "", then the caller inform the callee of END
     * Throws:      
     */

    virtual bool process(std::string& data, StreamWriter& streamwriter);

};

};

#endif	/* METCODE_PROCESSOR_H */

