#pragma once

class Number {
private:
	double number;
public:
	Number();
	Number(double number);
	double getNumber();
	void setNumber(double number);
	Number operator+(const Number& number);
	Number operator-(const Number& number);
	Number operator*(const Number& number);
	Number operator/(const Number& number);
};
const Number ZERO = Number(0.0);
const Number ONE = Number(1.0);

Number createNumber(double number);
