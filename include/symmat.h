#ifndef GSOC_SYMMAT_H
#define GSOC_SYMMAT_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <random>
#include <ostream>
#include <algorithm>
#include <stdexcept>
#include <array>
#include "eigen3/Eigen/Eigen"


template<typename Scalar, int Dimension = Eigen::Dynamic>
class SymmetricMatrix {

    public:
    /* Constructors */

    SymmetricMatrix(const Eigen::Matrix<Scalar, Dimension, Dimension>& mat) {
        int i = 0;
        for (int row = 0; row < Dimension; ++row) {
            for (int col = row; col < Dimension; ++col) {
                elements[i++] = mat(row,col);
            }
        }
    }

    /* Overloaded operators */
    Scalar& operator()(int row, int col) {
        if (row <= col) {
            return elements[row * Dimension - (row-1)*((row-1) + 1)/2 + col - row];
        } else {
            return elements[col * Dimension - (col-1)*((col-1) + 1)/2 + row - col];
        }
    }

    friend std::ostream& operator<<(std::ostream& stream, SymmetricMatrix<Scalar, Dimension>& mat) {
        for (int row = 0; row < Dimension; ++row) {
            for (int col = 0; col < Dimension; ++col) {
                stream << mat(row, col) << " ";
            }
            stream << "\n";
        }
        return stream;
    }

    SymmetricMatrix<Scalar, Dimension> operator+(const SymmetricMatrix<Scalar, Dimension>& other) {
        // Construct new matrix and set underlying std::array
        SymmetricMatrix<Scalar, Dimension> ret(other);
        // Just add up both underlying std::vector
        for (int i = 0; i < elements.size(); ++i) {
           ret.elements[i] += other.elements[i];
        }
        return ret;
    }

    Eigen::Matrix<Scalar, Dimension, Dimension> operator+(const Eigen::Matrix<Scalar, Dimension, Dimension>& other) {
        Eigen::Matrix<Scalar, Dimension, Dimension> ret;
    
        for (int i = 0; i < Dimension; i++) {
            for (int j = i; j < Dimension; j++) {
                Scalar tmp = operator()(i, j);
                ret(i, j) = tmp + other(i, j);
                ret(j, i) = tmp + other(j, i);
            }
        }
        return ret;
    }

    private:
    static constexpr int calcArraySize(); 
    std::array<Scalar, calcArraySize()> elements;  
};

template<typename Scalar, int Dimension>
constexpr int SymmetricMatrix<Scalar, Dimension>::calcArraySize() {
    return (Dimension * Dimension + Dimension) / 2;
}



/**
 * Partial template specialisation (Dimension = Eigen::Dynamic)
 */
template<typename Scalar>
class SymmetricMatrix<Scalar, Eigen::Dynamic> {
    public:
    /**
     * Default constructor that constructs and 0-dimensional symmetric matrix
     */
    SymmetricMatrix() : dimension(0) {};

    /**
     * Constructor that builds a symmetric matrix from an Eigen::Matrix
     */
    SymmetricMatrix(const Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>& mat) 
    : dimension (mat.cols()) {
        // check if mat is a square matrix
        if (mat.cols() != mat.rows()) {
             throw std::invalid_argument("Not a square matrix");
        }

        // Push upper triangular part of mat into the underlying std::vector
        for (int row = 0; row < dimension; row++) {
            for (int col = row; col < dimension; col++) {
                elements.push_back(mat(row,col));
            }
        }
    }

    /**
     * Construtor that builds a symmetric matrix from a row major std::vector<T>.
     */
    SymmetricMatrix(const std::vector<Scalar>& vec) : elements(vec) {
        // Calculation of dimension
        dimension = (sqrt(1+8*vec.size())-1)/2;
    }

    /**
     * Constructor that builds a symmetric matrix from a row major std::vector<T>.
     * The dimension is passed as an arguments and does not have to be calculated
     */
    SymmetricMatrix(const std::vector<Scalar>& vec, int dimension) : elements(vec),
                                                                     dimension(dimension)
                                                                     {}

    /**
     * Checks if a matrix of type Eigen::Matrix is symmetric or not.
     * \param mat Matrix of type Eigen::Matrix.
     * \return True if mat is symmetric, false otherwise
     */
    static bool isSymmetric(const Eigen::Matrix<Scalar, Eigen::Dynamic, 
                                                Eigen::Dynamic>& mat) {
        // if mat is not square its not symmetric
        if (mat.cols() != mat.rows()) {
            return false;
        }
        // if mat is square we check if it is equal to the transposed matrix
        return (mat == mat.transpose())?true:false;
    }
    
    /**
     * Dimension of the symmetric matrix.
     * /return Dimension of the symmetric matrix.
     */
    Eigen::Index dim() const {
        return dimension;
    }

    /**
     * Overloaded operator () to access elements of the matrix directly
     * \param row Row index 
     * \param col Column index
     * \retrun Matrix element at position (row, col)
     */
    Scalar operator()(int row, int col) const {
        if (row <= col) {
            return elements[row * dimension - (row-1)*((row-1) + 1)/2 + col - row];
        } else {
            return elements[col * dimension - (col-1)*((col-1) + 1)/2 + row - col];
        }
    }

