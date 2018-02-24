/******************************************************************************* 
 *  Google Summer of Code - Faster Matrix Multiplication for ATLAS             *
 *  David A. Tellenbach <tellenbach@cip.ifi.lmu.de> - 2018-02-20               *
 *                                                                             *
 *  Example 1 - Compile-time vs. runtime                                       *
 *  Topics covered: > Construct a symmetric matrix with fixed dimension        *
 *                  > Static assertion vs. runtime exception                   *
 ******************************************************************************/

#include <iostream>
#include "../include/SymmetricMatrix.h"
#include "../include/eigen3/Eigen/Eigen"

// #ifndef FORCE_STATIC_ASSERTION
// #define FORCE_STATIC_ASSERTION 1
// #endif

// #ifndef FORCE_RUNTIME_EXCEPTION
// #define FORCE_RUNTIME_EXCEPTION 1
// #endif

int main() {

    // Create two instances of SymmetricMatrix of dynamic dimension 3 and 4
    // containing random values
    SymmetricMatrix<int> dsymmat3 = SymmetricMatrix<int>::Random(3);
    SymmetricMatrix<int> dsymmat4 = SymmetricMatrix<int>::Random(4);

    
     // Create two instances of SymmetricMatrix of fixed dimension 3 and 4
    // containing random values
    SymmetricMatrix<int, 3> ssymmat3 = SymmetricMatrix<int, 3>::Random();
    SymmetricMatrix<int, 4> ssymmat4 = SymmetricMatrix<int, 4>::Random();

#if defined FORCE_STATIC_ASSERTION
    auto ret = ssymmat3 + ssymmat4;
#endif 

#if defined FORCE_RUNTIME_EXCEPTION
    auto ret = dsymmat3 + dsymmat4;
#endif

}