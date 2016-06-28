#include "stdafx.h"
#include "TestThread.h"


TestThread::TestThread()
{
    test1();
}


void TestThread::test1()
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
                std::cout << "hello, world" << std::endl;
                Sleep( 1000 );
            }
        }

        bool m_running;
        boost::thread* m_thread;
    };

    Thread t;
    _getch();
}
