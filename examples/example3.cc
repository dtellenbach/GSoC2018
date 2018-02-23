/******************************************************************************* 
 *  Google Summer of Code - Faster Matrix Multiplication for ATLAS             *
 *  David A. Tellenbach <tellenbach@cip.ifi.lmu.de> - 2018-02-20               *
 *                                                                             *
 *  Example 1 - Compile-time vs. runtime                                       *
 *  Topics covered: > Construct a symmetric matrix with fixed dimension        *
 *                  > Static assertion vs. runtime exception                   *
 ******************************************************************************/

#include <iostream>
#include "../include/symmat.h"
#include "../include/eigen3/Eigen/Eigen"

#ifndef FORCE_STATIC_ASSERTION
#define FORCE_STATIC_ASSERTION 1
#endif

#ifndef FORCE_RUNTIME_EXCEPTION
#define FORCE_RUNTIME_EXCEPTION 1
#endif

int main() {


}