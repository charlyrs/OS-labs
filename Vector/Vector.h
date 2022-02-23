#pragma once
#include "Number.h"
#include "cmath"

#ifdef VECTOR_EXPORTS
#define VECTOR_API __declspec(dllexport)
#else
#define VECTOR_API __declspec(dllimport)
#endif


class Vector {
private:
	Number x;
	Number y;
public:
	VECTOR_API Vector();
	VECTOR_API Vector(Number x, Number y);
	VECTOR_API Number calculatePolarRadius();
	VECTOR_API Number calculatePolarAngle();
	VECTOR_API Vector operator+(const Vector& vector);
};

const Vector VECTOR_ZERO = Vector(Number(0), Number(0));
const Vector VECTOR_ONE = Vector(Number(1), Number(1));