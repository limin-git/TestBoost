#include "stdafx.h"
#include "TestFstream.h"


TestFstream::TestFstream()
{
    //test1();
    test2();
}


void TestFstream::test1()
{
    {
        std::ofstream os( "test.txt" );
        os << "hello, world!" << std::endl;
    }

    std::cout << "check file 'test.txt'" << std::endl;
    _getch();

    std::fstream fs( "test.txt", std::ios::in | std::ios::out | std::ios::app );
    //fs.unsetf( std::ios::skipws );

    for( std::string s; std::getline( fs, s ); )
    {
        std::cout << s << std::endl;
    }

    std::cout << "print file content" << std::endl;
    _getch();

    //fs.seekp( 0, std::ios::end );
    fs.clear();
    fs << "good, morning" << std::endl;

    std::cout << "write somethin to file 'test.txt'" << std::endl;
    _getch();
    
    fs.close();
    fs.open( "test.txt", std::ios::out | std::ios::trunc );
    fs << "abc" << std::endl;
    fs.close();
    std::cout << "replace file content with something other" << std::endl;
}


void TestFstream::test2()
{
    if ( 0 )
    {
        // empty file
        std::wofstream os( "test.txt" );
    }

    std::wfstream fs( "test.txt", std::ios::in | std::ios::out | std::ios::app );

    for( std::wstring s; std::getline( fs, s ); )
    {
        std::wcout << s << std::endl;
    }

    fs.clear();
    fs << L"hello, world!" << std::endl;
    fs.close();
    boost::system::error_code ec;
    boost::filesystem::remove( "test.txt", ec );
}
