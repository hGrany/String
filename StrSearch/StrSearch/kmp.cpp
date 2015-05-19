#include "stdafx.h"
#include "kmp.h"

namespace ARC
{
    typedef unsigned int UINT;

    //////////////////////////////
    //
    // KMP 的目的是匹配过程中如果目标串和模式串在某个位置上失配,
    // 尽可能的不回溯或者少回溯的指针, 从而加快匹配的过程.
    // 算法引入了一个数组NEXT, 长度与模式串P的长度相同.
    // NEXT[i]值如果不为0, 那么意为者P[i](不包含P[i])之前NEXT[i]
    // 个字符组成的串是P的一个前缀. 即P[i-NEXT[i]...i-1]是P
    // 的前缀
    //
    // 假设有目标串 S: abababacd 和模式串 P: ababacd
    //
    //    0 1 2 3 4 5 6 7 8 9  
    // S: a b a b a b a c d
    // P: a b a b a c d
    // N: 0 0 0 1 2 3 0
    // 
    // S[5]!=P[5]. P[5]之前字符组成的的串的后缀是P的一个前缀. 
    // 也就是P[2-4]是P的一个前缀. 即P[2-4]=P[0-2]. 且这个后缀的
    // 最长长度是3. 通过比较, 已知S[0-4]=P[0-4], 
    // 所以S[2-4]=P[2-4]. 又因为 P[0-2]=P[2-4], S[2-4]=P[0-2]. 
    // 此时,继续比较S[5]和P[3]即可, 不需要回溯.
    //
    //    0 1 2 3 4 5 6 7 8 9  
    // S: a b a b a b a c d
    // P:     a b a b a c d
    // N:     0 0 0 1 2 3 0
    //
    // 如何计算NEXT
    // NEXT的计算过程可以看做是求后缀是其否是前缀的过程
    // 已知P[i...i+k]是P的前缀, 长度为k+1. 即P[0...k]=P[i...i+k].
    // 当读入新的字符P[i+k+1], 求P[i...i+k+1]是否是P的前缀. 
    // 此时, 如果P[k+1]=P[i+k+1]. 那么它是
    // P的一个前缀且长度为k+1. 更新NEXT[i+k+1]=k+1. 
    // 如果P[k+1]!=P[i+k+1]. 可以按照失配问题来处理. 
    // 把P[i...n]当做目标串, P[0...i]当做模式串.
    // 
    // 如果有模式串P: ababacd, i=2, k=2, 新字符P[i+k+1]=c
    //     2 3 4 5 6
    // Pp: a b a c d
    //     0 1 2 3 4 5 6
    // Ps: a b a b a c d    模式串
    //  N: 0 0 0 1 2 3 ?
    // P[i+k+1]!=P[i+1] 又因为N[3]=1. 可以不回溯指针. 使i=0,k=1
    // 继续比较
    //     2 3 4 5 6
    // Pp: a b a c d
    //         0 1 2 3 4 5 6
    // Ps:     a b a b a c d    模式串
    //  N:     0 0 0 1 2 3 ?
    ////////////////////////////////////////////////////////////////
    int kmp_search( const char* pstrSrc, unsigned int nLenSrc, const char* pstrDst, unsigned int nLenDst )
    {
        UINT * pNext = new UINT[nLenDst + 1];

        pNext[0] = pNext[1] = 0;
        UINT j = 0;

        for( UINT i = 1; i < nLenDst - 1; ++i )
        {
            while( j != 0 && pstrDst[j] != pstrDst[i] )
            {
                j = pNext[j];
            }

            if( pstrDst[j] == pstrDst[i] )
            {
                ++j;
            }

            pNext[i + 1] = j;
        }

        j = 0;
        /*for( UINT i = 0; i < nLenSrc; ++i )
        {
            while( j != 0 && pstrDst[j] != pstrSrc[i] )
            {
                j = pNext[j];
            }

            if( pstrDst[j] == pstrSrc[i] )
            {
                ++j;
            }

            if( j == nLenDst )
            {
                delete [] pNext;
                return ( i + 1 - nLenDst );
            }
        }*/
        UINT i = 0;
        while( i < nLenSrc )
        {   
            if( pstrDst[j] == pstrSrc[i] )
            {               
                ++i;
                ++j;

                if( j == nLenDst )
                {
                    delete[] pNext;
                    return ( i - nLenDst );
                }
            }
            else
            {
                if( j == 0 )
                {
                    ++i;
                }
                j = pNext[j];                             
            } 
        };

        delete[] pNext;
        return -1;
    }

};