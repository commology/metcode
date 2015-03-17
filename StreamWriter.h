/* 
 * File:   StreamWriter.h
 * Author: kavlar
 *
 * Created on 20140821
 */

#ifndef METCODE_STREAMWRITER_H
#define	METCODE_STREAMWRITER_H

#include <string>
#include <fstream>
#include <sstream>
#include "IOException.h"
#include "ITA.h"

namespace MetCode
{

class StreamWriter
{
public:
    
    StreamWriter();
    
    virtual ~StreamWriter();

private:

    StreamWriter(const StreamWriter& orig);

private:

    std::ofstream ofs;
    std::ostream* pos;

private:
    
    std::ostringstream cache;

private:

    unsigned long n_line;
    unsigned long n_group;

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
     * Function:    prepare to write stream to media
     * Returns:     true if writing is possible; false if otherwise
     * Parameters:  media
     * Throws:      IOException if failed to write to media
     */

    bool open(const std::string& filename) throw (IOException);

    bool open(std::ostream& os) throw (IOException);

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
     * Returns:     void
     * Parameters:  (none)
     * Throws:      (none)
     */

    void reset() throw ();

public:

    /*
     * Name:        close
     * Function:    finalize writing stream to media
     * Returns:     void
     * Parameters:  (none)
     * Throws:      IOException if something failed
     */

    void close() throw (IOException);

public:

    /*
     * Name:        put
     * Function:    put data into stream
     * Returns:     true if something is put; false if otherwise
     * Parameters:  input buffer
     *              delimiter
     * Throws:      IOException if failed to write to media
     */

    bool put(const std::string& str, unsigned long& line,
             const bool new_line = true,
             const bool skip_empty_line = true,
             const std::string& delimit = DEFAULT_LINE_DELIMIT) throw (IOException);

    bool put(const std::string& str, unsigned long& group, unsigned long& line,
             const bool new_group = true, const bool new_line = false,
             const bool skip_empty_group = true,
             const bool skip_empty_line = true,
             const std::string& group_delimit = DEFAULT_GROUP_DELIMIT,
             const std::string& line_delimit = DEFAULT_LINE_DELIMIT) throw (IOException);
    
public:
    
    /*
     * Name:        flush
     * Function:    write stream to media
     * Returns:     true if something is write; false if otherwise
     * Parameters:  prefix size (automatically)
     *              type indicator
     * Throws:      IOException if failed to write to media
     */

    bool flush(bool prefix_size = false, const std::string& type = "") throw (IOException);

};

};

#endif	/* METCODE_STREAMWRITER_H */

