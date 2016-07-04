#include "stdafx.h"
#include "TestLexicalCast.h"


TestLexicalCast::TestLexicalCast()
{
    //test1();
    test2();
}


void TestLexicalCast::test1()
{
    std::wstring ws = L"123 \t hello, world!";
    std::wstringstream wstrm( ws );
    size_t x = 0;
    wstrm >> x;
    std::cout << x << std::endl;

    try
    {
        x = boost::lexical_cast<size_t>( ws );
    }
    catch ( std::exception& e )
    {
        std::cout << "error: " << e.what() << std::endl;
    }
}


void TestLexicalCast::test2()
{
    try
    {
        size_t x = boost::lexical_cast<size_t>( L"123" );
        std::cout << x << std::endl;
    }
    catch ( std::exception& e )
    {
        std::cout << "error: " << e.what() << std::endl;
    }

    try
    {
        size_t x = boost::lexical_cast<size_t>( L"123 " ); // the space will cause exception
        std::cout << x << std::endl;
    }
    catch ( std::exception& e )
    {
        std::cout << "error: " << e.what() << std::endl;
    }
}
