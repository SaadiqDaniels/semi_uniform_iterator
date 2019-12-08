/*!
 * @file inheritance.h
 * @author Saadiq Daniels
 * @date 2/12/2019
 * @version 1.0
 * @brief
 *      Tests the functionality of the iterator classes with some simple
 *      inheritance objects and classes
 */

#ifndef TEMPL_ITERATOR_INHERITANCE_H
#define TEMPL_ITERATOR_INHERITANCE_H

/*!
 * The base class for all of the derived classes
 */
class base
{
  /*!
   * The number id given to this object during construction
   */
  int        _baseint;
  /*!
   * The number to keep track of baseint
   */
  static int number;
public:
  /*!
   * A virtual destructor
   */
  virtual ~base() = default;
  
  /*!
   * A function to return the floats in the base class
   * @return a float number
   */
  virtual float getfloat() const = 0;
  
  /*!
   * A non-const function for testing const correctness
   */
  virtual void doNothing() = 0;
  
  /*!
   * A const function for testing const correctness
   */
  virtual void doSomething() const = 0;
  
  /*!
   * A reference to the internally stored integer
   */
  const int &base_int;
protected:
  /*!
   * Default constructor for the derived classes to call
   */
  base()
    : _baseint(number++), base_int(_baseint)
  {}
};

/*!
 * The first derived class that inherits from base and becomes
 * inherited by derived3
 */
class derived1
  : public base
{
  /*!
   * The number returned from getfloat() and set
   * by the constructor
   */
  float _number;
public:
  /*!
   * Conversion constructor for the derived class
   * @param number the number to store in the _number float
   */
  derived1(float number)
    : base(), _number(number)
  {}
  
  /*!
   * Gets the number set during construction
   * @return _number value
   */
  float getfloat() const override
  {
    
    return _number;
  }
  
  /*!
   * Does nothing
   */
  virtual void doNothing() override
  {
    
    std::cout << "Derived 1 Do Nothing" << std::endl;
  }
  
  /*!
   * Does nothing (const)
   */
  void doSomething() const override
  {
    
    std::cout << "Derived 1 or 3 Do Something" << std::endl;
  }
};

/*!
 * The second derived class, inherits from base
 */
class derived2
  : public base
{
  /*!
   * The number returned by getfloat()
   *  and set by the constructor
   */
  float _other_number;
public:
  /*!
   * Constructor for derived2
   * @param number2 the number to set _other_number to
   */
  derived2(float number2)
    : base(), _other_number(number2 * 2.f)
  {}
  
  /*!
   * Returns the _other_number
   * @return _other_number
   */
  float getfloat() const override
  {
    
    return _other_number;
  }
  
  /*!
   * Does nothing
   */
  void doNothing() override
  {
    
    std::cout << "Derived 2 Do Nothing" << std::endl;
  }
  
  /*!
   * Does nothing (const)
   */
  void doSomething() const override
  {
    
    std::cout << "Derived 2 Do Something" << std::endl;
  }
};

/*!
 * The third derived class, inherits from derived1
 */
class derived3
  : public derived1
{
  /*!
   * Constructor for a derived3 that takes a float
   * @param newNum the number to place into derived1
   */
  derived3(float newNum)
    : derived1(newNum)
  {}

public:
  /*!
   * The default constructor for the third class
   */
  derived3()
    : derived1(300.f)
  {}
  
  /*!
   * The float stored in derived1
   * @return
   */
  float getfloat() const override
  {
    
    return derived1::getfloat();
  }
  
  /*!
   * Overridden doNothing function from derived 1
   */
  void doNothing() override
  {
    
    std::cout << "Derived 3 Do Nothing" << std::endl;
  }
  
  /*!
   * Assignment operator
   * @param rhs The derived 1 reference to assign to this object
   * @return A reference to the left hand side derived 3
   */
  base &operator=(derived1 &rhs)
  {
    
    new(this) derived3(rhs.getfloat());
    return *this;
  }
  
};

int base::number;

/*!
 * Print output operator for the base class
 * @param os The output stream to place the data into
 * @param data The data to print
 * @return The output stream
 */
std::ostream &operator<<(std::ostream &os, base &data)
{
  // Print the float with padding
  os << " " << data.getfloat() << " ";
  return os;
}

#endif //TEMPL_ITERATOR_INHERITANCE_H
