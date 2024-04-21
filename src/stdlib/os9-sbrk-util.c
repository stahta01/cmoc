// os9-sbrk-util.c - sbrk() for OS-9.
//
// By Pierre Sarrazin <http://sarrazip.com/>.
// This file is in the public domain.
//
// Variables and functions that are needed by the OS-9 versions
// of sbrk() and sbrkmax().

#include "os9-sbrk-util.h"


void *_CMOC_dataSegmentEnd;
void *_CMOC_freeDataMemoryStart;


asm void *
_CMOC_getCurrentDataSegmentEnd(void)
{
    asm
    {
        pshs    y           ; save data segment pointer
        clra
        clrb                ; D = 0 will only request info
        os9     $07         ; F$Mem
        tfr     y,d
        puls    y
        bcc     @done       ; success: go return D
        clra
        clrb                ; return NULL upon failure
@done
    }
}


// Initializes _CMOC_dataSegmentEnd and _CMOC_freeDataMemoryStart
// if not already done. May be called more than once.
// Returns the result of _CMOC_getCurrentDataSegmentEnd().
//
void *
_CMOC_initSbrkAllocator(void)
{
    if (_CMOC_dataSegmentEnd == NULL)  // if not already done
    {
        _CMOC_dataSegmentEnd = _CMOC_getCurrentDataSegmentEnd();
        if (_CMOC_dataSegmentEnd == NULL)  // if still null
            return NULL;
        _CMOC_freeDataMemoryStart = _CMOC_dataSegmentEnd;
    }
    return _CMOC_dataSegmentEnd;
}


void *
_CMOC_resizeDataMemoryArea(void *requestedEnd)
{
    void *grantedEnd = NULL;
    asm
    {
        pshs    y               ; save data segment pointer
        ldd     :requestedEnd
        subd    ,s              ; make relative to start of data segment
        os9     $07             ; F$Mem
        tfr     y,d
        puls    y
        bcs     @done           ; upon error, leave grantedEnd null
        std     :grantedEnd
@done
    }
    return grantedEnd;
}
