/**
 * @file dependency-injection.h
 * MIT License 
 * Copyright (c) 2022-Today Kamil Rog
 *
 * Dependency Injection
 * 
 * The Problem:
 *
 * Hardcoding a dependency into an object.
 *
 * Solution:
 *
 * Object receives other objects that it depends on, called dependencies.
 * code that passes the service to the client is called the injector.
 *
 * There are several ways of injecting the dependency, it can be done with
 * constructor or a setter injection function, in this example it is implemented
 * utilizing the former method.
 *
 * References:
 * https://stackoverflow.com/questions/29365084/is-dependency-injection-useful-in-c
 *
*/

#include <iostream>
#include <string>

/** 
 * Base dependency interface
 */
class Dependency
{
    public:

        virtual void Operation() = 0;
        virtual ~Dependency() = default;
};

/** 
 * Specialized Dependencies implementing the operation
*/
class SpecializedDependency1 : public Dependency
{
    public:
        virtual void Operation()
        {
            std::cout << "Output of specialized dependency 1" << std::endl;
        }
};

class SpecializedDependency2 : public Dependency
{
    public:
        virtual void Operation()
        {
            std::cout << "Output of specialized dependency 2" << std::endl;
        }
};

/** 
 * Service utilizing specialized dependencies thriough base interface
*/
class Service
{
    
    public:

        /** 
         * The dependency is passed in through constructor injection
         * as opposed to hard-coded into the class definition.
        */
        Service(Dependency *dependency) :
            m_dependency(dependency)
        {
            // Check dependency for nullptr.
            if(m_dependency == nullptr)
            {
                // Throw an exception.
                throw std::invalid_argument("Dependency must not be null");
            }
        }

        void ExecuteService()
        {
            std::cout << "Executing dependency operation!" << std::endl;
            // Abstract away the dependency implementation with polymorphism.
            m_dependency->Operation();
        }

    private:

        Dependency *m_dependency = nullptr;
};


int main()
{
    Dependency *dependency1 = new SpecializedDependency1();
    Dependency *dependency2 = new SpecializedDependency2();

    // Service is independent from the implementation of the dependency.
    // The dependenct is injected.
    Service service1(dependency1);
    service1.ExecuteService();

    // Execute service 2 with dependency 2.
    Service service2(dependency2);
    service2.ExecuteService();

    // Delete Dependencies.
    delete dependency1;
    delete dependency2;
    return 0;
}
