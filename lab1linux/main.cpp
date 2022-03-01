#include <iostream>
#include "Vector.h"
#include "Number.h"
int main() {
    Number one(1);
    Number three(3);
    Vector a(one,three);
    std::cout << a.calculatePolarAngle().getNumber()  << std::endl;
    std::cout << a.calculatePolarRadius().getNumber()  << std::endl;
    return 0;
}
