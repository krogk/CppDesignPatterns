/**
 * @file object-pool.h
 * 
 * MIT License 
 * Copyright (c) 2022-Today Kamil Rog
 *
 * Object-Pool pattern
 *
 * The Problem:
 *
 * Creating and destroying objects causes memory fragmentation.
 * 
 * Solution:
 *
 * Preallocate objects and re-use 
 *
 * References:
 * https://gameprogrammingpatterns.com/object-pool.html 
 *
*/

#include <iostream>
#include <string>

/**
 * Resource class
*/
class Resource 
{

    public:

        void UseResource();
        /**
         * Reset
         * Resets the resource to initial known & safe state 
        */
        void Reset();

    private:

        float m_value;

};

/**
 * Object Pool Class
 * There are numerous ways of implementation,
 * the most important factor to consider here is the
 * ownership and memory management. 
*/
template <class T>
class ObjectPool
{

    ObjectPool() {}
    virtual ~ObjectPool(){}

    private:

    static const size_t PoolSize = 100;
    T m_resources[PoolSize];
    //std::stack<std::unique_ptr<T> > pool_;

};



template <class T>
class SharedPool
{
    public:
    using ptrType = std::unique_ptr<T, std::function<void(T*)>>;

        SharedPool() {}
        virtual ~SharedPool(){}

        void Add(std::unique_ptr<T> t)
        {
            m_pool.push(std::move(t));
        }

        ptrType Acquire()
        {
            // Check if pool is empty
            assert(!m_pool.empty());

            // Lambda expression 
            ptrType tmp(m_pool.top().release(),
                [this](T* ptr)
                {
                    this->Add(std::unique_ptr<T>(ptr));
                });
            m_pool.pop();
            return std::move(tmp);
        }

        // Check if pool is empty 
        bool Empty() const
        {
            return m_pool.empty();
        }

        // Get size of the pool
        size_t Size() const
        {
            return m_pool.size();
        }

    private:

        std::stack<std::unique_ptr<T> > m_pool;
};