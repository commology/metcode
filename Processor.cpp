/* 
 * File:   Processor.cpp
 * Author: kavlar
 * 
 * Created on 20140821
 */

#include "Processor.h"

template<class Type>
MetCode::Processor<Type>::Processor()
{
}

template<class Type>
MetCode::Processor<Type>::Processor(const Processor& orig)
{
}

template<class Type>
MetCode::Processor<Type>::~Processor()
{
}

template<class Type>
bool MetCode::Processor<Type>::registerInstance(Type* impl) throw ()
{
    if (setInstance.find(impl) != setInstance.end())
        return false;
    setInstance.insert(impl);
    return true;
}

template<class Type>
bool MetCode::Processor<Type>::enquireInstances(const std::string& headFragment) throw ()
{
    bool result = false;

    for (std::set<Type*>::iterator iter = setInstance.begin(); iter != setInstance.end(); iter++)
    {
        Type* instance = *iter;
        if (instance->canIdentify(headFragment))
        {
            workingInstance = instance;
            if (defaultInstance == NULL)
                writerInstance = workingInstance;
            else
                writerInstance = defaultInstance;
            result = true;
            break;
        }
    }
    return result;
}

template<class Type>
bool MetCode::Processor<Type>::canIdentify(const std::string& headFragment) const throw ()
{
    return false;
}

template<class Type>
bool MetCode::Processor<Type>::setDefaultInstance(const bool default_writer) throw ()
{
    if (default_writer)
    {
        if (defaultInstance != this)
        {
            defaultInstance = static_cast<Type*>(this);
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (defaultInstance == this)
        {
            defaultInstance = NULL;
            return true;
        }
        else
        {
            return false;
        }
    }
}

extern void trim(std::string& str, const std::string chars);

template<class Type>
bool MetCode::Processor<Type>::log(const std::string& level, unsigned long line, unsigned group,
                                   const std::string& text, const std::string& detail) const throw (IOException)
{
    std::cerr << "[" << level << "]";
    std::cerr << "(" << line << "," << group << ")";
    std::cerr << module << " : " << text << std::endl;
    if (detail.size() > 0)
        std::cerr << "\"" << detail << "\"" << std::endl;
    return true;
}

template<class Type>
bool MetCode::Processor<Type>::main(StreamReader& streamreader, StreamWriter& streamwriter)
{
    return false;
}

template<class Type>
bool MetCode::Processor<Type>::process(std::string& data, StreamWriter& streamwriter)
{
    return false;
}
