/**
 * Implementation file for the Complex Class
 */
#include "Complex.h"
#include <cmath>
#include <limits>
#include <iostream>

Complex::Complex(const double &value) :
	_real(value), _imaginary(0)
{}

Complex::Complex(const double &real, const double &imaginary) :
	_real(real), _imaginary(imaginary)
{}

const Complex Complex::conj() const {
	Complex res(_real, -_imaginary);
	return res;
}
const double Complex::getReal() const
{
	return _real;
}

const double Complex::getImaginary() const
{
	return _imaginary;
}

const Complex Complex::operator+(const Complex &other) const
{
	Complex result(_real+other._real, _imaginary+other._imaginary);
	return result;
}

Complex Complex::operator+=(const Complex &other) 
{
	_real += other._real;
	_imaginary += other._imaginary;
	return *this;
}

const Complex Complex::operator-(const Complex &other) const
{
	Complex result(_real-other._real, _imaginary-other._imaginary);
	return result;
}

Complex Complex::operator-=(const Complex &other) 
{
	_real -= other._real;
	_imaginary -= other._imaginary;
	return *this;
}

const Complex Complex::operator*(const Complex &other) const
{
	Complex result(_real*other._real - _imaginary*other._imaginary, _real*other._imaginary + _imaginary*other._real);
	return result;
}

std::ostream& operator<<(std::ostream &os, const Complex &number)
{
	if (number._imaginary < 0)
		os << number._real << " - " << fabs(number._imaginary) << "i";
	else
		os << number._real << " + " << number._imaginary << "i";
	return os;
}

const bool Complex::operator==(const Complex &other) const {
	 return (std::fabs(_real - other._real) < std::numeric_limits<double>::epsilon())
			 && (std::fabs(_imaginary - other._imaginary) < std::numeric_limits<double>::epsilon()) ;
}
const bool Complex::operator!=(const Complex &other) const {
	return !(*this == other);
}



