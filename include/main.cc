#include <iostream>
#include "symmat.h"
#include <eigen3/Eigen/Eigen>

int main() {
    Eigen::Matrix<int, 4, 4> mat;

    mat << 1,2,3,4,
           2,2,3,2,
           3,3,3,1,
           4,2,1,4;



    
    
    SymMat<int, 4> sym(mat);

   

}