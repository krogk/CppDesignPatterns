/**
* @file scoped-thread.h
* MIT License 
* Copyright (c) 2022-Today Kamil Rog
*
* Thread guard pattern
*
* The Problem:
*
* Not joining the thread before the end of the scope 
*
* Solution:
*
* Wrapper object which contains the joins the thread if it is joinable upon the 
* 
*/

#include <thread>

class ThreadGuard
{
    public:

    // Prefixing constructor with explicit keyword prevents the compiler from using that constructor for implicit conversions
    explicit ThreadGuard(std::thread thr) :
        m_thr(thr) {}

    /**
     * Destructor
     * Provides join()
    */
    ~ThreadGuard()
    {
        if( m_thr.joinable() )
        {
            m_thr.join();
        }
    }

    /**
     * Delete copy constructor and copy-assignment respectivley 
     *  
     * Ensures the compiler is not going to generate these and as a result
     * priovide a way for object to outlive the thread it is suppose to join.
     * Instead a compilation error is going to be generated on the attempt to
     * execute these operations.
     * 
     */ 
    ThreadGuard(ThreadGuard const&) = delete;
    ThreadGuard& operator=(ThreadGuard const&) = delete;

    private:
    // Reference to the threads
    std::thread& m_thr;

};