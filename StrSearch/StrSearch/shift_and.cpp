#include "stdafx.h"
#include "shift_and.h"
#include "bf.h"

namespace ARC
{
    int shift_and_search( const char* pstrSrc, unsigned int nLenSrc, const char* pstrDst, unsigned int nLenDst )
    {
        if( nLenDst > ( sizeof( int ) * 8 ) )
        {
            return bf_search( pstrSrc, nLenSrc, pstrDst, nLenDst );
        }

        const int cSizeOfChar = 256;
        UINT arnPresnece[cSizeOfChar] = { 0 };

        for( UINT i = 0; i < nLenDst; ++i )
        {
            arnPresnece[pstrDst[i]] |= ( 1 << i );
        }

        UINT nRes = 0;
        UINT nSuccess = ( 1 << nLenDst );

        for( UINT i = 0; i < nLenSrc; ++i )
        {
             nRes = ( ( pstrSrc[i] & arnPresnece[pstrSrc[i]] ) & ( (nRes << 1) + 1) );
            if( nRes == nSuccess )
            {
                return i;
            }
        }
        
        return -1;
    }
};