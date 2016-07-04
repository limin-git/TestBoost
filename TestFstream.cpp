#include "stdafx.h"
#include "TestFstream.h"


TestFstream::TestFstream()
{
    test1();
    //test2();
}


void TestFstream::test1()
{
    {
        std::ofstream os( "test.txt" );
        os << "hello, world!" << std::endl;
    }

    std::fstream fs( "test.txt", std::ios::in | std::ios::out );
    //fs.unsetf( std::ios::skipws );

    std::string s;
    while ( std::getline( fs, s ) )
    {
        std::cout << s << std::endl;
    }

    fs.clear();
    fs.seekp( 0, std::ios::end );

    //fs.clear();
    fs << "good, morning" << std::endl;


    //std::cout << s << std::endl;
}
