/**
* @file builder.h
* MIT License 
* Copyright (c) 2022-Today Kamil Rog
*
* Builder creational pattern
*
* The Problem:
*
* Class (the same construction process) creating different representations of a complex object.
* Simplifying creation of an object containing complex objects.
*
* Solution:
*
* Encapsulate creating and assembling the parts of a complex object in a separate builder object.
*
* A class delegates object creation to a builder object instead of creating the objects directly.
*
* A class (the same construction process) can delegate to different Builder objects to create
* different representations of a complex object
*
*
* Notes:
*
* Compared to other creational patterns builder does not require products to have a common(base) interface.
* Therefore it allows to produce different products using the same construction process.
*
*/

#include <iostream>
#include <string>
#include <vector>

class Product1
{
    public:


        void ListParts() const
        {
            std::cout << "Product parts: ";
            for (size_t i = 0; i < m_parts.size(); i++)
            {
                if(m_parts[i] == m_parts.back())
                {
                    std::cout << m_parts[i];
                }
                else
                {
                    std::cout << m_parts[i] << ", ";
                }
            }
            std::cout << "\n\n"; 
        }

        std::vector<std::string> m_parts;
};


/**
 * The Builder base interface specifies functions for creating parts of
 * the product objects.
 */
class Builder
{
    public:
        virtual ~Builder(){}
        virtual void ProducePartA() const = 0;
        virtual void ProducePartB() const = 0;
        virtual void ProducePartC() const = 0;
};


/**
 * The Concrete Builder classes follow the Builder interface and provide
 * specific implementations of the building steps. Your program may have several
 * variations of Builders, implemented differently.
 */
class SpecializedBuilder1 : public Builder
{
    public:

    SpecializedBuilder1()
    {
        this->Reset();
    }

    ~SpecializedBuilder1()
    {
        delete m_product;
    }

    void Reset()
    {
        this->m_product = new Product1();
    }

    /**
     * All production steps work with the same product instance.
     */
    void ProducePartA() const override
    {
        this->m_product->m_parts.push_back("PartA1");
    }

    void ProducePartB() const override
    {
        this->m_product->m_parts.push_back("PartB1");
    }

    void ProducePartC() const override
    {
        this->m_product->m_parts.push_back("PartC1");
    }

    /**
     * Specialized Builders are supposed to provide their own methods for
     * retrieving results. That's because various types of builders may create
     * entirely different products that don't follow the same interface.
     * Therefore, such methods cannot be declared in the base Builder interface
     * (at least in a statically typed programming language).
     * 
     * Usually, after returning the end result to the client, a builder instance
     * is expected to be ready to start producing another product. That's why
     * it's a usual practice to call the reset method at the end of the
     * `getProduct` method body. However, this behavior is not mandatory, and
     * you can make your builders wait for an explicit reset call from the
     * client code before disposing of the previous result.
     */


    /**
     * Note on memory ownership:
     * Caller of GetProduct function is responsible for deallocating memory.
     * A better option could be to return smart pointer.
     */
    Product1* GetProduct()
    {
        Product1* result = this->m_product;
        this->Reset();
        return result;
    }

    private:

    /**
     * A fresh builder instance should contain a blank product object, which is
     * used in further assembly.
     */
    Product1* m_product;
};


/**
 * Director class is optional, it is only responsible for executing buliding process
 * in a specific sequence.
 */
class Director
{
    public:

    /**
     * The Director works with any builder instance that the client code passes
     * to it. This way, the client code may alter the final type of the newly
     * assembled product.
     */
    void SetBuilder(Builder* builder)
    {
        this->m_builder = builder;
    }

    /**
     * The Director can construct several product variations using the same
     * building steps.
     */
    void BuildMinimalProduct()
    {
        this->m_builder->ProducePartA();
    }
    
    void BuildFullProduct()
    {
        this->m_builder->ProducePartA();
        this->m_builder->ProducePartB();
        this->m_builder->ProducePartC();
    }

    private:

    Builder* m_builder;
};


/**
 * The client code creates a builder object, passes it to the director and then
 * initiates the construction process. The end result is retrieved from the
 * builder object.
 */
void ClientCode(Director& director)
{
    SpecializedBuilder1* builder = new SpecializedBuilder1();
    director.SetBuilder(builder);

    // Build minimal product
    std::cout << "Minimal product:\n"; 
    director.BuildMinimalProduct();
    Product1* p = builder->GetProduct();
    p->ListParts();
    delete p;

    // Build full product
    std::cout << "Full product:\n"; 
    director.BuildFullProduct();
    p = builder->GetProduct();
    p->ListParts();
    delete p;

    // Use builder object directly (without a director class).
    std::cout << "Custom product:\n";
    builder->ProducePartA();
    builder->ProducePartC();
    p = builder->GetProduct();
    p->ListParts();
    delete p;

    delete builder;
}

int main()
{
    Director* director = new Director();
    ClientCode(*director);
    delete director;
    return 0;    
}