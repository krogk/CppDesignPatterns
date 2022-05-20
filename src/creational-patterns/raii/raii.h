/**
* @file raii.h
* MIT License 
* Copyright (c) 2022-Today Kamil Rog
*
* Resource acquisition is initialization
*
* 'Resource' does not assume purley memory resources.
* It could be file handles, network sockets, locks etc
*
* RAII is programming idiom which dictates following:
*
*   * Encapsulate resource into a class
*
*   * Use resource via local instance of the class
*
*   * Resource management is automatically handled by the objects destructor
*
* Often is the resource is thought to be allocated inside the class via constructor,
* however it may also be allocated outside and passed in as a parameter as in example
* provided below.
* 
*/

// Type alias for RawResourceHandle, a simlpe char
using RawResourceHandle = char;

class ManagedResourceHandle
{

    public:

        /**
        * Consturctor
        * Assigns the passed in raw handle to
        * pointer member variable via initializer list
        */
        ManagedResourceHandle(RawResourceHandle* rawHandle) : m_rawHandle(rawHandle) {};
    
        /**
        * Destructor
        * Deletes the resource held by the object
        */
        ~ManagedResourceHandle() {delete m_rawHandle; }


    private:

        // Resource 
        RawResourceHandle* m_rawHandle;
};