// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "kmp.h"
#include "bf.h"
#include "horspool.h"
#include "shift_and.h"

typedef int (*SEARCH_FUN )( const char*, unsigned int, const char*, unsigned int );

void FunTest( const std::string& strFunName, SEARCH_FUN pFun, const std::string& strSrc, const std::string& strDst )
{
#ifdef _DEBUG 
    UINT nTimes = 1;
#else
    UINT nTimes = 10000000;
#endif;

    int nRes = 0;

    DWORD dwStart = GetTickCount();

    for( UINT nT = 0; nT < nTimes; ++nT )
    {
        nRes = (*pFun)( strSrc.c_str(), strSrc.length(), strDst.c_str(), strDst.length() );
    }

    DWORD dwEnd = GetTickCount();

    std::cout << "[Name: " << strFunName << "  Time: " 
              << dwEnd - dwStart << "  Res: "
              << nRes << "]" << std::endl;
}

int _tmain( int argc, _TCHAR* argv[] )
{
    std::string strSrc = "abfwerpbvpsfpqaeprieababacd";
    std::string strDst = "ababacd";
    
    FunTest( "BF", ARC::bf_search, strSrc, strDst );

    FunTest( "KMP", ARC::kmp_search, strSrc, strDst );

    FunTest( "Horspool", ARC::horspool_search, strSrc, strDst );

    FunTest( "ShiftAnd", ARC::shift_and_search, strSrc, strDst );
    
    getchar();

    return 0;
}

