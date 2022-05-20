/**
* @file abstract-factory.h
* MIT License 
* Copyright (c) 2022-Today Kamil Rog
*
* The Problem:
*
* 
*
* Solution:
*
*
* Notes: Abstract Factories can be implemented as singletons.
*/

#include <string>
#include <iostream>

/**
 * Each distinct product of a product family must have a base interface.
 */
class AbstractProductA
{
    public:
        virtual ~AbstractProductA(){};
        //
        virtual std::string UsefulFunctionA() const = 0;
};

/**
 * Specialzed products are created by corresponding Concrete Factories.
 */
class SpecializedProductA1 : public AbstractProductA
{
    public:
        std::string UsefulFunctionA() const override
        {
            return "Output of the product A1";
        }
};

class SpecializedProductA2 : public AbstractProductA
{
    public:
        std::string UsefulFunctionA() const override 
        {
            return "Output of the product A2";
        }
};


/**
 * Base interface of another product, B. All products can interact
 * with each other, however, correct interaction is possible only between products of
 * the same specialized variant.
 */
class AbstractProductB
{
    public:
        virtual ~AbstractProductB(){};
        virtual std::string UsefulFunctionB() const = 0;

        /**
         * ...but it also can collaborate with the ProductA.
         *
         * The Abstract Factory makes sure that all products it creates are of the
         * same variant and thus, compatible.
         */
        virtual std::string ColaboratorFunctionB(const AbstractProductA &collaborator) const = 0;
};

/**
 * Specialized Products are created by corresponding Specialized Factories.
 */
class SpecializedProductB1 : public AbstractProductB
{
    public:
        std::string UsefulFunctionB() const override
        {
            return "Output of the product B1";
        }

        /**
         * Collaborator function B(1)
         * Accepts any instance of AbstractProductA as an input
         * parameter, however, it only executes correctly with product A2.
         */
        std::string ColaboratorFunctionB(const AbstractProductA &collaborator) const override 
        {
            const std::string result = collaborator.UsefulFunctionA();
            return "B1 collaborating with ( " + result + " )";
        }
};

class SpecializedProductB2 : public AbstractProductB
{
    public:
        std::string UsefulFunctionB() const override
        {
            return "Output of the product B2";
        }

        /**
         * Collaborator function B(2)
         * Accepts any instance of AbstractProductA as an input
         * parameter, however, it only executes correctly with product A2.
         */
        std::string ColaboratorFunctionB(const AbstractProductA &collaborator) const override
        {
            const std::string result = collaborator.UsefulFunctionA();
            return "B2 collaborating with ( " + result + " )";
        }
};

/**
 * The Abstract Factory interface declares a set of functions which return
 * different abstract products. These products are called a family and are
 * related by a high-level concept. Products of one family have ability
 * to collaborate with each other. A family of products could have numerous
 * variants, however the products of one variant are incompatible with products of
 * another variant.
 */
class AbstractFactory 
{
    public:
        virtual AbstractProductA *CreateProductA() const = 0;
        virtual AbstractProductB *CreateProductB() const = 0;
};

/**
 * Specialized Factories produce a family of products that belong to a single
 * variant. The factory ensures generated products are compatible.
 * Note the function signatures of the specialized Factory's function return an abstract product,
 * but the actual product returned is specialized.
 */
class SpecializedFactory1 : public AbstractFactory
{
    public:
        AbstractProductA *CreateProductA() const override
        {
            return new SpecializedProductA1();
        }

        AbstractProductB *CreateProductB() const override
        {
            return new SpecializedProductB1();
        }
};

/**
 * Each Concrete Factory has a corresponding product variant.
 */
class SpecializedFactory2 : public AbstractFactory 
{
    public:
        AbstractProductA *CreateProductA() const override
        {
            return new SpecializedProductA2();
        }

        AbstractProductB *CreateProductB() const override
        {
            return new SpecializedProductB2();
        }
};

/**
 * Use Factory
 * Utilize factories and products only through abstract
 * types: AbstractFactory and AbstractProduct. Allowing to work with 
 * any factory or product subclass.
 */

void UseFactory(const AbstractFactory &factory)
{
    // Create const product
    const AbstractProductA *product_a = factory.CreateProductA();
    const AbstractProductB *product_b = factory.CreateProductB();
    std::cout << product_b->UsefulFunctionB() << "\n";
    std::cout << product_b->ColaboratorFunctionB(*product_a) << "\n";
    delete product_a;
    delete product_b;
}

int main()
{
    std::cout << "Utilizing first factory type:\n";
    SpecializedFactory1 *f1 = new SpecializedFactory1();
    UseFactory(*f1);
    delete f1;
    std::cout << std::endl;
    std::cout << "Utilizing second factory type:\n";
    SpecializedFactory2 *f2 = new SpecializedFactory2();
    UseFactory(*f2);
    delete f2;
    return 0;
}