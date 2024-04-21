// os9-sbrk.c - sbrk() for OS-9.
//
// By Pierre Sarrazin <http://sarrazip.com/>.
// This file is in the public domain.
//
// Does not store the OS-9 error code upon error.

#include "os9-sbrk-util.h"


// Returns (void *) -1 upon error.
//
void *
sbrk(size_t increment)
{
    if (_CMOC_initSbrkAllocator() == NULL)
        return (void *) -1;

    if (increment == 0)
        return _CMOC_freeDataMemoryStart;

    void *returnedAddress;
    if (_CMOC_dataSegmentEnd - _CMOC_freeDataMemoryStart < increment)
    {
        // Process does not already have enough space.
        // If _CMOC_freeDataMemoryStart + increment >= 0x10000, then the increment is too large.
        // Avoid overflow and 32-bit arithmetic.
        if (_CMOC_freeDataMemoryStart - 1 >= (void *) (0xFFFFu - increment))
            return (void *) -1;
        void *newDataSegmentEnd = _CMOC_resizeDataMemoryArea(_CMOC_freeDataMemoryStart + increment);
        if (newDataSegmentEnd == NULL)
            return (void *) -1;
        _CMOC_dataSegmentEnd = newDataSegmentEnd;
    }

    returnedAddress = _CMOC_freeDataMemoryStart;
    _CMOC_freeDataMemoryStart += increment;
    return returnedAddress;
}
