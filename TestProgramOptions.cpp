#include "stdafx.h"
#include "TestProgramOptions.h"


void test_wstringstream();
void test_wifstream();


TestProgramOptions::TestProgramOptions()
{
    //test_wstringstream();
    //test_wifstream();
    test_duplicate_options();
}


void TestProgramOptions::test_wstringstream()
{
    namespace ps = boost::program_options;
    ps::options_description desc( "Test Options" );
    
    desc.add_options()
        ( "foo", ps::wvalue<std::wstring>(), "bar" )
        ;

    ps::variables_map vm;
    std::wstringstream strm( wstring_from_file( L"test-unicode-options.ini" ) );

    try
    {
        store( ps::parse_config_file( strm, desc ), vm );

        if ( vm.count("foo") )
        {
            std::wstring ws = vm["foo"].as<std::wstring>();
            WriteConsole( GetStdHandle(STD_OUTPUT_HANDLE), ws.c_str(), ws.size(), 0, 0 );
            std::cout << std::endl;
        }
    }
    catch ( std::exception& ex )
    {
        std::cout << "exception: " << ex.what() << std::endl;
    }
}


void TestProgramOptions::test_wifstream()
{
    namespace ps = boost::program_options;
    ps::options_description desc( "Test Options" );

    desc.add_options()
        ( "foo", ps::wvalue<std::wstring>(), "bar" )
        ;

    ps::variables_map vm;
    std::wifstream wifs( "test-unicode-options.ini" );
    wifs.seekg( 2, std::ios::beg );

    try
    {
        store( ps::parse_config_file( wifs, desc ), vm );

        if ( vm.count("foo") )
        {
            std::wstring ws = vm["foo"].as<std::wstring>();
            WriteConsole( GetStdHandle(STD_OUTPUT_HANDLE), ws.c_str(), ws.size(), 0, 0 );
            std::cout << std::endl;
        }
    }
    catch ( std::exception& ex )
    {
        std::cout << "exception: " << ex.what() << std::endl;
    }
}


std::wstring TestProgramOptions::wstring_from_file( const wchar_t* file_name, int code_page )
{
    std::wstring ws;
    std::ifstream is( file_name, std::ios::in | std::ios::binary );

    if ( !is )
    {
        return L"";
    }

    unsigned char ch[3] = { 0 };

    is.unsetf( std::ios::skipws );
    is.read( (char*)ch, 3 );

    if ( ch[0] == 0xFF && ch[1] == 0xFE ) // unicode: FF FE
    {
        is.seekg( -2, std::ios::end );
        size_t size = is.tellg();
        ws.resize( size / 2 );
        is.seekg( 2, std::ios::beg );
        is.read( (char*)&ws[0], size );
    }
    else if ( ch[0] == 0xEF && ch[1] == 0xBB && ch[2] == 0xBF ) // utf-8 + BOM: EF BB BF
    {
        is.seekg( -3, std::ios::end );
        size_t size = is.tellg();
        char* buf = new char[ size ];
        is.seekg( 3, std::ios::beg );
        is.read( buf, size );
        size_t wsize = MultiByteToWideChar( CP_UTF8, 0, buf, size, 0, 0 );
        ws.resize( wsize );
        MultiByteToWideChar( CP_UTF8, 0, buf, size, &ws[0], wsize );
        delete[] buf;
    }
    else // ANSI
    {
        is.seekg( 0, std::ios::end );
        size_t size = is.tellg();
        char* buf = new char[ size ];
        is.seekg( 0, std::ios::beg );
        is.read( buf, size );
        size_t wsize = MultiByteToWideChar( code_page, 0, buf, size, 0, 0 );
        ws.resize( wsize );
        MultiByteToWideChar( code_page, 0, buf, size, &ws[0], wsize );
    }

    return ws;
}


void TestProgramOptions::test_duplicate_options()
{
    struct Handler
    {
        static void handler( const std::string& s )
        {
            std::cout << "Handler: " << s << std::endl;
        }
    };


    namespace po = boost::program_options;

    po::options_description desc( "Test Duplicate Options" );
    desc.add_options()
        //( "foo", po::value<std::string>(), "foo 1" )
        ( "foo", po::value<std::string>()->notifier( &Handler::handler )->value_name( "value name" ), "foo 2" )
        //( "foo", po::value<std::string>()->notifier( &Handler::handler ), "foo 3" )
        ;


    //std::ofstream ofs( "test.txt" );
    //ofs <<  "foo = hwllo,world" << std::endl;
    //ofs.close();

    //std::ifstream ifs( "test.txt" );

    std::stringstream strm;
    strm << "foo = hwllo,world \n";

    try
    {
        po::variables_map vm;
        //po::parse_config_file<char>( ifs, desc, true );
        store( po::parse_config_file<char>( strm, desc ), vm );

        notify( vm );

        if ( vm.count("foo") )
        {
            std::cout << vm["foo"].as<std::string>() << std::endl;
        }
    }
    catch ( std::exception& e )
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    std::cout << desc << std::endl;

}
