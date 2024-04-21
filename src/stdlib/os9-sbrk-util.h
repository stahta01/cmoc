// os9-sbrk-util.h
//
// By Pierre Sarrazin <http://sarrazip.com/>.
// This file is in the public domain.

#ifndef _H_OS9_SBRK_UTIL
#define _H_OS9_SBRK_UTIL

#include <cmoc.h>


extern void *_CMOC_dataSegmentEnd;
extern void *_CMOC_freeDataMemoryStart;


void *_CMOC_initSbrkAllocator(void);
void *_CMOC_getCurrentDataSegmentEnd(void);
void *_CMOC_resizeDataMemoryArea(void *requestedEnd);


#endif  /* _H_OS9_SBRK_UTIL */
