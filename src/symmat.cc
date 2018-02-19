#include "../include/symmat.h"

SymMat::SymMat(Eigen::Matrix<Scalar, Rows, Cols>& mat){
    for (int row = 0; row < Dimension; row++) {
        for (int col = row; col < Dimension; col++) {
            _elements.push_back(mat[row][col]);
        }
    }
}

bool SymMat::isSymmetric(Eigen::Matrix<Scalar, Rows, Cols>& mat) {
    return (mat == mat.transpose())?true:false;
}

std::string SymMat::print() {
    for (int row = 0; row < Dimension; row++) {
        
    }
}
