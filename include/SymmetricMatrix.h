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

/**
 * \class SymmetricMatrix
 * \brief Class for symmetric matrices
 * 
 * Class for handling symmetric matrices. Only the upper triangular part of the
 * matrix is stored. Interoperability with instances of type Eigen::Matrix is 
 * guaranteed by providing several constructors, operators and member functions.
 * 
 * The class SymmetricMatrix is in fact a class template that expects two 
 * template arguments: The type of the elements the matrix stores and the 
 * dimension of the matrix. However the dimension has the default value
 * Eigen::Dynamic.
 * 
 * When a fixed dimension is choosen a lot of work can be done during compiletime
 * and all matrix elements are stored on stack. Fixed dimensions are therefore
 * only suitable for small matrices (a few hundert to a tousand elements). If
 * the dimension is set to Eigen::Dynamic (or not at all) all elements are stored
 * on the heap but all the work is done during runtime.
 */
template<typename Scalar, int Dimension = Eigen::Dynamic>
class SymmetricMatrix {
 public:
    /* Constructors */

    /**
     * \brief Construct SymmetricMatrix from Eigen::Matrix
     * 
     * Construct an instance of SymmetricMatrix with fixed dimension by passing
     * an instance of Eigen::Matrix with fixed dimension. This construction
     * is completly done at compile-time.
     * 
     * \param mat Instance of Eigen::Matrix with fixed dimension
     */
    explicit SymmetricMatrix(const Eigen::Matrix<Scalar,
                                                 Dimension, Dimension>& mat) {
        int i = 0;
        for (int row = 0; row < Dimension; ++row) {
            for (int col = row; col < Dimension; ++col) {
                elements[i++] = mat(row, col);
            }
        }
    }

    /**
     * \brief Construct SymmetricMatrix from Eigen::Matrix
     * 
     * Construct an instance of SymmetricMatrix with fixed dimension by passing
     * an instance of Eigen::Matrix with dynamic dimension. 
     * 
     * \param mat Instance of Eigen::Matrix with dynamic dimension
     */
    SymmetricMatrix(const Eigen::Matrix<Scalar, Eigen::Dynamic,
                                        Eigen::Dynamic>& mat) {
        int i = 0;
        for (int row = 0; row < mat.rows(); ++row) {
            for (int col = row; col < mat.cols(); ++col) {
                elements[i++] = mat(row, col);
            }
        }
    }

    Eigen::Matrix<Scalar, Dimension, Dimension>
    constructEigenMatrix() {
        Eigen::Matrix<Scalar, Dimension, Dimension> ret;
        // Only loop through the upper triangular part
        for (int i = 0; i < Dimension; ++i) {
            for (int j = i; j < Dimension; ++j) {
                ret(i, j) = operator()(i, j);
                ret(j, i) = operator()(i, j);
            }
        }
        return ret;
    }

    static SymmetricMatrix<Scalar, Dimension>
    Random() {
        return SymmetricMatrix<Scalar, Dimension>(
            static_cast<Eigen::Matrix<Scalar, Dimension, Dimension>>(
                Eigen::Matrix<Scalar, Dimension, Dimension>::Random(Dimension, 
                                                                    Dimension)));
    }

    /* Overloaded operators */

    /**
     * \brief Operator () to access a single element of the matrix
     * 
     * Overloaded operator () to access a single element of the current instance
     * of SymmetricMatrix.
     * 
     * \param row The row index of the element
     * \param col The column index of the element
     * \return Reference to the elemenet (row, col) of the matrix
     */
    Scalar&
    operator()(int row, int col) {
        if (row <= col) {
            return elements[row * Dimension - (row - 1)*((row - 1) + 1)/2
                            + col - row];
        } else {
            return elements[col * Dimension - (col - 1)*((col - 1) + 1)/2
                            + row - col];
        }
    }

