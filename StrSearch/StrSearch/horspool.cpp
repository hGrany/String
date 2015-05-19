#include "stdafx.h"
#include "horspool.h"

namespace ARC
{
    int horspool_search( const char* pstrSrc, unsigned int nLenSrc, const char* pstrDst, unsigned int nLenDst )
    {
        if( nLenDst > nLenSrc )
        {
            return 0;
        }

        const int cNumOfChar = 256;
        UINT arnFail[cNumOfChar] = { 0 };

        for( UINT i = 0; i < nLenDst - 1; ++i )
        {
            arnFail[pstrDst[i]] = i;
        }

        UINT i = nLenDst - 1;
        UINT n = 0;
        while( i < nLenSrc )
        {
            UINT j = nLenDst - 1;

            while( pstrSrc[i] == pstrDst[j] )
            {
                if( j == 0 )
                {
                    return i;
                }
                --i;
                --j;
            }

            char c = pstrSrc[n + nLenDst - 1];
            n = n + ( nLenDst - arnFail[c] ) - 1;

            i = n + nLenDst - 1;
        }
        
        return -1;
    }
}