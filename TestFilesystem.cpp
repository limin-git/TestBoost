#include "stdafx.h"
#include "TestFilesystem.h"


namespace fs = boost::filesystem;


TestFilesystem::TestFilesystem()
{
    //test_system_complete();
    test_parent_path();
}


void TestFilesystem::test_system_complete()
{
    fs::path p( "test.txt" );
    fs::path p2 = fs::system_complete( p );
    std::cout << p2.string() << std::endl;
}


void TestFilesystem::test_parent_path()
{
    fs::path p( "test.txt" );
    fs::path p2 = fs::system_complete( p );

    while ( p2.has_parent_path() )
    {
        fs::path parent = p2.parent_path();
        p2 = parent;
        std::cout << parent.string() << std::endl;
    }

}
