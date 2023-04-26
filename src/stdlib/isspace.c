#include <cmoc.h>


int
isspace(int c)
{
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';  // \f and \v left off...
}

