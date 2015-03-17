/* 
 * File:   FMCode.cpp
 * Author: kavlar
 * 
 * Created on 20140821
 */

#include "FMCode.h"

std::set<MetCode::FMCode*> MetCode::Processor<MetCode::FMCode>::setInstance;
MetCode::FMCode* MetCode::Processor<MetCode::FMCode>::workingInstance = NULL;
MetCode::FMCode* MetCode::Processor<MetCode::FMCode>::defaultInstance = NULL;
MetCode::FMCode* MetCode::Processor<MetCode::FMCode>::writerInstance = NULL;

MetCode::FMCode::FMCode()
{
    module = "FMCode";
    registerInstance(this);
    workingInstance = NULL;
    defaultInstance = NULL;
    writerInstance = NULL;
    state = UNKNOWN;
}

MetCode::FMCode::FMCode(const FMCode& orig)
{
}

MetCode::FMCode::~FMCode()
{
}

bool MetCode::FMCode::process(std::string& cache, StreamWriter& streamwriter)
{
    std::string group;

    unsigned long pos;

    // 0. (only) if in UNKNOWN state
    //    enquire instances and identify
    if (state == FMCode::UNKNOWN)
    {
        if (this->enquireInstances(cache))
        {
            // working instance has been re/assigned
            state = FMCode::ASSIGNED;
            // drop to ASSIGNED section
        }
        else
        {
            if (cache.size() > 0)
            {
                log("W", i_line, i_group, "un-identified text skipped.", group);

                cache.clear(); // no instances could identify
            }

            return true;
        }
    }

    // 1. (only) if in ASSIGNED state
    //    check MIMIMJMJ
    if (state == FMCode::ASSIGNED)
    {
        if (workingInstance == NULL || writerInstance == NULL)
        {
            log("F", i_line, i_group, "inconsistent state (ASSIGNED & NULL).", cache);
            // try to reset to UNKNOWN state
            state = FMCode::UNKNOWN;
        }
        else
        {
            bool isNextGroupYYGG = false;
            
            if (workingInstance->onMiMiMjMj(cache, isNextGroupYYGG))
            {
                if (isNextGroupYYGG)
                    // need next group as YYGG
                    state = FMCode::YYGG;
                else
                    // transit to MIMIMJMJ state
                    state = FMCode::MIMIMJMJ;

                if (writerInstance->onMiMiMjMj(cache, streamwriter))
                {
                }
                else
                {
                    log("W", o_line, o_group, "MiMiMjMj text ignored by target format.", group);
                }
            }
            else
            {
                log("W", i_line, i_group, "un-expected MiMiMjMj text skipped.", group);
            }
        }

        cache.clear();

        return true;
    }

    // 2. (only) if in YYGG state
    //    check YYGG
    if (state == FMCode::YYGG)
    {
        if (workingInstance == NULL || writerInstance == NULL)
        {
            log("F", i_line, i_group, "inconsistent state (YYGG & NULL).", cache);
            // try to reset to UNKNOWN state
            state = FMCode::UNKNOWN;
        }
        else
        {
            if (workingInstance->onYYGG(cache))
            {
                // transit to MIMIMJMJ state
                state = FMCode::MIMIMJMJ;

                if (writerInstance->onYYGG(cache, streamwriter))
                {
                }
                else
                {
                    log("W", o_line, o_group, "MiMiMjMj/YYGG text ignored by target format.", group);
                }
            }
            else
            {
                log("W", i_line, i_group, "un-expected MiMiMjMj/YYGG text skipped.", group);
            }
        }

        cache.clear();

        return true;
    }

    // 3. (only) if in BEGIN state
    if (state == FMCode::MIMIMJMJ)
    {
        state = FMCode::GROUP_HEAD;
    }
    
    // 4. (only) if in GROUP_HEAD or GROUP state
    if (state == FMCode::GROUP_HEAD || state == FMCode::GROUP)
    {
        if (workingInstance == NULL || writerInstance == NULL)
        {
            log("F", i_line, i_group, "inconsistent state (GROUP & NULL).", cache);
            // try to reset to UNKNOWN state
            state = FMCode::UNKNOWN;
        }
        else if (cache.size() == 0)     // notified when 'end of bulletin'
        {
            if (workingInstance->onEND(cache))
            {
                // finished the current FMCode, transit to END state
                state = FMCode::END;

                if (writerInstance->onEND(cache, streamwriter))
                {
                }
                else
                {
                    log("W", o_line, o_group, "END text ignored by target format.", group);
                }
            }
            else
            {
                log("W", i_line, i_group, "un-expected END text skipped.", group);
            }
        }
        else
        {
            if (state == FMCode::GROUP_HEAD)
            {
                if (workingInstance->onHeadGroup(cache))
                {
                    if (writerInstance->onHeadGroup(cache, streamwriter))
                    {
                    }
                    else
                    {
                        log("W", o_line, o_group, "FM code head group ignored by target format.", group);
                    }

                    cache.clear();
                }
                else
                {
                    log("W", i_line, i_group, "un-expected FM code group text skipped.", group);

                    cache.clear();
                }
                
                state = FMCode::GROUP;
            }
            else if (state == FMCode::GROUP)
            {
                if (*(cache.rbegin()) == '=')
                {
                    if (workingInstance->onEndGroup(cache))
                    {
                        if (writerInstance->onEndGroup(cache, streamwriter))
                        {
                        }
                        else
                        {
                            log("W", o_line, o_group, "FM code end group text ignored by target format.", group);
                        }

                        cache.clear();
                    }
                    else
                    {
                        log("W", i_line, i_group, "un-expected FM code end group head skipped.", group);

                        cache.clear();
                    }
                    state = FMCode::GROUP_HEAD;
                }
                else
                {
                    if (workingInstance->onGroup(cache))
                    {
                        if (writerInstance->onGroup(cache, streamwriter))
                        {
                        }
                        else
                        {
                            log("W", o_line, o_group, "FM code group text ignored by target format.", group);
                        }

                        cache.clear();
                    }
                    else
                    {
                        log("W", i_line, i_group, "un-expected FM code group head skipped.", group);

                        cache.clear();
                    }
                    state = FMCode::GROUP;
                }
                    
            }

            return true;
        }
    }

    // 4. (only) if in END state
    if (state == FMCode::END)
    {
        if (workingInstance == NULL || writerInstance == NULL)
        {
            log("F", i_line, i_group, "inconsistent state (END & NULL).", cache);
            // try to reset to UNKNOWN state
            state = FMCode::UNKNOWN;
        }
        else
        {
            c_object++;

            // transit to UNKNOWN state
            state = FMCode::UNKNOWN;
            workingInstance = NULL;
        }

        return true;
    }

    return false;
}

