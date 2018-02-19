#ifndef GSOC_SYMMAT_H
#define GSOC_SYMMAT_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <random>
#include "eigen3/Eigen/Eigen"


template<typename Scalar, int Dimension>
class SymMat {
    public:

    SymMat(){};

    /**
     * Constructor that builds a symmetric matrix from an Eigen::Matrix
     */
    SymMat(Eigen::Matrix<Scalar, Dimension, Dimension>& mat) {
        for (int row = 0; row < Dimension; row++) {
            for (int col = row; col < Dimension; col++) {
                _elements.push_back(mat(row,col));
            }
        }
    }

    void randInit() {
        std::random_device rd;
        std::mt19937 mt(rd);
    }

    static bool isSymmetric(Eigen::Matrix<Scalar, Dimension, Dimension>& mat) {
        return (mat == mat.transpose())?true:false;
    }

    
    Scalar operator()(int row, int col) {
        if (row <= col) {
            return _elements[row * Dimension - (row-1)*((row-1) + 1)/2 + col - row];
        } else {
            return _elements[col * Dimension - (col-1)*((col-1) + 1)/2 + row - col];
        }
    }

    
    SymMat<Scalar, Dimension> operator+(SymMat<Scalar, Dimension> &other) {
        SymMat<Scalar, Dimension> ret;
        for (int i = 0; i < Rows; i++) {
            for (int j = 0; j < Cols; j++) {
                ret(i, j) = this->operator()(i, j) + other(i,j);
            }
        }
        return ret;
    }


   
    private:
    std::vector<Scalar> _elements;
};

#endif /* GSOC_SYMMAT_H */