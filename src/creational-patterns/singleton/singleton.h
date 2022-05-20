/**
* @file singleton.h
* MIT License 
* Copyright (c) 2022-Today Kamil Rog
*
* Problem:
*
* 
*
* Solution:
*
* 
*
* References:
* https://stackoverflow.com/questions/11831/singletons-good-design-or-a-crutch
* https://stackoverflow.com/questions/86582/singleton-how-should-it-be-used
* https://code.google.com/archive/p/google-singleton-detector/wikis/WhySingletonsAreControversial.wiki 
* https://testing.googleblog.com/2008/08/by-miko-hevery-so-you-join-new-project.html
* https://testing.googleblog.com/2008/08/where-have-all-singletons-gone.html
* https://testing.googleblog.com/2008/08/root-cause-of-singletons.html
*/

class Singleton
{

    public:
    
        static Singleton& getInstance()
        {
            // Instantiated on first use
            static Singleton instance; 
            return instance;
        }
        
        // Make deleted function public for better error detection
        // Delete Copy Constructor
        Singleton(Singleton const&)         = delete;
        // Delete Copy Assignment 
        void operator=(Singleton const&)    = delete;

    private:

        /**
        * Hide default constructor
        */
        Singleton() {}

};
