#include "stdafx.h"
#include "TestTokenizer.h"


TestTokenizer::TestTokenizer()
{
    test1();
}


void TestTokenizer::test1()
{
    std::string s = "1 seconds, 2 seconds; 3 seconds \t 4 seconds: 5 seconds";
    typedef boost::tokenizer< boost::char_separator<char> > tokenizer;
    boost::char_separator<char> sep( ";,:\t" );
    tokenizer tokens( s, sep );

    for ( tokenizer::iterator it = tokens.begin(); it != tokens.end(); ++it )
    {
        std::cout << *it << std::endl;
    }
}
