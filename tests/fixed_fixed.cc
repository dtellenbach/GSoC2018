/*******************************************************************************
 *  This file is part of the evaluation test of the Google Summer of Code 2018 *
 *  project "Faster Matrix Algebra for ATLAS".                                 *
 *                                                                             *
 *  David A. Tellenbach <tellenbach@cip.ifi.lmu.de>                            *
 *                                                                             *
 * Test - Fixed Fixed                                                          *
 * Operations between instances of SymmetricMatrix of fixed size               *
*******************************************************************************/

#include <iostream>
#include <functional>

#include <SymmetricMatrix.h>
#include <eigen3/Eigen/Eigen>

/**
 * Addition of symmetric matrices of fixed size and symmetric matrix of dynamic
 * size
 */
template<typename Scalar, int Dimension>
int TEST_ADD_SYMF_SYMF(const Eigen::Matrix<Scalar, Dimension, Dimension>& mat1,
                       const Eigen::Matrix<Scalar, Dimension, Dimension>& mat2) {
    Eigen::Matrix<Scalar, Dimension, Dimension> res = mat1 + mat2;
    SymmetricMatrix<Scalar, Dimension> symmat1(mat1);
    SymmetricMatrix<Scalar, Dimension> symmat2(mat2);
    SymmetricMatrix<Scalar, Dimension> symres = symmat1 + symmat2;

    if (symres.constructEigenMatrix() == res) {
        return 0;
    }
    return 1;
}

/**
 * Subtraction of symmetric matrices of fixed size
 */
template<typename Scalar, int Dimension>
int TEST_SUB_SYMF_SYMF(const Eigen::Matrix<Scalar, Dimension, Dimension>& mat1,
                       const Eigen::Matrix<Scalar, Dimension, Dimension>& mat2) {
    Eigen::Matrix<Scalar, Dimension, Dimension> res = mat1 - mat2;
    SymmetricMatrix<Scalar, Dimension> symmat1(mat1);
    SymmetricMatrix<Scalar, Dimension> symmat2(mat2);
    SymmetricMatrix<Scalar, Dimension> symres = symmat1 - symmat2;

    if (symres.constructEigenMatrix() == res) {
        return 0;
    }
    return 1;
}

/**
 * Subtraction of symmetric matrices of fixed size
 */
template<typename Scalar, int Dimension>
int TEST_MULT_SYMF_SYMF(const Eigen::Matrix<Scalar, Dimension, Dimension>& mat1,
                       const Eigen::Matrix<Scalar, Dimension, Dimension>& mat2) {
    Eigen::Matrix<Scalar, Dimension, Dimension> res = mat1 * mat2;
    SymmetricMatrix<Scalar, Dimension> symmat1(mat1);
    SymmetricMatrix<Scalar, Dimension> symmat2(mat2);
    Eigen::Matrix<Scalar, Dimension, Dimension> symres = symmat1 * symmat2;

    if (symres == res) {
        return 0;
    }
    return 1;
}

/**
 * Make an instance of Eigen::Matrix symmetric
 */
template<typename Scalar, int Dimension>
void makeSymmetric(Eigen::Matrix<Scalar, Dimension, Dimension>& mat) {
    for (int i = 0; i < mat.rows(); ++i) {
        for (int j = i; j < mat.cols(); ++j) {
            mat(i, j) = mat(j, i);
        }
    }
}

template<typename Scalar, int Dimension>
int runTest(std::function<int (Eigen::Matrix<Scalar, Dimension, Dimension>,
                                Eigen::Matrix<Scalar,  Dimension, Dimension>)> func)
{
    Eigen::Matrix<Scalar, Dimension, Dimension> mat1 = 
    Eigen::Matrix<Scalar, Dimension, Dimension>::Random();
    Eigen::Matrix<Scalar, Dimension, Dimension> mat2 = 
    Eigen::Matrix<Scalar, Dimension, Dimension>::Random();
    makeSymmetric<Scalar, Dimension>(mat1);
    makeSymmetric<Scalar, Dimension>(mat2);
    if (!func(mat1, mat2)) {
        return 0;
    } else {
        return 1;
    }   
}

