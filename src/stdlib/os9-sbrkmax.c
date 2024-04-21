// os9-sbrkmax.c - sbrkmax() for OS-9.
//
// By Pierre Sarrazin <http://sarrazip.com/>.
// This file is in the public domain.
//
// Does not store the OS-9 error code upon error.

#include "os9-sbrk-util.h"


enum
{
    LARGE_INCREMENT = 0x2000,
    SMALL_INCREMENT = 0x0100,  // smallest increment allowed by F$Mem
};


size_t
sbrkmax(void)
{
    static void *maxAddress = NULL;

    void *origEnd = _CMOC_initSbrkAllocator();
    if (origEnd == NULL)
        return 0;

    if (maxAddress == NULL)  // if not already computed
    {
        // Advance the end until OS-9 reports a failure.
        void *highestEnd = origEnd;
        size_t increment = LARGE_INCREMENT;  // start w/ large inc, to reduce # of system calls
        while (highestEnd <= 0xFE00)
        {
            void *grantedEnd = _CMOC_resizeDataMemoryArea(highestEnd + increment);
            if (grantedEnd == NULL)  // if failed
            {
                if (increment == SMALL_INCREMENT)
                    break;  // got highest possible address
                increment = SMALL_INCREMENT;  // continue with smaller increments
                continue;
            }
            highestEnd += increment;
        }

        // Restore the original end.
        if (_CMOC_resizeDataMemoryArea(origEnd) == NULL)
            return 0;

        maxAddress = highestEnd;  // remember for next call
    }
    return maxAddress - _CMOC_freeDataMemoryStart;
}
