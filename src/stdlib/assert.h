/*  assert.h - Assert macro for CMOC

    By Pierre Sarrazin <http://sarrazip.com/>.
    This file is in the public domain.

    When NDEBUG is not defined, the following functions are declared by this
    header file in addition to the assert() macro.

    // Determine what happens after a failed assert, if no custom handler
    // as been installed by _SetFailedAssertHandler().
    // freeze: If non-zero, a failed assert will freeze on an infinite loop.
    //         If zero, it will call exit(1) (this is the default).
    //
    void _FreezeOnFailedAssert(int freeze);

    // Determine the function to be called when an assert() fails.
    // If this function is not called, an assert prints an error message to the console
    // and then calls exit(1). See also _FreezeOnFailedAssert().
    // The given handler does not have to exit or freeze. It is allowed to return
    // to let the execution continue.
    // If a handler is given to this function, then the value passed to
    // _FreezeOnFailedAssert() does not apply, because the handler decides
    // if it freezes or not.
    // The handler must have this signature:
    //   void (*)(const char *file, int lineno, const char *condition)
    //
    void _SetFailedAssertHandler(_FailedAssertHandler newHandler);
*/

#ifndef _ASSERT_H
#define _ASSERT_H

#ifdef NDEBUG
#define assert(cond)
#define _FreezeOnFailedAssert(freeze)
#define _SetFailedAssertHandler(newHandler)
#else
#include <assert-impl.h>
#endif

#endif  /* _ASSERT_H */
