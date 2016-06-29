#include "stdafx.h"
#include "TestProgramOptions.h"

namespace po = boost::program_options;
void test_wstringstream();
void test_wifstream();


TestProgramOptions::TestProgramOptions()
{
    //test_wstringstream();
    //test_wifstream();
    //test_notifier();
    //test_multitoken();
    //test_multitoken_2();
    //test_positional();
    test_positional_2();
}


void TestProgramOptions::test_wstringstream()
{
    po::options_description desc( "Test Options" );
    
    desc.add_options()
        ( "foo", po::wvalue<std::wstring>(), "bar" )
        ;

    po::variables_map vm;
    std::wstringstream strm( wstring_from_file( L"test-unicode-options.ini" ) );

    try
    {
        store( po::parse_config_file( strm, desc ), vm );

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
    namespace po = boost::program_options;
    po::options_description desc( "Test Options" );

    desc.add_options()
        ( "foo", po::wvalue<std::wstring>(), "bar" )
        ;

    po::variables_map vm;
    std::wifstream wifs( "test-unicode-options.ini" );
    wifs.seekg( 2, std::ios::beg );

    try
    {
        store( po::parse_config_file( wifs, desc ), vm );

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
        delete[] buf;
    }

    return ws;
}


void TestProgramOptions::test_notifier()
{
    struct Handler
    {
        static void handler( const std::string& s )
        {
            std::cout << "Handler: " << s << std::endl;
        }
    };

    po::options_description desc( "Test Duplicate Options" );
    desc.add_options()
        ( "foo", po::value<std::string>()->notifier( &Handler::handler )->value_name( "value name" ), "foo 2" )
        ;

    std::stringstream strm;
    strm << "foo = hwllo, world";

    try
    {
        po::variables_map vm;
        store( po::parse_config_file<char>( strm, desc ), vm );
        notify( vm );
    }
    catch ( std::exception& e )
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
}


void TestProgramOptions::test_variables_map()
{
    po::variables_map vm1;
    po::variables_map vm2;

    BOOST_FOREACH( const po::variables_map::value_type& v, vm1 )
    {
        vm2.insert( v );
    }
}


void TestProgramOptions::test_multitoken()
{
    char* argv[] = { "place-holder", "--foo", "hello, world", "good, morning" };
    int argc = sizeof( argv ) / sizeof( char* );
    po::options_description desc;
    desc.add_options()
        ( "foo", po::value< std::vector<std::string> >()->multitoken(), "test" )
        ;
    po::variables_map vm;

    try
    {
        store( po::parse_command_line<char>( argc, argv, desc ), vm );

        if ( vm.count( "foo" ) )
        {
            std::vector<std::string> vs = vm["foo"].as< std::vector<std::string> >();
            std::copy( vs.begin(), vs.end(), std::ostream_iterator<std::string>( std::cout, ", " ) );
            std::cout << std::endl;
        }
    }
    catch ( std::exception& e)
    {
        std::cout << "error: " << e.what() << std::endl;
    }
}


void TestProgramOptions::test_multitoken_2()
{
    char* argv[] = { "place-holder", "hello, world", "good, morning" };
    int argc = sizeof( argv ) / sizeof( char* );
    po::options_description desc;
    desc.add_options()
        ( "foo", po::value< std::vector<std::string> >()->multitoken(), "test" )
        ;
    po::variables_map vm;

    po::positional_options_description odesc;
    odesc.add( "foo", -1 );

    try
    {
        store( po::command_line_parser( argc, argv ).options( desc ).positional( odesc ).run(), vm );

        if ( vm.count( "foo" ) )
        {
            std::vector<std::string> vs = vm["foo"].as< std::vector<std::string> >();
            std::copy( vs.begin(), vs.end(), std::ostream_iterator<std::string>( std::cout, ", " ) );
            std::cout << std::endl;
        }
    }
    catch ( std::exception& e)
    {
        std::cout << "error: " << e.what() << std::endl;
    }
}


void TestProgramOptions::test_positional()
{
    char* argv[] = { "place-holder", "foo", "bar1", "bar2", "foobar1", "foobar2", "foobar3" };
    int argc = sizeof( argv ) / sizeof( char* );
    po::options_description desc;
    desc.add_options()
        ( "foo", po::value< std::vector<std::string> >(), "foo" )
        ( "bar", po::value< std::vector<std::string> >(), "bar" )
        ( "foobar", po::value< std::vector<std::string> >(), "foobar" )
        ;
    po::variables_map vm;

    po::positional_options_description odesc;
    odesc.add( "foo", 1 ).add( "bar", 2 ).add( "foobar", -1 );

    try
    {
        store( po::command_line_parser( argc, argv ).options( desc ).positional( odesc ).run(), vm );

        if ( vm.count( "foo" ) )
        {
            std::vector<std::string> vs = vm["foo"].as< std::vector<std::string> >();
            std::copy( vs.begin(), vs.end(), std::ostream_iterator<std::string>( std::cout, ", " ) );
            std::cout << std::endl;
        }

        if ( vm.count( "bar" ) )
        {
            std::vector<std::string> vs = vm["bar"].as< std::vector<std::string> >();
            std::copy( vs.begin(), vs.end(), std::ostream_iterator<std::string>( std::cout, ", " ) );
            std::cout << std::endl;
        }

        if ( vm.count( "foobar" ) )
        {
            std::vector<std::string> vs = vm["foobar"].as< std::vector<std::string> >();
            std::copy( vs.begin(), vs.end(), std::ostream_iterator<std::string>( std::cout, ", " ) );
            std::cout << std::endl;
        }
    }
    catch ( std::exception& e)
    {
        std::cout << "error: " << e.what() << std::endl;
    }
}




void TestProgramOptions::test_positional_2()
{
    char* argv[] = { "place-holder", "foo", "bar1", "--hello=world", "bar2", "foobar1", "foobar2", "--hello", "world2", "foobar3" };
    int argc = sizeof( argv ) / sizeof( char* );
    po::options_description desc;
    desc.add_options()
        ( "hello", po::value< std::vector<std::string> >(), "hello" )
        ( "foo", po::value< std::vector<std::string> >(), "foo" )
        ( "bar", po::value< std::vector<std::string> >(), "bar" )
        ( "foobar", po::value< std::vector<std::string> >(), "foobar" )
        ;
    po::variables_map vm;

    po::positional_options_description odesc;
    odesc.add( "foo", 1 ).add( "bar", 2 ).add( "foobar", -1 );

    try
    {
        store( po::command_line_parser( argc, argv ).options( desc ).positional( odesc ).run(), vm );

        if ( vm.count( "hello" ) )
        {
            std::vector<std::string> vs = vm["hello"].as< std::vector<std::string> >();
            std::copy( vs.begin(), vs.end(), std::ostream_iterator<std::string>( std::cout, ", " ) );
            std::cout << std::endl;
        }

        if ( vm.count( "foo" ) )
        {
            std::vector<std::string> vs = vm["foo"].as< std::vector<std::string> >();
            std::copy( vs.begin(), vs.end(), std::ostream_iterator<std::string>( std::cout, ", " ) );
            std::cout << std::endl;
        }

        if ( vm.count( "bar" ) )
        {
            std::vector<std::string> vs = vm["bar"].as< std::vector<std::string> >();
            std::copy( vs.begin(), vs.end(), std::ostream_iterator<std::string>( std::cout, ", " ) );
            std::cout << std::endl;
        }

        if ( vm.count( "foobar" ) )
        {
            std::vector<std::string> vs = vm["foobar"].as< std::vector<std::string> >();
            std::copy( vs.begin(), vs.end(), std::ostream_iterator<std::string>( std::cout, ", " ) );
            std::cout << std::endl;
        }
    }
    catch ( std::exception& e)
    {
        std::cout << "error: " << e.what() << std::endl;
    }
}
