/**
* @file scoped-thread.h
* MIT License 
* Copyright (c) 2022-Today Kamil Rog
*
* Scoped thread pattern
*
* The Problem:
*
* Solution:
*
*
* Notes:
* The functionality of the ScopedThread has been implemented and
* improved in C++20 standard under the concept of std::jthread.
* 
*/

#include <thread>
#include <stdexcept>
	
/**
 * Scoped Thread Class
 * Provides transfer of ownership
*/
class ScopedThread
{

    public:

    /**
     * Constructor
     * Transfers the ownership of of the input thread to the
     * member thread object.
     * 
    */
    explicit ScopedThread(std::thread thr) :
        m_thread(std::move(thr))
    {
        // If thread is non joinable
        if(!m_thread.joinable())
        { 
            // Throw exception
            throw std::logic_error("Thread non-joinable");
        }
    }

    /**
     * Destructor
     * Provides join()
    */
    ~ScopedThread()
    {
        m_thread.join();
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
    ScopedThread(ScopedThread const&) = delete;
    ScopedThread& operator=(ScopedThread const&) = delete;

    private:
    
    // Thread object
    std::thread m_thread;
};


