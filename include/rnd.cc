#include <iostream>
#include "SymmetricMatrix.h"

int main() {
    SymmetricMatrix<std::complex<int>, 3> symmat = SymmetricMatrix<std::complex<int>, 3>::Random();

    std::cout << symmat;
}