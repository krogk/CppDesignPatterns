/**
* @file thread-object.h
* MIT License 
* Copyright (c) 2022-Today Kamil Rog
*
* Thread object wrapper 
*
* The Problem:
* 
* C++ thread can call only call static functions.
*
* Solution:
*
* A wrapper around the run function
*
* Usage:
*
* Create a thread object, inherit the public functions and override the Run()
* with desired functionality.
*
* Using derived object
* DerivedThread thr;
* thr.start();
* thr.join();
*
* 
*/

#ifndef __THREAD_OBJECT_H_
#define __THREAD_OBJECT_H_


#include <thread>


class ThreadObject
{

    public:
        /**
         * Start the thread.
         */
        inline void Start() 
        {
            // If pointer does not point to thread
            if (m_pThread == nullptr)
            {
                // Create new thread using static function and use this object instance
                m_pThread = new std::thread(ThreadObject::Execute, this);
            }
        }

        /**
         * Wait for the thread to finish it's execution.
         */
        inline void Join()
        {
            // If the thread pointer is not null 
            if (m_pThread != nullptr)
            {
                // Join thread
                m_pThread->join();
                // Delete thread
                delete m_pThread;
                // Reset thread pointer to null
                m_pThread = nullptr;
            }
        }

    protected:
        /**
         * This functions performs the work of the thread.
         * Override this purley virtual function.
         */
        virtual void Run() = 0;	

    private:

        // Pointer to the thread
        std::thread* m_pThread = nullptr;

        // Static function wrapper around run function 
        static void Execute(ThreadObject* threadObject)
        {
            threadObject->Run();
        }
};


#endif //__THREAD_OBJECT_H_