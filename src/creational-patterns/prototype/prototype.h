/**
 * @file prototype.h
 * MIT License 
 * Copyright (c) 2022-Today Kamil Rog
 *
 * Prototype creational pattern
 *
 * The Problem:
 *
 * Object instantiation being costly as a result of many complex operations in initialization processes.
 *
 * Solution:
 *
 * Createion of a new object cheaply with the help of an already constructed or pre-initialized
 * and stored object.
 *
 * Prefer to copy an existing object to creation of a new instance from scratch, as a result,
 * skiping costly operations.
 *
 * Existing object act as a prototype.
 *
 * Notes: Prototypes can be implemented as singletons.
*/


#include <iostream>
#include <string>
#include <unordered_map>

/**
* Prototype base class
*/
class Prototype 
{

    public:

        // Default constructor
        Prototype() {}

        // Constructor initializing string member variable via initalizer list 
        Prototype(std::string name)
            : m_prototypeName(name){}
        
        // Destructor
        virtual ~Prototype() {}

        // Pure virtual function responsible for cloning object
        virtual Prototype* Clone() const = 0;

        /**
         * Operation function
         * Prints the member variables 
        */
        virtual void Operation(float prototype_value)
        {
            this->m_prototypeValue = prototype_value;
            std::cout << "Prototype: " << m_prototypeName << " Value: " << m_prototypeValue << std::endl;
        }

    protected:

        std::string m_prototypeName;
        float m_prototypeValue;

};


/**
 * Specialized Prototype inherits from base prototype 
*/
class SpecializedPrototype1 : public Prototype
{
    public:
        
        // Constructor initializing prototype's member variables
        SpecializedPrototype1(std::string prototypeName, float prototypeValue)
        : Prototype(prototypeName), m_specializedPrototypeValue1(prototypeValue) {}
        
        /**
         * Clone function
         * Creates and returns a replica of the object.
         * Note the reutrned type is Prototype not SpecializedPrototype1.
         * In addition, the entity calling this clone is responsible for
         * memory management, i.e deleting the object
        */
        Prototype* Clone() const override
        {
            return new SpecializedPrototype1(*this);
        }

    private:

        float m_specializedPrototypeValue1;
};

class SpecializedPrototype2 : public Prototype
{
    public:
        
        // Constructor initializing prototype's member variables
        SpecializedPrototype2(std::string prototypeName, float prototypeValue)
        : Prototype(prototypeName), m_specializedPrototypeValue2(prototypeValue)
        { }
        
        /**
        * Clone function
        */
        Prototype* Clone() const override
        {
            return new SpecializedPrototype2(*this);
        }

    private:

        float m_specializedPrototypeValue2;
};

// See method factory creational pattern to understand PrototypeFactory 

enum class Prototypes
{
    PROTOTYPE_1 = 0,
    PROTOTYPE_2 = 1
};

/**
 * PrototypeFactory contains two specialized prototypes, each of these can be
 * used for cloneing.
*/
class PrototypeFactory 
{
    public:
        // Default constructor
        PrototypeFactory()
        {
            m_prototypes[Prototypes::PROTOTYPE_1] = new SpecializedPrototype1("Prototype_1 ", 180.f);
            m_prototypes[Prototypes::PROTOTYPE_2] = new SpecializedPrototype2("Prototype_2 ", 360.f);
        }

        /**
         * Destructor
         * Free memory allocated by deleting two prototypes.
         * TODO: Improvement: Use smart pointers
        */
        ~PrototypeFactory()
        {
            delete m_prototypes[Prototypes::PROTOTYPE_1];
            delete m_prototypes[Prototypes::PROTOTYPE_2];
        }

        /**
         * Create prototype
         * Creates new prototype, based on the input parameter which dictates 
         * the type of the prototype to be created will call clone function 
         * of appropriate specialized prototype.
        */
        Prototype *CreatePrototype(Prototypes type)
        {
            return m_prototypes[type]->Clone();
        }

    private:
        // Map holding prototype objects
        std::unordered_map<Prototypes, Prototype *, std::hash<int>> m_prototypes;
};

/**
 * Client Function
 * Create two specialized prototypes using the 
 * prototype factory
*/
void Client(PrototypeFactory &prototype_factory) {
    std::cout << "Creating prototype 1...\n";

    Prototype *prototype = prototype_factory.CreatePrototype(Prototypes::PROTOTYPE_1);
    prototype->Operation(75);
    delete prototype;

    std::cout << std::endl;

    std::cout << "Creating prototype 2...\n";
    prototype = prototype_factory.CreatePrototype(Prototypes::PROTOTYPE_2);
    prototype->Operation(100);

    delete prototype;
}

int main()
{
    // Create prototype factory
    PrototypeFactory *prototype_factory = new PrototypeFactory();
    // Call client function
    Client(*prototype_factory);
    // Delete prototype factory
    delete prototype_factory;

    // Exit gracefully
    return 0;
}