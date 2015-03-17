/* 
 * File:   StreamReader.h
 * Author: kavlar
 *
 * Created on 20140821
 */

#ifndef METCODE_STREAMREADER_H
#define	METCODE_STREAMREADER_H

#include <string>
#include <fstream>
#include "IOException.h"

#define STREAMREADER_DEFAULT_DELIMIT " \t\r\n"

namespace MetCode
{

class StreamReader
{
public:

    static const int BUFFER_SIZE = 1024;
    const std::string DEFAULT_DELIMIT;

public:
    
    StreamReader(size_t bufferSize = StreamReader::BUFFER_SIZE);
    
    virtual ~StreamReader();

private:

    StreamReader(const StreamReader& orig);

private:

    std::ifstream ifs;
    std::istream* pis;

private:

    size_t buffersize;
    char* buffer;

    std::string cache;

private:

    unsigned long n_line;
    unsigned long n_concrete_line;
    unsigned long n_group;
    unsigned long n_concrete_group;

protected:

    /*
     * Name:        log
     * Function:    formatted log
     * Returns:     (none)
     * Parameters:  level, text
     * Throws:      IOException
     */

    bool log(const std::string& level, const std::string& text) const throw (IOException);

public:

    /*
     * Name:        open
     * Function:    prepare to read stream from media
     * Returns:     true if reading is possible; false if otherwise
     * Parameters:  media
     * Throws:      IOException if failed to read from media
     */

    bool open(const std::string& filename) throw (IOException);

    bool open(std::istream& is) throw (IOException);

public:

    /*
     * Name:        isEOF
     * Function:    test if stream is at end
     * Returns:     true if is EOF; false if otherwise
     * Parameters:  (none)
     * Throws:      IOException if failed to test
     */

    bool isEOF() throw (IOException);

private:

    /*
     * Name:        reset
     * Function:    reset internal counters
     * Returns:     (none)
     * Parameters:  (none)
     * Throws:      (none)
     */

    void reset() throw ();

public:

    /*
     * Name:        close
     * Function:    finalize reading stream from media
     * Returns:     void
     * Parameters:  (none)
     * Throws:      IOException if something failed
     */

    void close() throw (IOException);

public:

    /*
     * Name:        get
     * Function:    get/read stream from media
     * Returns:     true if something is got; false if otherwise
     * Parameters:  output buffer and size
     *              delimiter
     * Throws:      IOException if failed to read from media
     */

    bool get(size_t size, std::string& str, unsigned long& line,
             const bool skip_empty_line = true) throw (IOException);

    bool get(std::string& str, unsigned long& group, unsigned long& line,
             const bool skip_empty_group = true,
             const bool skip_empty_line = true,
             const std::string& delimit = STREAMREADER_DEFAULT_DELIMIT,
             size_t size = 0) throw (IOException);

};

};

#endif	/* METCODE_STREAMREADER_H */

