#include "stdafx.h"
#include "bf.h"

namespace ARC
{    
    int bf_search( const char* pstrSrc, unsigned int nLenSrc, const char* pstrDst, unsigned int nLenDst )
    {
        UINT i = 0;
        while( i <= nLenSrc - nLenDst )
        {
            UINT n = i;
            UINT j = 0;
            while( pstrSrc[i] == pstrDst[j] )
            {
                ++i;
                ++j;

                if( j == nLenDst )
                {
                    return n;
                }
            }
            
            i = n + 1;
        }

        return -1;
    }
};