    /**
     * Overloaded operator + for addition of a symmetric matrix with
     * another symmetric matrix. Only the upper triangular part is taken into
     * account.
     * \param other The symmetric matrix to add with.
     * \return Sum of the matrices.
     */
    SymmetricMatrix<Scalar> operator+(const SymmetricMatrix<Scalar>& other) {
        // Check if both dimensions match, if not throw exception (runtime case)
        if (dim() != other.dim()) {
            throw std::invalid_argument("Not matching dimension");
        }

        // Construct new matrix and set underlying std::vector
        SymmetricMatrix<Scalar> ret(elements, dimension);

        // Just add up both underlying std::vector
        for (int i = 0; i < elements.size(); ++i) {
           ret.elements[i] += other.elements[i];
        }
        return ret;
    }

    /**
     * Overloaded operator - for subtraction of a symmetric matrix with
     * another symmetric matrix. Only the upper triangular part is taken into
     * account.
     * \param other The symmetric matrix to subtract with.
     * \return Difference of both matrices.
     */
    SymmetricMatrix<Scalar> operator-(const SymmetricMatrix<Scalar>& other) {
        // Check if both dimensions match, if not throw exception (runtime case)
        if (dim() != other.dim()) {
            throw std::invalid_argument("Not matching dimension");
        }
        SymmetricMatrix<Scalar> ret(elements, dimension);
        int numElements = elements.size();
        for (int i = 0; i < numElements; ++i) {
           ret.elements[i] -= other.elements[i];
        }
        return ret;
    }

    /**
     * Overloaded operator + for addition of symmetric matrix with arbitrary 
     * matrix
     * \param other Matrix of type Eigen::Matrix
     * \return Sum of matrices
     */
    Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> 
    operator+(const Eigen::Matrix<Scalar, 
                                  Eigen::Dynamic, 
                                  Eigen::Dynamic>& other) {
        Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> ret;

        // Check if both dimensions match, if not throw exception (runtime case)
        if (dim() != other.dim()) {
            throw std::invalid_argument("Not matching dimension");
        }
        for (int i = 0; i < dimension; i++) {
            for (int j = 0; j < dimension; j++) {
                ret(i,j) = operator()(i,j) + other(i,j);
            }
        }
        return ret;
    }

    /**
     * Construct a matrix of type Eigen::Matrix from a symmetric matrix
     * \return Eigen::Matrix that contains the same elements as the
     * symmetric matrix
     */
    Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>  
    constructEigenMatrix() const {
        Eigen::Matrix<Scalar, 
                      Eigen::Dynamic, 
                      Eigen::Dynamic> ret(dimension, dimension);
        // Only loop through the upper triangular part
        for (int i = 0; i < dimension; ++i) {
            for (int j = i; j < dimension; ++j) {
                ret(i, j) = operator()(i, j);
                ret(j, i) = operator()(i, j);
            }
        }
        return ret;
    }

    /**
     * Overloaded operator * for multiplying to symmetric matrices. 
     * \param other Symmetric matrix to multiply with
     * \return Eigen::Matrix that is the product of both symmetric matrices
     */
    Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> 
    operator*(const SymmetricMatrix<Scalar>& other) {
        // Check if both dimensions match, if not throw exception (runtime case)
        if (dim() != other.dim()) {
            throw std::invalid_argument("Not matching dimension");
        }
        return Eigen::Matrix<Scalar, 
                             Eigen::Dynamic, 
                             Eigen::Dynamic>(constructEigenMatrix() 
                                             * other.constructEigenMatrix());
    }

    /**
     * Overloaded operator * to multiply an arbitrary matrix with a symmetric
     * matrix.
     * \param other Arbitrary matrix to multiply with
     * \return Product of the matrices
     */
    Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>
    operator*(const Eigen::Matrix<Scalar, 
                                  Eigen::Dynamic, 
                                  Eigen::Dynamic>& other) {
        // Check if both dimensions match, if not throw exception (runtime case)
        if (dim() != other.cols()) {
            throw std::invalid_argument("Not matching dimension");
        }
        return Eigen::Matrix<Scalar, 
                             Eigen::Dynamic, 
                             Eigen::Dynamic>(constructEigenMatrix() * other);
    }

    /**
     * Overloaded operator << to print the matrix in human friendly form.
     * \param stream Output stream
     * \param mat Matrix that is printed
     * \return Output stream with representation of matrix pushed on
     */
    friend std::ostream& operator<<(std::ostream& stream, SymmetricMatrix<Scalar>& mat) {
        for (int row = 0; row < mat.dim(); row++) {
            for (int col = 0; col < mat.dim(); col++) {
                stream << mat(row, col) << " ";
            }
            stream << "\n";
        }
        return stream;
    }

    private:
    std::vector<Scalar> elements;
    Eigen::Index dimension;
};



#endif /* GSOC_SymmetricMatrix_H */