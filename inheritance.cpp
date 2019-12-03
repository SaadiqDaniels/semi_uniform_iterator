/*!
 * @file inheritance.cpp
 * @author Saadiq Daniels
 * @date 2/12/2019
 * @version 0.8
 */

#include <iostream>

#include "inheritance.h"

namespace inherit
{
    int base::number = 0;

    base::base()
            : _baseint(number++), base_int(_baseint)
    {
    }

    derived1::derived1(float number)
            : base(), _number(number)
    {
    }

    float derived1::getfloat() const
    {
        return _number;
    }

    void derived1::doNothing()
    {
        std::cout << "Derived 1 Do Nothing" << std::endl;
    }

    void derived1::doSomething() const
    {
        std::cout << "Derived 1 or 3 Do Something" << std::endl;
    }

    derived2::derived2(float number2)
            : base(), _other_number(number2 * 2.f)
    {
    }

    float derived2::getfloat() const
    {
        return _other_number;
    }

    void derived2::doNothing()
    {
        std::cout << "Derived 2 Do Nothing" << std::endl;
    }

    void derived2::doSomething() const
    {
        std::cout << "Derived 2 Do Something" << std::endl;
    }

    derived3::derived3()
            : derived1(300.f)
    {

    }

    float derived3::getfloat() const
    {
        return derived1::getfloat();
    }

    void derived3::doNothing() const
    {
        std::cout << "Derived 3 Do Nothing" << std::endl;
    }

    base &derived3::operator=(derived1 &rhs)
    {
        new (this) derived3(rhs.getfloat());
        return *this;
    }

    derived3::derived3(float newNum)
            : derived1(newNum)
    {
    }
}

std::ostream &operator<<(std::ostream &os, inherit::base &data)
{
    // Print the float with padding
    os << " " << data.getfloat() << " ";
    return os;
}
