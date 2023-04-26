/*  cmoc-stdlib-private.h

    By Pierre Sarrazin <http://sarrazip.com/>.
    This file is in the public domain.
*/

#ifndef _H_cmoc_stdlib_private
#define _H_cmoc_stdlib_private


void _CMOC_applyRealFunction(void *fpa0Transform, float *p);


#if defined(_COCO_BASIC_)
#define _CMOC_ecb_or_dgn(ecb_value, dgn_value) ecb_value
#elif defined(DRAGON)
#define _CMOC_ecb_or_dgn(ecb_value, dgn_value) dgn_value
#endif


#endif  /* _H_cmoc_stdlib_private */
