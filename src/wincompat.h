#ifndef _H_wincompat
#define _H_wincompat

#ifndef PACKAGE  // Allow the compilation to define the package name as a macro.
static const char *PACKAGE = "cmoc";
#endif

#ifndef VERSION  // Allow the compilation to define the VERSION as a macro.
static const char *VERSION = "0.1.81";
#endif

#endif  /* _H_wincompat */