    /**
     * \brief Operator << to push the elements of the matrix into an outstream.
     * 
     * To print the matrix the operator << is overloaded. 
     * 
     * \param stream The outstream
     * \param mat The matrix to push into stream
     */
    friend std::ostream&
    operator<<(std::ostream& stream, SymmetricMatrix<Scalar, Dimension>& mat) {
        for (int row = 0; row < Dimension; ++row) {
            for (int col = 0; col < Dimension; ++col) {
                stream << mat(row, col) << " ";
            }
            stream << "\n";
        }
        return stream;
    }

    /**
     * \brief Overloaded operator + to add a SymmetricMatrix with fixed dimension.
     * \param other Matrix to add
     * \return Sum of both matrices
     */
    SymmetricMatrix<Scalar, Dimension>
    operator+(const SymmetricMatrix<Scalar, Dimension>& other) {
        // Construct new matrix and set underlying std::array
        SymmetricMatrix<Scalar, Dimension> ret(other);
        // Just add up both underlying std::vector
        for (int i = 0; i < elements.size(); ++i) {
           ret.elements[i] += other.elements[i];
        }
        return ret;
    }

    /**
     * \brief Overloaded operator + to add a SymmetricMatrix with dynamic dimension.
     * \param other Matrix to add
     * \return Sum of both matrices
     */
    SymmetricMatrix<Scalar, Dimension>
    operator+(const SymmetricMatrix<Scalar>& other) {
        // Check if dynamic dimension is equal to fixed one
        if (Dimension != other.dim()) {
            throw std::invalid_argument("Not matching dimension");
        }

        // Construct new matrix and set underlying std::array
        SymmetricMatrix<Scalar, Dimension> ret(other);
        // Just add up both underlying std::vector
        for (int i = 0; i < elements.size(); ++i) {
           ret.elements[i] += other.elements[i];
        }
        return ret;
    }

    /**
     * \brief Overloaded operator - to subtract a SymmetricMatrix with fixed dimension.
     * \param other Matrix to subtract
     * \return Difference of both matrices
     */
    SymmetricMatrix<Scalar, Dimension>
    operator-(const SymmetricMatrix<Scalar, Dimension>& other) {
        // Construct new matrix and set underlying std::array
        SymmetricMatrix<Scalar, Dimension> ret(other);
        // Just add up both underlying std::vector
        for (int i = 0; i < elements.size(); ++i) {
           ret.elements[i] -= other.elements[i];
        }
        return ret;
    }

    /**
     * \brief Overloaded operator - to subtract a SymmetricMatrix with dynamic dimension.
     * \param other Matrix to subtract
     * \return Difference of both matrices
     */
    SymmetricMatrix<Scalar, Dimension>
    operator-(const SymmetricMatrix<Scalar>& other) {
        // Check if dynamic dimension is equal to fixed one
        if (Dimension != other.dim()) {
            throw std::invalid_argument("Not matching dimension");
        }

        // Construct new matrix and set underlying std::array
        SymmetricMatrix<Scalar, Dimension> ret(other);
        // Just add up both underlying std::vector
        for (int i = 0; i < elements.size(); ++i) {
           ret.elements[i] -= other.elements[i];
        }
        return ret;
    }

