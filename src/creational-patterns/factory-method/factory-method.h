/**
* @file factory-method.h
* MIT License 
* Copyright (c) 2022-Today Kamil Rog
*
* Factory Method
*
* The Problem:
*
*
* Solution:
*
* Factory Method pattern recommends to replace direct object
* construction calls via new operator with calls to factory method.
*
* The Factory method pattern defines interface for creating an object, but
* lets a class defer instantiation it uses to subclasses.
*
* Objects returned by a factory method are referred to as products.
*
* In essence the factory method design pattern circumvents the following
* limitations of C++ class constructors:
*
*
*   No return type - A constructor cannot return a result, which limits 
*   signalisation of an error during object initialization to throwing
*   an exception from a constructor.
*
*
*   Naming - A constructor must have the same name as the class, which means 
*   only one constructors with same a single argument.
*
*
*   Compile time bound - Upon object creation the name of specialized class must
*   be specified. There is no way of dynamic binding constructors at run time.
*
*
*   There is no virtual constructor - 
*
* In the example below
* 
*
* References:
*
* https://stackoverflow.com/questions/5120768/how-to-implement-the-factory-method-pattern-in-c-correctly
*
*
*/

#include <string>
#include <iostream>

/**
 * The product interface declares the operations which all specialized products must
 * implement, this is achieved by creating a purley virtual functions.
 */
class Product
{
 public:
  virtual ~Product() {}
  // Create purley virtual function by setting it to zero in the parent class
  virtual std::string Operation() const = 0;
};


/**
 * Specilized products provide specialized implementations of the product interface.
 */
class SpecilizedProduct1 : public Product
{
 public:
  std::string Operation() const override
  {
    return "{Output of the specilized product 1}";
  }
};

class SpecilizedProduct2 : public Product
{
 public:
  std::string Operation() const override
  {
    return "{Output of the specilized product 2}";
  }
};


/**
 * The Creator class declares the factory method that is responsible for return an
 * object of a Product class. The Creator's subclasses provide the
 * implementation of this method.
 */
class Creator
{

 public:
  virtual ~Creator(){};
  /**
   * Create factory method, purley virtual function, 
   * Note: Creator could also provide default implementation of the factory method.
   */
  virtual Product* FactoryMethod() const = 0;

  /**
   * The Creator's responsibility is not creating products, it contains logic which
   * relies on product objects returned by the factory methods. Subclasses can
   * indirectly modify this logic by overriding the factory method and
   * returning a different type of product from it.
   */
  std::string Operation() const
  {
    // Call the factory method to create a product object
    Product* product = this->FactoryMethod();
    // Use the product
    std::string result = "Creator: " + product->Operation();
    // Delete product
    delete product;
    // Return result string
    return result;
  }
};

/**
 * Specialized creators override the factory method in order to change the
 * resulting product's type.
 */
class SpecializedCreator1 : public Creator
{
  /**
   * Note the function still returns the abstract product type,
   * even though the specialized product is actually returned from the function. This
   * ensures creator is independent of specialized product classes.
   */
 public:
  Product* FactoryMethod() const override
  {
    return new SpecilizedProduct1();
  }
};

class SpecializedCreator2 : public Creator
{
 public:
  Product* FactoryMethod() const override
  {
    return new SpecilizedProduct2();
  }
};

/**
 * Use a specialized creator through its base interface.
 */
void UseCreator(const Creator& creator)
{
  std::cout << " Creator's class...\n" << creator.Operation() << std::endl;
}


int main()
{
    // Create specialized object 1 
    std::cout << "Using specialized creator 1...\n";
    // Instantiate specialized creator 1
    Creator* creator1 = new SpecializedCreator1();
    // Run clinet code using specialized creator 1 
    UseCreator(*creator1);

    
    std::cout << std::endl;

    // Create specialized object 2
    std::cout << "Using specialized creator 2...\n";
    // Instantiate specialized creator 2
    Creator* creator2 = new SpecializedCreator2();
    // Run clinet code using specialized creator 2
    UseCreator(*creator2);

    // Delete creators
    delete creator1;
    delete creator2;
    return 0;
}