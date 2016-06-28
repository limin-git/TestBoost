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
    struct Thread
    {
        Thread()
        {
            m_running = true;
            m_thread = new boost::thread( boost::ref(*this) );
        }

        ~Thread()
        {
            terminate();
            m_thread->join();
            delete m_thread;
        }

        void terminate()
        {
            m_running = false;
        }

        void operator()()
        {
            while ( m_running )
            {
                std::cout << "hello, world "  << std::endl;
                Sleep( 100 );
            }
        }
    };

    Thread t;
    _getch();
}