int main() {
    std::cout << "Testing addition...\n";
    std::cout << "[TEST_ADD_SYMF_SYMF][int][10]"
              << ((!runTest<int, 10>(TEST_ADD_SYMF_SYMF<int, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMF_SYMF][int][50]"
              << ((!runTest<int, 50>(TEST_ADD_SYMF_SYMF<int, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMF_SYMF][int][100]"
              << ((!runTest<int, 100>(TEST_ADD_SYMF_SYMF<int, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMF_SYMF][uint64_t][10]"
              << ((!runTest<uint64_t, 10>(TEST_ADD_SYMF_SYMF<uint64_t, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMF_SYMF][uint64_t][50]"
              << ((!runTest<uint64_t, 50>(TEST_ADD_SYMF_SYMF<uint64_t, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMF_SYMF][uint64_t][100]"
              << ((!runTest<uint64_t, 100>(TEST_ADD_SYMF_SYMF<uint64_t, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMF_SYMF][float][10]"
              << ((!runTest<float, 10>(TEST_ADD_SYMF_SYMF<float, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMF_SYMF][float][50]"
              << ((!runTest<float, 50>(TEST_ADD_SYMF_SYMF<float, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMF_SYMF][float][100]"
              << ((!runTest<float, 100>(TEST_ADD_SYMF_SYMF<float, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMF_SYMF][double][10]"
              << ((!runTest<double, 10>(TEST_ADD_SYMF_SYMF<double, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMF_SYMF][double][50]"
              << ((!runTest<double, 50>(TEST_ADD_SYMF_SYMF<double, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMF_SYMF][double][100]"
              << ((!runTest<double, 100>(TEST_ADD_SYMF_SYMF<double, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMF_SYMF][std::complex<int>][10]"
              << ((!runTest<std::complex<int>, 10>(TEST_ADD_SYMF_SYMF<std::complex<int>, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMF_SYMF][std::complex<int>][50]"
              << ((!runTest<std::complex<int>, 50>(TEST_ADD_SYMF_SYMF<std::complex<int>, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMF_SYMF][std::complex<int>][100]"
              << ((!runTest<std::complex<int>, 100>(TEST_ADD_SYMF_SYMF<std::complex<int>, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMF_SYMF][std::complex<double>][10]"
              << ((!runTest<std::complex<double>, 10>(TEST_ADD_SYMF_SYMF<std::complex<double>, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMF_SYMF][std::complex<double>][50]"
              << ((!runTest<std::complex<double>, 50>(TEST_ADD_SYMF_SYMF<std::complex<double>, 50>))?" => PASSED\n":" => FAIL\n");

    std::cout << "Testing subtraction...\n";
    std::cout << "[TEST_SUB_SYMF_SYMF][int][10]"
              << ((!runTest<int, 10>(TEST_SUB_SYMF_SYMF<int, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMF_SYMF][int][50]"
              << ((!runTest<int, 50>(TEST_SUB_SYMF_SYMF<int, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMF_SYMF][int][100]"
              << ((!runTest<int, 100>(TEST_SUB_SYMF_SYMF<int, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMF_SYMF][uint64_t][10]"
              << ((!runTest<uint64_t, 10>(TEST_SUB_SYMF_SYMF<uint64_t, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMF_SYMF][uint64_t][50]"
              << ((!runTest<uint64_t, 50>(TEST_SUB_SYMF_SYMF<uint64_t, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMF_SYMF][uint64_t][100]"
              << ((!runTest<uint64_t, 100>(TEST_SUB_SYMF_SYMF<uint64_t, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMF_SYMF][float][10]"
              << ((!runTest<float, 10>(TEST_SUB_SYMF_SYMF<float, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMF_SYMF][float][50]"
              << ((!runTest<float, 50>(TEST_SUB_SYMF_SYMF<float, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMF_SYMF][float][100]"
              << ((!runTest<float, 100>(TEST_SUB_SYMF_SYMF<float, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMF_SYMF][double][10]"
              << ((!runTest<double, 10>(TEST_SUB_SYMF_SYMF<double, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMF_SYMF][double][50]"
              << ((!runTest<double, 50>(TEST_SUB_SYMF_SYMF<double, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMF_SYMF][double][100]"
              << ((!runTest<double, 100>(TEST_SUB_SYMF_SYMF<double, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMF_SYMF][std::complex<int>][10]"
              << ((!runTest<std::complex<int>, 10>(TEST_SUB_SYMF_SYMF<std::complex<int>, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMF_SYMF][std::complex<int>][50]"
              << ((!runTest<std::complex<int>, 50>(TEST_SUB_SYMF_SYMF<std::complex<int>, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMF_SYMF][std::complex<int>][100]"
              << ((!runTest<std::complex<int>, 100>(TEST_SUB_SYMF_SYMF<std::complex<int>, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMF_SYMF][std::complex<double>][10]"
              << ((!runTest<std::complex<double>, 10>(TEST_SUB_SYMF_SYMF<std::complex<double>, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMF_SYMF][std::complex<double>][50]"
              << ((!runTest<std::complex<double>, 50>(TEST_SUB_SYMF_SYMF<std::complex<double>, 50>))?" => PASSED\n":" => FAIL\n");

    std::cout << "Testing multiplication...\n";
    std::cout << "[TEST_MULT_SYMF_SYMF][int][10]"
              << ((!runTest<int, 10>(TEST_MULT_SYMF_SYMF<int, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMF_SYMF][int][50]"
              << ((!runTest<int, 50>(TEST_MULT_SYMF_SYMF<int, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMF_SYMF][int][100]"
              << ((!runTest<int, 100>(TEST_MULT_SYMF_SYMF<int, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMF_SYMF][uint64_t][10]"
              << ((!runTest<uint64_t, 10>(TEST_MULT_SYMF_SYMF<uint64_t, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMF_SYMF][uint64_t][50]"
              << ((!runTest<uint64_t, 50>(TEST_MULT_SYMF_SYMF<uint64_t, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMF_SYMF][uint64_t][100]"
              << ((!runTest<uint64_t, 100>(TEST_MULT_SYMF_SYMF<uint64_t, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMF_SYMF][float][10]"
              << ((!runTest<float, 10>(TEST_MULT_SYMF_SYMF<float, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMF_SYMF][float][50]"
              << ((!runTest<float, 50>(TEST_MULT_SYMF_SYMF<float, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMF_SYMF][float][100]"
              << ((!runTest<float, 100>(TEST_MULT_SYMF_SYMF<float, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMF_SYMF][double][10]"
              << ((!runTest<double, 10>(TEST_MULT_SYMF_SYMF<double, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMF_SYMF][double][50]"
              << ((!runTest<double, 50>(TEST_MULT_SYMF_SYMF<double, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMF_SYMF][double][100]"
              << ((!runTest<double, 100>(TEST_MULT_SYMF_SYMF<double, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMF_SYMF][std::complex<int>][10]"
              << ((!runTest<std::complex<int>, 10>(TEST_MULT_SYMF_SYMF<std::complex<int>, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMF_SYMF][std::complex<int>][50]"
              << ((!runTest<std::complex<int>, 50>(TEST_MULT_SYMF_SYMF<std::complex<int>, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMF_SYMF][std::complex<int>][100]"
              << ((!runTest<std::complex<int>, 100>(TEST_MULT_SYMF_SYMF<std::complex<int>, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMF_SYMF][std::complex<double>][10]"
              << ((!runTest<std::complex<double>, 10>(TEST_MULT_SYMF_SYMF<std::complex<double>, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMF_SYMF][std::complex<double>][50]"
              << ((!runTest<std::complex<double>, 50>(TEST_MULT_SYMF_SYMF<std::complex<double>, 50>))?" => PASSED\n":" => FAIL\n");
}


