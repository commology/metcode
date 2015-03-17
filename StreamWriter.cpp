/* 
 * File:   StreamWriter.cpp
 * Author: kavlar
 * 
 * Created on 20140821
 */

#include "StreamWriter.h"

MetCode::StreamWriter::StreamWriter()
{
    pos = NULL;
}

MetCode::StreamWriter::StreamWriter(const StreamWriter& orig)
{
}

MetCode::StreamWriter::~StreamWriter()
{
    ofs.close();
}

void MetCode::StreamWriter::reset() throw ()
{
    cache.clear();
    cache.str("");
    n_line = 0;
    n_group = 0;
}

bool MetCode::StreamWriter::log(const std::string& level, const std::string& text) const throw (IOException)
{
    std::cerr << "<< [" << level << "]" << text << std::endl;
    return true;
}

bool MetCode::StreamWriter::open(const std::string& filename) throw (IOException)
{
    ofs.open(filename.c_str(), std::ofstream::out | std::ofstream::binary);
    if (ofs.fail())
    {
        ofs.close();
        log("E", "Failed to open file: " + filename);
        throw IOException();
        return false;
    }

    pos = static_cast<std::ostream*> (&ofs);
    reset();
    return true;
}

bool MetCode::StreamWriter::open(std::ostream& os) throw (IOException)
{
    if (os.fail())
    {
        log("E", "Failed to write istream");
        throw IOException();
        return false;
    }

    pos = static_cast<std::ostream*> (&os);
    reset();
    return true;
}

bool MetCode::StreamWriter::isEOF() throw (IOException)
{
    return pos->fail();
}

extern void trim(std::string& str, const std::string chars);

bool MetCode::StreamWriter::put(const std::string& str, unsigned long& line,
                                const bool new_line,
                                const bool skip_empty_line,
                                const std::string& delimit) throw (IOException)
{
    bool result = false;

    if (cache)
    {
        if (new_line)
        {
            if (skip_empty_line && str.size() == 0)
            {
            }
            else
            {
                n_line++;
                cache << delimit;
            }
        }
        
        cache << str;
        line = n_line;

        if (cache.good())
        {
            result = true;
        }
    }

    //std::cerr << ">> PUTLINE (" << line << ") : " << str.size() << "[" << str << "]" << std::endl;

    return result;
}

bool MetCode::StreamWriter::put(const std::string& str, unsigned long& group, unsigned long& line,
                                const bool new_group, const bool new_line,
                                const bool skip_empty_group,
                                const bool skip_empty_line,
                                const std::string& group_delimit,
                                const std::string& line_delimit) throw (IOException)
{
    bool result = false;

    if (cache)
    {
        if (new_line)
        {
            result = put(str, line, new_line, skip_empty_line, line_delimit);
        }
        else
        {
            if (new_group)
            {
                if (skip_empty_group && str.size() == 0)
                {
                }
                else
                {
                    n_group++;
                    cache << group_delimit;
                }
            }

            cache << str;
            group = n_group;

            if (cache.good())
            {
                result = true;
            }
        }
    }

    //std::cerr << ">> PUTGROUP (" << line << "," << group << ") : " << str.size() << "[" << str << "]" << std::endl;

    return result;
}

bool MetCode::StreamWriter::flush(bool prefix_size, const std::string& type) throw (IOException)
{
    if (*pos)
    {
        if (prefix_size)
        {
            char buf[20];
            ::sprintf(buf, "%08d\0", cache.str().size());
            *pos << buf;
        }
        *pos << type.substr(0, 2);
        *pos << cache.str();
        
        cache.clear();
        cache.str("");
    }
    else
    {
        throw IOException();
        return false;
    }
}

void MetCode::StreamWriter::close() throw (IOException)
{
    ofs.close();
    pos = NULL;
    reset();
}
