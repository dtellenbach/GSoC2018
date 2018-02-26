#ifndef GSOC_SYMMAT_H
#define GSOC_SYMMAT_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <ostream>
#include <algorithm>
#include <stdexcept>
#include <array>
#include "eigen3/Eigen/Eigen"

/**
 * \class SymmetricMatrix<typename Scalar, int Dimension = Eigen::Dimension>
 * \brief Generic class template for symmetric matrices
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
 * When a fixed dimension is chosen a lot of work can be done during compile-time
 * and all matrix elements are stored on stack. Fixed dimensions are therefore
 * only suitable for small matrices (a few hundred to a thousand elements). If
 * the dimension is set to Eigen::Dynamic (or not at all) all elements are stored
 * on the heap but all the work is done during runtime.
 */
template<typename Scalar, int Dimension = Eigen::Dynamic>
class SymmetricMatrix {
 public:
    /* Constructors */
    SymmetricMatrix(){}

    /**
     * \brief Construct SymmetricMatrix from Eigen::Matrix
     * 
     * Construct an instance of SymmetricMatrix with fixed dimension by passing
     * an instance of Eigen::Matrix with fixed dimension. This construction
     * is completely done at compile-time.
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

    /**
     * \brief Construct an Eigen::Matrix with fixed size from the current
     * instance of SymmetricMatrix
     * \return Eigen::Matrix that contains the same elements as SymmetricMatrix
     */
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

    /**
     * \brief Checks if a matrix of type Eigen::Matrix is symmetric or not.
     * \param mat Matrix of type Eigen::Matrix.
     * \return True if mat is symmetric, false otherwise
     */
    static bool
    isSymmetric(const Eigen::Matrix<Scalar, Dimension, Dimension>& mat) {
        return (mat == mat.transpose())?true:false;
    }

