#include <iostream>
#include <string>

using namespace std;

// Class to represent complex numbers with real and imaginary parts.
class Complex
{
public:
    // Constructor to initialize the complex number with real part 'a' and imaginary part 'b'.
    Complex(double a, double b) : _a(a), _b(b) {}

    // Converts the complex number to a string representation.
    // Returns the complex number in the form of "a+bi", "a-bi", or "a" (if b is 0).
    string to_string() const
    {
        if (_b == 0)
            return std::to_string(_a); // If imaginary part is zero, return only the real part.
        else
            return std::to_string(_a) + (_b > 0 ? "+" : "") + std::to_string(_b) + "i"; // Append "+" if b is positive.
    }

    // Overloads the stream insertion operator to output complex numbers directly.
    friend std::ostream &operator<<(std::ostream &os, const Complex &c);

    bool operator>(const Complex &other) const
    {
        return _a > other._a; // or include imaginary part comparison if needed
    }

private:
    double _a; // Real part of the complex number.
    double _b; // Imaginary part of the complex number.
};

// Implementation of the overloaded stream insertion operator.
// Outputs the complex number to the output stream in an appropriate format.
std::ostream &operator<<(std::ostream &os, const Complex &c)
{
    if (c._b == 0)
        os << c._a; // If the imaginary part is zero, output only the real part.
    else
        os << c._a << (c._b > 0 ? "+" : "") << c._b << "i"; // Append "+" if b is positive.
    return os;
}