bool MetCode::FMCode::onMiMiMjMj(std::string& mimimjmj, bool& isNextGroupYYGG) const throw ()
{
    isNextGroupYYGG = false;
    return false;
}

bool MetCode::FMCode::onMiMiMjMj(std::string& mimimjmj, StreamWriter& streamwriter) throw ()
{
    return false;
}

bool MetCode::FMCode::onYYGG(std::string& yygg) const throw ()
{
    return false;
}

bool MetCode::FMCode::onYYGG(std::string& yygg, StreamWriter& streamwriter) throw ()
{
    return false;
}

bool MetCode::FMCode::onGroup(std::string& reportGroup) const throw ()
{
    return false;
}

bool MetCode::FMCode::onGroup(std::string& reportGroup, StreamWriter& streamwriter) throw ()
{
    return false;
}

bool MetCode::FMCode::onHeadGroup(std::string& reportHeadGroup) const throw ()
{
    return false;
}

bool MetCode::FMCode::onHeadGroup(std::string& reportHeadGroup, StreamWriter& streamwriter) throw ()
{
    return false;
}

bool MetCode::FMCode::onEndGroup(std::string& reportEndGroup) const throw ()
{
    return false;
}

bool MetCode::FMCode::onEndGroup(std::string& reportEndGroup, StreamWriter& streamwriter) throw ()
{
    return false;
}

bool MetCode::FMCode::onEND(std::string& end) const throw ()
{
    return false;
}

bool MetCode::FMCode::onEND(std::string& end, StreamWriter& streamwriter) throw ()
{
    return false;
}