   /**
     * \brief Overloaded operator + to add an Eigen::Matrix with fixed dimension.
     * \param other Matrix to subtract
     * \return Sum of both matrices
     */
    Eigen::Matrix<Scalar, Dimension, Dimension>
    operator+(const Eigen::Matrix<Scalar, Dimension, Dimension>& other) {
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

    /**
     * \brief Overloaded operator + to add an Eigen::Matrix with dynamic dimension.
     * \param other Matrix to add
     * \return Sum of both matrices
     */
    Eigen::Matrix<Scalar, Dimension, Dimension>
    operator+(const Eigen::Matrix<Scalar,
                                  Eigen::Dynamic, Eigen::Dynamic>& other) {
        // Check if dynamic dimension is equal to fixed one
        if (Dimension != other.cols()) {
            throw std::invalid_argument("Not matching dimension");
        }
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

    /**
     * \brief Overloaded operator - to subtract an Eigen::Matrix with fixed dimension.
     * \param other Matrix to subtract
     * \return Difference of both matrices
     */
    Eigen::Matrix<Scalar, Dimension, Dimension>
    operator-(const Eigen::Matrix<Scalar, Dimension, Dimension>& other) {
        Eigen::Matrix<Scalar, Dimension, Dimension> ret;

        for (int i = 0; i < Dimension; i++) {
            for (int j = i; j < Dimension; j++) {
                Scalar tmp = operator()(i, j);
                ret(i, j) = tmp - other(i, j);
                ret(j, i) = tmp - other(j, i);
            }
        }
        return ret;
    }

    /**
     * \brief Overloaded operator - to subtract an Eigen::Matrix with dynamic dimension.
     * \param other Matrix to subtract
     * \return Difference of both matrices
     */
    Eigen::Matrix<Scalar, Dimension, Dimension>
    operator-(const Eigen::Matrix<Scalar,
                                  Eigen::Dynamic, Eigen::Dynamic>& other) {
        // Check if dynamic dimension is equal to fixed one
        if (Dimension != other.cols()) {
            throw std::invalid_argument("Not matching dimension");
        }
        Eigen::Matrix<Scalar, Dimension, Dimension> ret;

        for (int i = 0; i < Dimension; i++) {
            for (int j = i; j < Dimension; j++) {
                Scalar tmp = operator()(i, j);
                ret(i, j) = tmp - other(i, j);
                ret(j, i) = tmp - other(j, i);
            }
        }
        return ret;
    }

    /**
     * \brief Overloaded operator * to multiply an SymmetricMatrix with fixed dimension
     * \param other Matrix to multiply
     * \return Product of both matrices
     */
    Eigen::Matrix<Scalar, Dimension, Dimension>
    operator*(const SymmetricMatrix<Scalar, Dimension>& other) {
        return Eigen::Matrix<Scalar, Eigen::Dynamic,
                             Eigen::Dynamic>(constructEigenMatrix()
                                             * other.constructEigenMatrix());
    }

    /**
     * \brief Overloaded operator * to multiply an SymmetricMatrix with dynamic dimension
     * \param other Matrix to multiply
     * \return Product of both matrices
     */
    Eigen::Matrix<Scalar, Dimension, Dimension>
    operator*(const SymmetricMatrix<Scalar>& other) {
        return Eigen::Matrix<Scalar, Eigen::Dynamic,
                             Eigen::Dynamic>(constructEigenMatrix()
                                             * other.constructEigenMatrix());
    }


    /**
     * \brief Overloaded operator * to multiply an Eigen::Matrix with fixed dimension
     * \param other Matrix to multiply
     * \return Product of both matrices
     */
    Eigen::Matrix<Scalar, Dimension, Dimension>
    operator*(const Eigen::Matrix<Scalar, Dimension, Dimension>& other) {
        return Eigen::Matrix<Scalar, Eigen::Dynamic,
                             Eigen::Dynamic>(constructEigenMatrix() * other);
    }

    /**
     * \brief Overloaded operator * to multiply an Eigen::Matrix with dynamic dimension
     * \param other Matrix to multiply
     * \return Product of both matrices
     */
    Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>
    operator*(const Eigen::Matrix<Scalar,
                                  Eigen::Dynamic, Eigen::Dynamic>& other) {
        return Eigen::Matrix<Scalar, Eigen::Dynamic,
                             Eigen::Dynamic>(constructEigenMatrix() * other);
    }

 private:
    /**
     * Calculate size of the underlying std::array at compiletime
     */
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
     * \brief Default constructor that constructs a 0-dimensional symmetric matrix
     */
    SymmetricMatrix() : dimension(0) {}

    /**
     * \brief Constructor that builds a symmetric matrix from an Eigen::Matrix
     * 
     * The Eigen::Matrix that is passed as an argument must be a square matrix and
     * have the template parameters Eigen::Dynamic
     * 
     * \param mat Instance of Eigen::Matrix
     */
    SymmetricMatrix(const Eigen::Matrix<Scalar,
                                        Eigen::Dynamic, Eigen::Dynamic>& mat)
    : dimension(mat.cols()) {
        // check if mat is a square matrix
        if (mat.cols() != mat.rows()) {
             throw std::invalid_argument("Not a square matrix");
        }

        // Push upper triangular part of mat into the underlying std::vector
        for (int row = 0; row < dimension; row++) {
            for (int col = row; col < dimension; col++) {
                elements.push_back(mat(row, col));
            }
        }
    }

    /**
     * Construtor that builds a symmetric matrix from a row major std::vector<T>.
     */
    explicit SymmetricMatrix(const std::vector<Scalar>& vec) : elements(vec) {
        // Calculation of dimension
        dimension = (sqrt(1 + 8 * vec.size()) - 1) / 2;
    }

    /**
     * Constructor that builds a symmetric matrix from a row major std::vector<T>.
     * The dimension is passed as an arguments and does not have to be calculated
     */
    SymmetricMatrix(const std::vector<Scalar>& vec, int dimension)
    : elements(vec), dimension(dimension) {}

    /**
     * \brief Checks if a matrix of type Eigen::Matrix is symmetric or not.
     *
     * \param mat Matrix of type Eigen::Matrix.
     * \return True if mat is symmetric, false otherwise
     */
    static bool
    isSymmetric(const Eigen::Matrix<Scalar,
                                    Eigen::Dynamic, Eigen::Dynamic>& mat) {
        // if mat is not square its not symmetric
        if (mat.cols() != mat.rows()) {
            return false;
        }
        // if mat is square we check if it is equal to the transposed matrix
        return (mat == mat.transpose())?true:false;
    }

    /**
     * \brief Dimension of the symmetric matrix.
     *
     * Since any symmetric matrix is a square matrix no difference between
     * row-number and column-number has to be considered.
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
            return elements[row * dimension - (row - 1 )* ((row - 1) + 1) / 2
                            + col - row];
        } else {
            return elements[col * dimension - (col - 1) * ((col - 1) + 1) / 2
                            + row - col];
        }
    }

    /**
     * \brief Operator +
     *
     * Overloaded operator + for addition of a symmetric matrix with
     * another symmetric matrix. Only the upper triangular part is taken into
     * account.
     * \param other The symmetric matrix to add with.
     * \return Sum of the matrices.
     */
    SymmetricMatrix<Scalar>
    operator+(const SymmetricMatrix<Scalar>& other) {
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
     * \brief Operator -
     *
     * Overloaded operator - for subtraction of a symmetric matrix with
     * another symmetric matrix. Only the upper triangular part is taken into
     * account.
     * \param other The symmetric matrix to subtract with.
     * \return Difference of both matrices.
     */
    SymmetricMatrix<Scalar>
    operator-(const SymmetricMatrix<Scalar>& other) {
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
     * \brief Operator +
     *
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
            for (int j = i; j < dimension; j++) {
                Scalar tmp = operator()(i, j);
                ret(i, j) = tmp + other(i, j);
                ret(j, i) = tmp + other(j, i);
            }
        }
        return ret;
    }

    /**
     * \brief Get Eigen::Matrix from SymmetricMatrix
     *
     * Construct a matrix of type Eigen::Matrix from a symmetric matrix. In 
     * particular the constructed Eigen::Matrix has dynamic dimensions.
     * 
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
     * \brief Operator *
     * 
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

        // Currently can't beat Eigens multiplication mechanism. Since the
        // product of a symmetric with an arbitrary matrix is not symmetric,
        // we just mutliply instances of Eigen::Matrix
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
     * \brief Operator << 
     *
     * Overloaded operator << to print the matrix in human friendly form.
     * \param stream Output stream
     * \param mat Matrix that is printed
     * \return Output stream with representation of matrix pushed on
     */
    friend std::ostream& operator<<(std::ostream& stream,
                                    SymmetricMatrix<Scalar>& mat) {
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
