#include "stdafx.h"
#include "TestSemaphore.h"
#include <boost/interprocess/sync/interprocess_semaphore.hpp>


TestSemaphore::TestSemaphore()
{
    test1();
    //test2();
}


void TestSemaphore::test1()
{
    namespace ii = boost::interprocess;

    struct Producer
    {
        Producer( ii::interprocess_semaphore& semphore )
            : m_semaphore( semphore )
        {
        }

        void operator()()
        {
            while ( true )
            {
                if ( 'q' == _getch() )
                {
                    break;
                }

                m_semaphore.post();
            }
        }

        ii::interprocess_semaphore& m_semaphore;
    };

    struct Consumer
    {
        Consumer( ii::interprocess_semaphore& semphore )
            : m_semaphore( semphore )
        {
        }

        void operator()()
        {
            while ( true )
            {
                m_semaphore.wait();
                std::cout << "hello, world" << std::endl;
            }
        }

        ii::interprocess_semaphore& m_semaphore;
    };

    ii::interprocess_semaphore semaphore( 0 ); 
    Producer p( semaphore );
    Consumer c( semaphore );
    boost::thread producer( boost::ref(p) );
    boost::thread consumer( boost::ref(c) );
    producer.join();
}
