/*!
 * @file inheritance.h
 * @author Saadiq Daniels
 * @date 2/12/2019
 * @version 0.8
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
    [[nodiscard]] virtual float getfloat() const = 0;

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
    base();
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
    derived1(float number);

    /*!
     * Gets the number set during construction
     * @return _number value
     */
    [[nodiscard]] float getfloat() const override;

    /*!
     * Does nothing
     */
    virtual void doNothing() override;

    /*!
     * Does nothing (const)
     */
    void doSomething() const override;
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
    derived2(float number2);

    /*!
     * Returns the _other_number
     * @return _other_number
     */
    [[nodiscard]] float getfloat() const override;

    /*!
     * Does nothing
     */
    void doNothing() override;

    /*!
     * Does nothing (const)
     */
    void doSomething() const;
};

/*!
 * The third derived class, inherits from derived1
 */
class derived3
        : public derived1
{
    /*!
     * COnstructor for a derived3 that takes a float
     * @param newNum the number to place into derived1
     */
    derived3(float newNum);

public:
    /*!
     * The default constructor for the third class
     */
    derived3();

    /*!
     * The float stored in derived1
     * @return
     */
    [[nodiscard]] float getfloat() const override;

    /*!
     * Overridden doNothing function from derived 1
     */
    void doNothing() const;

    /*!
     * Assignment operator
     * @param rhs The derived 1 reference to assign to this object
     * @return A reference to the left hand side derived 3
     */
    base &operator=(derived1 &rhs);

};


/*!
 * Print output operator for the base class
 * @param os The output stream to place the data into
 * @param data The data to print
 * @return The output stream
 */
std::ostream &operator<<(std::ostream &os, base &data);

#endif //TEMPL_ITERATOR_INHERITANCE_H
