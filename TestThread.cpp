#include "stdafx.h"
#include "TestThread.h"


TestThread::TestThread()
{
    //test1();
    test2();
}


void TestThread::test1()
{
    boost::thread* t = new boost::thread( foo );
    Sleep( 200 );
    delete t;
    Sleep( 200 );
}


void TestThread::foo()
{
    while ( true )
    {
        std::cout << "hello, world" << std::endl;
        //boost::thread::this_thread::sleep_for();
        Sleep( 100 );        
    }
}


void TestThread::test2()
{
    struct Test
    {
        Test( int x_ = 0 )
        {
            x = x_;
            m_running = true;
        }

        bool m_running;
        int x;
        void operator()()
        {
            while ( m_running )
            {
                std::cout << "hello, world " << x++ << std::endl;
                Sleep( 100 );
            }
        }

        ~Test()
        {
            //m_running = false;
        }
    };

    boost::thread* t = NULL;

    {
        Test obj;
        t = new boost::thread( boost::ref(obj) );
        Sleep(100);
    }

    std::cout << "Test destroyed" << std::endl;
    Sleep( 1000 );
    //t->join();
    //delete t;
}
