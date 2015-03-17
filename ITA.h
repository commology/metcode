/* 
 * File:   ITA.h
 * Author: kavlar
 *
 * Created on 20140821
 */

#ifndef METCODE_ITA_H
#define	METCODE_ITA_H

#define ITA2_BEGIN  "ZCZC"
#define ITA2_END    "NNNN"

#define NUL     '\000'
#define SOH     '\001'
#define STX     '\002'
#define ETX     '\003'
#define EOT     '\004'
#define ENQ     '\005'
#define ACK     '\006'
#define BEL     '\007'

#define BS      '\010'
#define TAB     '\011'
#define LF      '\012'
#define VT      '\013'
#define FF      '\014'
#define CR      '\015'
#define SO      '\016'
#define SI      '\017'

#define DLE     '\020'
#define DC1     '\021'
#define DC2     '\022'
#define DC3     '\023'
#define DC4     '\024'
#define NAK     '\025'
#define SYN     '\026'
#define ETB     '\027'

#define CAN     '\030'
#define EM      '\031'
#define SUB     '\032'
#define ESC     '\033'
#define FS      '\034'
#define GS      '\035'
#define RS      '\036'
#define US      '\037'

#define SP      '\040'
#define SPACE   '\040'

#define DEL     '\177'

#define REPORT_END  '='

#define DEFAULT_GROUP_DELIMIT  " "
#define DEFAULT_LINE_DELIMIT   "\r\r\n"

#define AWSS_BEGIN  "BG"
#define AWSS_END    "ED"
#define AWSS_GROUP_DELIMIT  ","


#ifdef	__cplusplus
extern "C"
{
#endif

extern char ITA2L(int combination_number);

extern char ITA2F(int combination_number);

#ifdef	__cplusplus
}
#endif

#endif	/* METCODE_ITA_H */

