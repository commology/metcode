/* 
 * File:   StreamReader.cpp
 * Author: kavlar
 * 
 * Created on 20140821
 */

#include "StreamReader.h"

MetCode::StreamReader::StreamReader(size_t bufferSize)
: DEFAULT_DELIMIT(STREAMREADER_DEFAULT_DELIMIT)
{
    pis = NULL;
    buffersize = bufferSize;
    buffer = new char[buffersize];
}

MetCode::StreamReader::StreamReader(const StreamReader& orig)
{
}

MetCode::StreamReader::~StreamReader()
{
    delete buffer;
    ifs.close();
}

void MetCode::StreamReader::reset() throw ()
{
    cache.clear();
    n_line = 0;
    n_concrete_line = 0;
    n_group = 0;
    n_concrete_group = 0;
}

bool MetCode::StreamReader::log(const std::string& level, const std::string& text) const throw (IOException)
{
    std::cerr << ">> [" << level << "]" << text << std::endl;
    return true;
}

bool MetCode::StreamReader::open(const std::string& filename) throw (IOException)
{
    ifs.open(filename.c_str(), std::ifstream::in | std::ifstream::binary);
    if (ifs.fail())
    {
        ifs.close();
        log("E", "Failed to open file: " + filename);
        throw IOException();
        return false;
    }

    pis = static_cast<std::istream*> (&ifs);
    reset();
    return true;
}

bool MetCode::StreamReader::open(std::istream& is) throw (IOException)
{
    if (is.fail())
    {
        log("E", "Failed to read istream");
        throw IOException();
        return false;
    }

    pis = static_cast<std::istream*> (&is);
    reset();
    return true;
}

bool MetCode::StreamReader::isEOF() throw (IOException)
{
    return pis->fail();
}

bool MetCode::StreamReader::get(size_t size, std::string& str, unsigned long& line,
                                const bool skip_empty_line) throw (IOException)
{
    size_t buf_size = buffersize;
    if (size > 0 && size < buf_size) buf_size = size;

    str.clear();

    bool result = false;

    while (*pis && (size == 0 || str.size() == 0))
    {
        if (size > 0 && buf_size > size - str.size())
            buf_size = size - str.size();

        pis->getline(buffer, buf_size);
        
        n_line++;
        
        size_t length = strlen(buffer);

        if (skip_empty_line && length == 0)
            continue;

        result = true;

        str += buffer;
        str += "\n";

        n_concrete_line++;

        if (skip_empty_line)
            line = n_concrete_line;
        else
            line = n_line;
    }

    //std::cerr << ">> GETLINE (" << line << ") : " << str.size() << "[" << str << "]" << std::endl;

    return result;
}

bool MetCode::StreamReader::get(std::string& str, unsigned long& group, unsigned long& line,
                                const bool skip_empty_group, const bool skip_empty_line,
                                const std::string& delimit, size_t size) throw (IOException)
{
    bool result = false;

    unsigned long posSep;

    while (!result)
    {
        if (cache.size() == 0)
        {
            std::string rstr;
            result = this->get(buffersize, rstr, line, skip_empty_line);
            //std::cout << ">> GETCACHE (" << line << "," << group << ") : " << cache.size() << "[" << cache << "]" << std::endl;
            if (!result)
                break;
            cache += rstr;
        }

        posSep = cache.find_first_of(delimit);

        if (posSep == std::string::npos)
        {
            if (size == 0 || size > cache.size())
                continue;
        }
        else
        {
            str = cache.substr(0, posSep);
            cache = cache.substr(posSep + 1);
            if (cache.size() == 0)
                continue;
            //std::cout << ">> CUTCACHE (" << line << "," << group << ") : " << cache.size() << "[" << cache << "]" << std::endl;
            n_group++;
            if (str.size() > 0)
            {
                n_concrete_group++;
                if (skip_empty_group)
                {
                    group = n_concrete_group;
                }
                else
                {
                    group = n_group;
                }
                result = true;
            }
            else
            {
                if (skip_empty_group)
                {
                    result = false;
                }
                else
                {
                    group = n_group;
                    result = true;
                }
            }
        }
    }

    //std::cerr << ">> GETGROUP (" << line << "," << group << ") : " << str.size() << "[" << str << "]" << std::endl;

    return result;
}

void MetCode::StreamReader::close() throw (IOException)
{
    ifs.close();
    pis = NULL;
    reset();
}
