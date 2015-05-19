#include "stdafx.h"
#include "kmp.h"

namespace ARC
{
    typedef unsigned int UINT;

    //////////////////////////////
    //
    // KMP ��Ŀ����ƥ����������Ŀ�괮��ģʽ����ĳ��λ����ʧ��,
    // �����ܵĲ����ݻ����ٻ��ݵ�ָ��, �Ӷ��ӿ�ƥ��Ĺ���.
    // �㷨������һ������NEXT, ������ģʽ��P�ĳ�����ͬ.
    // NEXT[i]ֵ�����Ϊ0, ��ô��Ϊ��P[i](������P[i])֮ǰNEXT[i]
    // ���ַ���ɵĴ���P��һ��ǰ׺. ��P[i-NEXT[i]...i-1]��P
    // ��ǰ׺
    //
    // ������Ŀ�괮 S: abababacd ��ģʽ�� P: ababacd
    //
    //    0 1 2 3 4 5 6 7 8 9  
    // S: a b a b a b a c d
    // P: a b a b a c d
    // N: 0 0 0 1 2 3 0
    // 
    // S[5]!=P[5]. P[5]֮ǰ�ַ���ɵĵĴ��ĺ�׺��P��һ��ǰ׺. 
    // Ҳ����P[2-4]��P��һ��ǰ׺. ��P[2-4]=P[0-2]. �������׺��
    // �������3. ͨ���Ƚ�, ��֪S[0-4]=P[0-4], 
    // ����S[2-4]=P[2-4]. ����Ϊ P[0-2]=P[2-4], S[2-4]=P[0-2]. 
    // ��ʱ,�����Ƚ�S[5]��P[3]����, ����Ҫ����.
    //
    //    0 1 2 3 4 5 6 7 8 9  
    // S: a b a b a b a c d
    // P:     a b a b a c d
    // N:     0 0 0 1 2 3 0
    //
    // ��μ���NEXT
    // NEXT�ļ�����̿��Կ��������׺�������ǰ׺�Ĺ���
    // ��֪P[i...i+k]��P��ǰ׺, ����Ϊk+1. ��P[0...k]=P[i...i+k].
    // �������µ��ַ�P[i+k+1], ��P[i...i+k+1]�Ƿ���P��ǰ׺. 
    // ��ʱ, ���P[k+1]=P[i+k+1]. ��ô����
    // P��һ��ǰ׺�ҳ���Ϊk+1. ����NEXT[i+k+1]=k+1. 
    // ���P[k+1]!=P[i+k+1]. ���԰���ʧ������������. 
    // ��P[i...n]����Ŀ�괮, P[0...i]����ģʽ��.
    // 
    // �����ģʽ��P: ababacd, i=2, k=2, ���ַ�P[i+k+1]=c
    //     2 3 4 5 6
    // Pp: a b a c d
    //     0 1 2 3 4 5 6
    // Ps: a b a b a c d    ģʽ��
    //  N: 0 0 0 1 2 3 ?
    // P[i+k+1]!=P[i+1] ����ΪN[3]=1. ���Բ�����ָ��. ʹi=0,k=1
    // �����Ƚ�
    //     2 3 4 5 6
    // Pp: a b a c d
    //         0 1 2 3 4 5 6
    // Ps:     a b a b a c d    ģʽ��
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