    /**
     * \brief Get a SymmetricMatrix with fixed dimension that is filled with
     * random values.
     * \return SymmetricMatrix filled with random values
     */
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
     * \return Reference to the element (row, col) of the matrix
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
     * \brief Operator << to push the elements of the matrix into an out-stream.
     * 
     * To print the matrix the operator << is overloaded. 
     * 
     * \param stream The out-stream
     * \param mat The matrix to push into stream
     */
    friend std::ostream&
    operator<<(std::ostream& stream, SymmetricMatrix<Scalar, Dimension>& mat) {
        for (int row = 0; row < Dimension; ++row) {
            for (int col = 0; col < Dimension; ++col) {
                stream << mat(row, col) << " ";
            }
            stream << ((row == Dimension - 1)?"":"\n");
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
        SymmetricMatrix<Scalar, Dimension> ret(elements);
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
            throw std::invalid_argument("Operation + cannot be performed "
                                        "for instances of SymmetricMatrix "
                                        "with not matching dimension");
        }

        // Construct new matrix and set underlying std::array
        SymmetricMatrix<Scalar, Dimension> ret(elements);

        // Just add up the underlying std::array and std::vector
        for (int i = 0; i < calcArraySize(); ++i) {
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
        SymmetricMatrix<Scalar, Dimension> ret(elements);

        // Just add up both underlying std::vector
        for (int i = 0; i < calcArraySize(); ++i) {
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
            throw std::invalid_argument("Operation + cannot be performed "
                                        "for instances of SymmetricMatrix "
                                        "with not matching dimension");
        }

        // Construct new matrix and set underlying std::array
        SymmetricMatrix<Scalar, Dimension> ret(elements);
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

        for (int i = 0; i < Dimension; ++i) {
            for (int j = i; j < Dimension; ++j) {
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
            throw std::invalid_argument("Operation + cannot be performed "
                                        "for an instance of SymmetricMatrix "
                                        "with argument of type Eigen::Matrix "
                                        "for not matching dimensions");
        }
        Eigen::Matrix<Scalar, Dimension, Dimension> ret;

        for (int i = 0; i < Dimension; ++i) {
            for (int j = i; j < Dimension; ++j) {
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

        for (int i = 0; i < Dimension; ++i) {
            for (int j = i; j < Dimension; ++j) {
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
            throw std::invalid_argument("Operation + cannot be performed "
                                        "for an instance of SymmetricMatrix "
                                        "with argument of type Eigen::Matrix "
                                        "for not matching dimensions");
        }
        Eigen::Matrix<Scalar, Dimension, Dimension> ret;

        for (int i = 0; i < Dimension; ++i) {
            for (int j = i; j < Dimension; ++j) {
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
    operator*(SymmetricMatrix<Scalar, Dimension>& other) {
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
    operator*(SymmetricMatrix<Scalar>& other) {
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

    SymmetricMatrix(const std::array<Scalar,
        (Dimension*Dimension+Dimension)/2>& arr) : elements(arr){}
    /**
     * Calculate size of the underlying std::array at compile-time
     */
    static constexpr int calcArraySize();
    std::array<Scalar, calcArraySize()> elements;
};

template<typename Scalar, int Dimension>
constexpr int SymmetricMatrix<Scalar, Dimension>::calcArraySize() {
    return (Dimension * Dimension + Dimension) / 2;
}

/**
 * \class SymmetricMatrix<Scalar, Eigen::Dynamic>
 * 
 * Partial template specialisation where Dimension = Eigen::Dynamic.
 * 
 * This class represents symmetric matrices with dynamic dimension, i.e, the
 * matrix dimension can be chosen and changes at runtime. This class is in
 * particular suitable for large matrices as the matrix elements are stored
 * an the heap.
 */
template<typename Scalar>
class SymmetricMatrix<Scalar, Eigen::Dynamic> {
 public:
    
    /**
     * \brief Default constructor that constructs a 0-dimensional symmetric matrix
     */
    SymmetricMatrix() : dimension(0) {}

    /**
     * \brief Constructor that reserves size for the underlying container
     * \param dimension Dimension of the matrix
     */
    SymmetricMatrix(size_t dimension) : dimension(dimension) {
        elements.reserve((dimension*dimension+dimension)/2);
    }

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
             throw std::invalid_argument("No instance of SymmetricMatrix can "
                                         "be constructed from non-square "
                                         "matrix of type Eigen::Matrix");
        }

        // Push upper triangular part of mat into the underlying std::vector
        for (int row = 0; row < dimension; row++) {
            for (int col = row; col < dimension; col++) {
                elements.push_back(mat(row, col));
            }
        }
    }

    /**
     * \brief Constructor that builds a symmetric matrix from a std::vector<T>.
     * \param vec std::vector<Scalar> that contains the elements of the upper
     * triangular part of the matrix
     */
    explicit SymmetricMatrix(const std::vector<Scalar>& vec) : elements(vec) {
        // Calculation of dimension
        dimension = (sqrt(1 + 8 * vec.size()) - 1) / 2;
    }

    /**
     * \brief Constructor that builds a symmetric matrix from a std::vector<T>.
     * \param vec std::vector<Scalar> that contains the elements of the upper
     * triangular part of the matrix
     * \param dimension The dimension of the matrix. It doesn't have to be
     * calculated.
     */
    SymmetricMatrix(const std::vector<Scalar>& vec, int dimension)
    : elements(vec), dimension(dimension) {}

    /**
     * \brief Checks if a matrix of type Eigen::Matrix is symmetric or not.
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
     * \brief Get a SymmetricMatrix with dynamic dimension that is filled with
     * random values.
     * \param dim Dimension of the dynamic matrix
     * \return SymmetricMatrix filled with random values
     */
    static SymmetricMatrix<Scalar>
    Random(int dim) {
        if (dim < 0) {
            throw std::invalid_argument("Cannot construct matrix with negative "
                                        "dimension");
        }
        return SymmetricMatrix<Scalar>(
            static_cast<Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>>(
                Eigen::Matrix<Scalar,
                              Eigen::Dynamic,
                              Eigen::Dynamic>::Random(dim, dim)));
    }

    /**
     * \brief Dimension of the symmetric matrix.
     *
     * Since any symmetric matrix is a square matrix no difference between
     * row-number and column-number has to be considered.
     * /return Dimension of the symmetric matrix.
     */
    size_t dim() const {
        return dimension;
    }

    /**
     * \brief Operator () to access a single element of the matrix
     * 
     * Overloaded operator () to access a single element of the current instance
     * of SymmetricMatrix.
     * 
     * \param row The row index of the element
     * \param col The column index of the element
     * \return Reference to the element (row, col) of the matrix
     */
    Scalar&
    operator()(int row, int col) {
        if (row <= col) {
            return elements[row * dimension - (row - 1)*((row - 1) + 1)/2
                            + col - row];
        } else {
            return elements[col * dimension - (col - 1)*((col - 1) + 1)/2
                            + row - col];
        }
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
    constructEigenMatrix() {
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
     * \brief Operator << to push the elements of the matrix into an out-stream.
     * 
     * To print the matrix the operator << is overloaded. 
     * 
     * \param stream The out-stream
     * \param mat The matrix to push into stream
     */
    friend std::ostream&
    operator<<(std::ostream& stream, SymmetricMatrix<Scalar>& mat) {
        for (int row = 0; row < mat.dim(); ++row) {
            for (int col = 0; col < mat.dim(); ++col) {
                stream << mat(row, col) << " ";
            }
            stream << ((row == mat.dim() - 1)?"":"\n");
        }
        return stream;
    }

    /**
     * \brief Overloaded operator + to add a SymmetricMatrix with dynamic dimension.
     * \param other Matrix to add
     * \return Sum of both matrices
     */
    SymmetricMatrix<Scalar>
    operator+(const SymmetricMatrix<Scalar>& other) {
        // Check if both dynamic dimensions match
        if (dimension != other.dim()) {
            throw std::invalid_argument("Operation + cannot be performed "
                                        "for instances of SymmetricMatrix "
                                        "with not matching dimension");
        }

        // Construct new matrix and set underlying std::vector
        SymmetricMatrix<Scalar> ret(elements);

        // Just add up both underlying std::vector
        for (int i = 0; i < elements.size(); ++i) {
           ret.elements[i] += other.elements[i];
        }
        return ret;
    }

    /**
     * \brief Overloaded operator - to subtract a SymmetricMatrix with dynamic dimension.
     * \param other Matrix to subtract
     * \return Difference of both matrices
     */
    SymmetricMatrix<Scalar>
    operator-(const SymmetricMatrix<Scalar>& other) {
        // Check if both dynamic dimensions match
        if (dimension != other.dim()) {
            throw std::invalid_argument("Operation + cannot be performed "
                                        "for instances of SymmetricMatrix "
                                        "with not matching dimension");
        }

        // Construct new matrix and set underlying std::vector
        SymmetricMatrix<Scalar> ret(elements);

        // Just add up both underlying std::vector
        for (int i = 0; i < elements.size(); ++i) {
           ret.elements[i] -= other.elements[i];
        }
        return ret;
    }

    /**
     * \brief Overloaded operator + to add an Eigen::Matrix with dynamic
     * dimension
     * \param other Matrix to add
     * \return Sum of both matrices
     */
    Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>
    operator+(const Eigen::Matrix<Scalar,
                                  Eigen::Dynamic, Eigen::Dynamic>& other) {
        // Check if dynamic dimension is equal to fixed one
        if (dimension != other.cols()) {
            throw std::invalid_argument("Operation + cannot be performed "
                                        "for an instance of SymmetricMatrix "
                                        "with argument of type Eigen::Matrix "
                                        "for not matching dimensions");
        }

        Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> ret(dimension, 
                                                                  dimension);

        for (int i = 0; i < dimension; ++i) {
            for (int j = i; j < dimension; ++j) {
                Scalar tmp = operator()(i, j);
                ret(i, j) = tmp + other(i, j);
                ret(j, i) = tmp + other(j, i);
            }
        }
        return ret;
    }

    /**
     * \brief Overloaded operator - to subtract an Eigen::Matrix with dynamic
     * dimension
     * \param other Matrix to subtract
     * \return Difference of both matrices
     */
    Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>
    operator-(const Eigen::Matrix<Scalar,
                                  Eigen::Dynamic, Eigen::Dynamic>& other) {
        // Check if dynamic dimension is equal to fixed one
        if (dimension != other.cols()) {
            throw std::invalid_argument("Operation + cannot be performed "
                                        "for an instance of SymmetricMatrix "
                                        "with argument of type Eigen::Matrix "
                                        "for not matching dimensions");
        }
        Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> ret(dimension,
                                                                dimension);

        for (int i = 0; i < dimension; ++i) {
            for (int j = i; j < dimension; ++j) {
                Scalar tmp = operator()(i, j);
                ret(i, j) = tmp - other(i, j);
                ret(j, i) = tmp - other(j, i);
            }
        }
        return ret;
    }

    /**
     * \brief Overloaded operator * to multiply an SymmetricMatrix with dynamic
     * dimension
     * \param other Matrix to multiply
     * \return Product of both matrices
     */
    Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>
    operator*(SymmetricMatrix<Scalar>& other) {
        return Eigen::Matrix<Scalar, Eigen::Dynamic,
                             Eigen::Dynamic>(constructEigenMatrix()
                                             * other.constructEigenMatrix());
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
    // This is necessary since the generic class template needs to access
    // private members of this partial specialized class template
    template<typename _Scalar, int _Dimension>
    friend class SymmetricMatrix;
    std::vector<Scalar> elements;
    size_t dimension;
};

/**
 * \brief SymmetricMatrix of ints with dynamic dimension
 */
typedef SymmetricMatrix<int, Eigen::Dynamic> SymmetricMatrixXi;
/**
 * \brief SymmetricMatrix of floats with dynamic dimension
 */
typedef SymmetricMatrix<float, Eigen::Dynamic> SymmetricMatrixXf;
/**
 * \brief SymmetricMatrix of doubles with dynamic dimension
 */
typedef SymmetricMatrix<double, Eigen::Dynamic> SymmetricMatrixXd;
/**
 * \typedef SymmetricMatrix of complex floats with dynamic dimension
 */
typedef SymmetricMatrix<std::complex<float>, Eigen::Dynamic> SymmetricMatrixXcf;
/**
 * \typedef SymmetricMatrix of complex doubles with dynamic dimension
 */
typedef SymmetricMatrix<std::complex<float>, Eigen::Dynamic> SymmetricMatrixXcd;
/**
 * \typedef SymmetricMatrix of ints with fixed dimension 2
 */
typedef SymmetricMatrix<int, 2> SymmetricMatrix2i;
/**
 * \typedef SymmetricMatrix of floats with fixed dimension 2
 */
typedef SymmetricMatrix<float, 2> SymmetricMatrix2f;
/**
 * \typedef SymmetricMatrix of doubles with fixed dimension 2
 */
typedef SymmetricMatrix<double, 2> SymmetricMatrix2d;
/**
 * \typedef SymmetricMatrix of complex floats with fixed dimension 2
 */
typedef SymmetricMatrix<std::complex<float>, 2> SymmetricMatrix2cf;
/**
 * \typedef SymmetricMatrix of complex doubles with fixed dimension 2
 */
typedef SymmetricMatrix<std::complex<double>, 2> SymmetricMatrix2cd;
/**
 * \typedef SymmetricMatrix of ints with fixed dimension 3
 */
typedef SymmetricMatrix<int, 3> SymmetricMatrix3i;
/**
 * \typedef SymmetricMatrix of floats with fixed dimension 3
 */
typedef SymmetricMatrix<float, 3> SymmetricMatrix3f;
/**
 * \typedef SymmetricMatrix of doubles with fixed dimension 3
 */
typedef SymmetricMatrix<double, 3> SymmetricMatrix3d;
/**
 * \typedef SymmetricMatrix of complex floats with fixed dimension 3
 */
typedef SymmetricMatrix<std::complex<float>, 3> SymmetricMatrix3cf;
/**
 * \typedef SymmetricMatrix of complex doubles with fixed dimension 3
 */
typedef SymmetricMatrix<std::complex<double>, 3> SymmetricMatrix3cd;
/**
 * \typedef SymmetricMatrix of ints with fixed dimension 4
 */
typedef SymmetricMatrix<int, 4> SymmetricMatrix4i;
/**
 * \typedef SymmetricMatrix of floats with fixed dimension 4
 */
typedef SymmetricMatrix<float, 4> SymmetricMatrix4f;
/**
 * \typedef SymmetricMatrix of doubles with fixed dimension 4
 */
typedef SymmetricMatrix<double, 4> SymmetricMatrix4d;
/**
 * \typedef SymmetricMatrix of complex floats with fixed dimension 4
 */
typedef SymmetricMatrix<std::complex<float>, 4> SymmetricMatrix4cf;
/**
 * \typedef SymmetricMatrix of complex doubles with fixed dimension 4
 */
typedef SymmetricMatrix<std::complex<double>, 4> SymmetricMatrix4cd;

#endif /* GSOC_SymmetricMatrix_H */
