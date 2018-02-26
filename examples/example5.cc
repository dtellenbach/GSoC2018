/*******************************************************************************
 *  This file is part of the evaluation test of the Google Summer of Code 2018 *
 *  project "Faster Matrix Algebra for ATLAS".                                 *
 *                                                                             *
 *  David A. Tellenbach <tellenbach@cip.ifi.lmu.de>                            *
 *                                                                             *
 *  Example 5 - Error handling                                                 *
 *  Topics covered: > Runtime excpetions and compile-time errors               *
 ******************************************************************************/

#include <SymmetricMatrix.h>
#include <eigen3/Eigen/Eigen>
#include <iostream>
#include <cstdlib>  /* getenv() */

#define FORCE_FIXED_COMPILER_ERROR 0

int main() {
    // If an operation of matrices of different dynamic size is performed, a
    // runtime exception is thrown
    SymmetricMatrixXi dsymmat1 =  SymmetricMatrixXi::Random(2);
    SymmetricMatrixXi dsymmat2 =  SymmetricMatrixXi::Random(3);

    dsymmat1 + dsymmat2;      // will compile but will throw expection

    // If something similar is tried for matrices of fixed size, the compiler
    // will report an error. To try this change the defined value 
    // FORCE_FIXED_COMPILER_ERROR to 1

#if (FORCE_FIXED_COMPILER_ERROR)
        SymmetricMatrix2i ssymmat1 = SymmetricMatrix2i::Random();
        SymmetricMatrix3i ssymmat2 = SymmetricMatrix2i::Random();
        ssymmat1 + ssymat2;
#endif

}