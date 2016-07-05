// TestBoost.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TestChrono.h"
#include "TestTokenizer.h"
#include "TestProgramOptions.h"
#include "TestFilesystem.h"
#include "TestThread.h"
#include "TestSemaphore.h"
#include "TestLexicalCast.h"
#include "TestFstream.h"


int _tmain(int argc, _TCHAR* argv[])
{
    std::ios_base::sync_with_stdio( false );

    if ( 0 )
    {
        TestChrono test;
    }

    if ( 0 )
    {
        TestTokenizer test;
    }

    if ( 0 )
    {
        TestProgramOptions test;
    }

    if ( 0 )
    {
        TestFilesystem test;
    }

    if ( 0 )
    {
        TestThread test;
    }

    if ( 0 )
    {
        TestSemaphore test;
    }

    if ( 0 )
    {
        TestLexicalCast test;
    }

    if ( 1 )
    {
        TestFstream test;
    }

	return 0;
}
