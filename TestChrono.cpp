#include "stdafx.h"
#include "TestChrono.h"


TestChrono::TestChrono()
{
    //string_to_time();
    //string_to_time_failed();
    empty_string_to_time();
}


void TestChrono::string_to_time()
{
    std::vector<std::string> string_list;
    std::stringstream strm;
    boost::chrono::seconds s;

    const char* str[] =
    {
        "0 seconds",    "7 minutes",    "30 minutes",   "30 minutes",   "1 hours",      "3 hours",      "5 hours",
        "7 hours",      "9 hours",      "11 hours",     "13 hours",     "15 hours",     "17 hours",     "19 hours",
        "24 hours",     "48 hours",     "72 hours",     "96 hours",     "120 hours",    "144 hours",    "168 hours",
        "192 hours",    "216 hours",    "240 hours",    "264 hours",    "288 hours",    "312 hours",    "336 hours",
        "360 hours",    "384 hours",    "408 hours",    "432 hours",    "456 hours",    "480 hours",    "504 hours",
        "528 hours",    "552 hours",    "576 hours",    "600 hours",    "624 hours",    "648 hours",    "672 hours",
        "696 hours",    "720 hours",    "744 hours",    "768 hours",    "792 hours",    "816 hours",    "840 hours"
    };

    string_list.assign( str, str + sizeof(str) / sizeof(char*) );

    for ( size_t i = 0; i < string_list.size(); ++i )
    {
        strm.clear();
        strm.str( string_list[i] );
        strm >> s;
        std::cout << s << std::endl;
    }
}


void TestChrono::string_to_time_failed()
{
    std::string good_str = " 5000 seconds ";
    std::string bad_str = "hello, world";

    {
        std::cout << "     ----- test 1 -----     " << std::endl;
        boost::chrono::seconds s;
        std::istringstream strm( good_str );
        strm >> s;
        std::cout << strm.good() << ", " << strm.fail() << std::endl;
        std::cout << s << std::endl;
    }

    {
        std::cout << "     ----- test 2 -----     " << std::endl;
        boost::chrono::seconds s;
        std::istringstream strm( bad_str );
        strm >> s;
        std::cout << strm.good() << ", " << strm.fail() << std::endl;
        std::cout << s << std::endl;
    }

    {
        std::cout << "     ----- test 3 -----     " << std::endl;
        boost::chrono::seconds s;
        std::istringstream strm( bad_str );
        strm >> s;
        std::cout << strm.good() << ", " << strm.fail() << std::endl;
        std::cout << s << std::endl;

        strm.str( good_str );
        strm >> s;
        std::cout << strm.good() << ", " << strm.fail() << std::endl;
        std::cout << s << std::endl;
    }

    {
        std::cout << "     ----- test 4 -----     " << std::endl;
        boost::chrono::seconds s;
        std::istringstream strm( bad_str );
        strm >> s;
        std::cout << strm.good() << ", " << strm.fail() << std::endl;
        std::cout << s << std::endl;

        strm.clear();

        strm.str( good_str );
        strm >> s;
        std::cout << strm.good() << ", " << strm.fail() << std::endl;
        std::cout << s << std::endl;
    }
}


void TestChrono::empty_string_to_time()
{
    {
        boost::chrono::seconds s;
        std::istringstream strm( "0 seconds" );
        strm >> s;
        std::cout << strm.good() << ", " << strm.fail() << ", " << strm.bad() << std::endl;
        std::cout << s << std::endl;
    }

    {
        boost::chrono::seconds s;
        std::istringstream strm( "1 seconds" );
        strm >> s;
        std::cout << strm.good() << ", " << strm.fail() << ", " << strm.bad() << std::endl;
        std::cout << s << std::endl;
    }

    {
        boost::chrono::seconds s;
        std::istringstream strm( "xxxxx" );
        strm >> s;
        std::cout << strm.good() << ", " << strm.fail() << ", " << strm.bad() << std::endl;
        std::cout << s << std::endl;
    }
}

