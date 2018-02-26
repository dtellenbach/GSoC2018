#include <iostream>
#include <functional>

#include <SymmetricMatrix.h>
#include <eigen3/Eigen/Eigen>

/**
 * Addition of symmetric matrices of fixed size and symmetric matrix of dynamic
 * size
 */
template<typename Scalar, int Dimension>
int TEST_ADD_SYMD_SYMD(const Eigen::Matrix<Scalar, -1, -1>& mat1,
                       const Eigen::Matrix<Scalar, -1, -1>& mat2) {
    Eigen::Matrix<Scalar, -1, -1> res = mat1 + mat2;
    SymmetricMatrix<Scalar, -1> symmat1(mat1);
    SymmetricMatrix<Scalar, -1> symmat2(mat2);
    SymmetricMatrix<Scalar, -1> symres = symmat1 + symmat2;

    if (symres.constructEigenMatrix() == res) {
        return 0;
    }
    return 1;
}

/**
 * Subtraction of symmetric matrices of fixed size
 */
template<typename Scalar, int Dimension>
int TEST_SUB_SYMD_SYMD(const Eigen::Matrix<Scalar, -1, -1>& mat1,
                       const Eigen::Matrix<Scalar, -1, -1>& mat2) {
    Eigen::Matrix<Scalar, -1, Dimension> res = mat1 - mat2;
    SymmetricMatrix<Scalar, -1> symmat1(mat1);
    SymmetricMatrix<Scalar, -1> symmat2(mat2);
    SymmetricMatrix<Scalar, -1> symres = symmat1 - symmat2;

    if (symres.constructEigenMatrix() == res) {
        return 0;
    }
    return 1;
}

/**
 * Subtraction of symmetric matrices of fixed size
 */
template<typename Scalar, int Dimension>
int TEST_MULT_SYMD_SYMD(const Eigen::Matrix<Scalar, -1, -1>& mat1,
                       const Eigen::Matrix<Scalar, -1, -1>& mat2) {
    Eigen::Matrix<Scalar, -1, -1> res = mat1 * mat2;
    SymmetricMatrix<Scalar, -1> symmat1(mat1);
    SymmetricMatrix<Scalar, -1> symmat2(mat2);
    Eigen::Matrix<Scalar, -1, -1> symres = symmat1 * symmat2;

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
int runTest(std::function<int (Eigen::Matrix<Scalar, -1, -1>,
                                Eigen::Matrix<Scalar,  -1, -1>)> func)
{
    Eigen::Matrix<Scalar, -1, -1> mat1 = 
    Eigen::Matrix<Scalar, -1, -1>::Random(Dimension, Dimension);
    Eigen::Matrix<Scalar, -1, -1> mat2 = 
    Eigen::Matrix<Scalar, -1, -1>::Random(Dimension, Dimension);
    makeSymmetric<Scalar, -1>(mat1);
    makeSymmetric<Scalar, -1>(mat2);
    if (!func(mat1, mat2)) {
        return 0;
    } else {
        return 1;
    }   
}

int main() {
    std::cout << "Testing addition...\n";
    std::cout << "[TEST_ADD_SYMD_SYMD][int][10]"
              << ((!runTest<int, 10>(TEST_ADD_SYMD_SYMD<int, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMD_SYMD][int][50]"
              << ((!runTest<int, 50>(TEST_ADD_SYMD_SYMD<int, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMD_SYMD][int][100]"
              << ((!runTest<int, 100>(TEST_ADD_SYMD_SYMD<int, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMD_SYMD][int][1000]"
              << ((!runTest<int, 1000>(TEST_ADD_SYMD_SYMD<int, 1000>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMD_SYMD][uint64_t][10]"
              << ((!runTest<uint64_t, 10>(TEST_ADD_SYMD_SYMD<uint64_t, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMD_SYMD][uint64_t][50]"
              << ((!runTest<uint64_t, 50>(TEST_ADD_SYMD_SYMD<uint64_t, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMD_SYMD][uint64_t][100]"
              << ((!runTest<uint64_t, 100>(TEST_ADD_SYMD_SYMD<uint64_t, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMD_SYMD][uint64_t][1000]"
              << ((!runTest<uint64_t, 1000>(TEST_ADD_SYMD_SYMD<uint64_t, 1000>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMD_SYMD][float][10]"
              << ((!runTest<float, 10>(TEST_ADD_SYMD_SYMD<float, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMD_SYMD][float][50]"
              << ((!runTest<float, 50>(TEST_ADD_SYMD_SYMD<float, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMD_SYMD][float][100]"
              << ((!runTest<float, 100>(TEST_ADD_SYMD_SYMD<float, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMD_SYMD][float][1000]"
              << ((!runTest<float, 1000>(TEST_ADD_SYMD_SYMD<float, 1000>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMD_SYMD][double][10]"
              << ((!runTest<double, 10>(TEST_ADD_SYMD_SYMD<double, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMD_SYMD][double][50]"
              << ((!runTest<double, 50>(TEST_ADD_SYMD_SYMD<double, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMD_SYMD][double][100]"
              << ((!runTest<double, 100>(TEST_ADD_SYMD_SYMD<double, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMD_SYMD][double][1000]"
              << ((!runTest<double, 1000>(TEST_ADD_SYMD_SYMD<double, 1000>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMD_SYMD][std::complex<int>][10]"
              << ((!runTest<std::complex<int>, 10>(TEST_ADD_SYMD_SYMD<std::complex<int>, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMD_SYMD][std::complex<int>][50]"
              << ((!runTest<std::complex<int>, 50>(TEST_ADD_SYMD_SYMD<std::complex<int>, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMD_SYMD][std::complex<int>][100]"
              << ((!runTest<std::complex<int>, 100>(TEST_ADD_SYMD_SYMD<std::complex<int>, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMD_SYMD][std::complex<double>][10]"
              << ((!runTest<std::complex<double>, 10>(TEST_ADD_SYMD_SYMD<std::complex<double>, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMD_SYMD][std::complex<double>][50]"
              << ((!runTest<std::complex<double>, 50>(TEST_ADD_SYMD_SYMD<std::complex<double>, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMD_SYMD][std::complex<double>][100]"
              << ((!runTest<std::complex<double>, 100>(TEST_ADD_SYMD_SYMD<std::complex<double>, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_ADD_SYMD_SYMD][std::complex<double>][1000]"
              << ((!runTest<std::complex<double>, 1000>(TEST_ADD_SYMD_SYMD<std::complex<double>, 1000>))?" => PASSED\n":" => FAIL\n");

    std::cout << "Testing subtraction...\n";
    std::cout << "[TEST_SUB_SYMD_SYMD][int][10]"
              << ((!runTest<int, 10>(TEST_SUB_SYMD_SYMD<int, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMD_SYMD][int][50]"
              << ((!runTest<int, 50>(TEST_SUB_SYMD_SYMD<int, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMD_SYMD][int][100]"
              << ((!runTest<int, 100>(TEST_SUB_SYMD_SYMD<int, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMD_SYMD][int][1000]"
              << ((!runTest<int, 1000>(TEST_SUB_SYMD_SYMD<int, 1000>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMD_SYMD][uint64_t][10]"
              << ((!runTest<uint64_t, 10>(TEST_SUB_SYMD_SYMD<uint64_t, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMD_SYMD][uint64_t][50]"
              << ((!runTest<uint64_t, 50>(TEST_SUB_SYMD_SYMD<uint64_t, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMD_SYMD][uint64_t][100]"
              << ((!runTest<uint64_t, 100>(TEST_SUB_SYMD_SYMD<uint64_t, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMD_SYMD][uint64_t][1000]"
              << ((!runTest<uint64_t, 1000>(TEST_SUB_SYMD_SYMD<uint64_t, 1000>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMD_SYMD][float][10]"
              << ((!runTest<float, 10>(TEST_SUB_SYMD_SYMD<float, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMD_SYMD][float][50]"
              << ((!runTest<float, 50>(TEST_SUB_SYMD_SYMD<float, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMD_SYMD][float][100]"
              << ((!runTest<float, 100>(TEST_SUB_SYMD_SYMD<float, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMD_SYMD][float][1000]"
              << ((!runTest<float, 1000>(TEST_SUB_SYMD_SYMD<float, 1000>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMD_SYMD][double][10]"
              << ((!runTest<double, 10>(TEST_SUB_SYMD_SYMD<double, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMD_SYMD][double][50]"
              << ((!runTest<double, 50>(TEST_SUB_SYMD_SYMD<double, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMD_SYMD][double][100]"
              << ((!runTest<double, 100>(TEST_SUB_SYMD_SYMD<double, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMD_SYMD][double][1000]"
              << ((!runTest<double, 1000>(TEST_SUB_SYMD_SYMD<double, 1000>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMD_SYMD][std::complex<int>][10]"
              << ((!runTest<std::complex<int>, 10>(TEST_SUB_SYMD_SYMD<std::complex<int>, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMD_SYMD][std::complex<int>][50]"
              << ((!runTest<std::complex<int>, 50>(TEST_SUB_SYMD_SYMD<std::complex<int>, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMD_SYMD][std::complex<int>][100]"
              << ((!runTest<std::complex<int>, 100>(TEST_SUB_SYMD_SYMD<std::complex<int>, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMD_SYMD][std::complex<double>][10]"
              << ((!runTest<std::complex<double>, 10>(TEST_SUB_SYMD_SYMD<std::complex<double>, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMD_SYMD][std::complex<double>][50]"
              << ((!runTest<std::complex<double>, 50>(TEST_SUB_SYMD_SYMD<std::complex<double>, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMD_SYMD][std::complex<double>][100]"
              << ((!runTest<std::complex<double>, 100>(TEST_SUB_SYMD_SYMD<std::complex<double>, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_SUB_SYMD_SYMD][std::complex<double>][1000]"
              << ((!runTest<std::complex<double>, 1000>(TEST_SUB_SYMD_SYMD<std::complex<double>, 1000>))?" => PASSED\n":" => FAIL\n");

    std::cout << "Testing multiplication...\n";
    std::cout << "[TEST_MULT_SYMD_SYMD][int][10]"
              << ((!runTest<int, 10>(TEST_MULT_SYMD_SYMD<int, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMD_SYMD][int][50]"
              << ((!runTest<int, 50>(TEST_MULT_SYMD_SYMD<int, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMD_SYMD][int][100]"
              << ((!runTest<int, 100>(TEST_MULT_SYMD_SYMD<int, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMD_SYMD][int][1000]"
              << ((!runTest<int, 1000>(TEST_MULT_SYMD_SYMD<int, 1000>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMD_SYMD][uint64_t][10]"
              << ((!runTest<uint64_t, 10>(TEST_MULT_SYMD_SYMD<uint64_t, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMD_SYMD][uint64_t][50]"
              << ((!runTest<uint64_t, 50>(TEST_MULT_SYMD_SYMD<uint64_t, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMD_SYMD][uint64_t][100]"
              << ((!runTest<uint64_t, 100>(TEST_MULT_SYMD_SYMD<uint64_t, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMD_SYMD][uint64_t][1000]"
              << ((!runTest<uint64_t, 1000>(TEST_MULT_SYMD_SYMD<uint64_t, 1000>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMD_SYMD][float][10]"
              << ((!runTest<float, 10>(TEST_MULT_SYMD_SYMD<float, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMD_SYMD][float][50]"
              << ((!runTest<float, 50>(TEST_MULT_SYMD_SYMD<float, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMD_SYMD][float][100]"
              << ((!runTest<float, 100>(TEST_MULT_SYMD_SYMD<float, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMD_SYMD][float][1000]"
              << ((!runTest<float, 1000>(TEST_MULT_SYMD_SYMD<float, 1000>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMD_SYMD][double][10]"
              << ((!runTest<double, 10>(TEST_MULT_SYMD_SYMD<double, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMD_SYMD][double][50]"
              << ((!runTest<double, 50>(TEST_MULT_SYMD_SYMD<double, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMD_SYMD][double][100]"
              << ((!runTest<double, 100>(TEST_MULT_SYMD_SYMD<double, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMD_SYMD][double][1000]"
              << ((!runTest<double, 1000>(TEST_MULT_SYMD_SYMD<double, 1000>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMD_SYMD][std::complex<int>][10]"
              << ((!runTest<std::complex<int>, 10>(TEST_MULT_SYMD_SYMD<std::complex<int>, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMD_SYMD][std::complex<int>][50]"
              << ((!runTest<std::complex<int>, 50>(TEST_MULT_SYMD_SYMD<std::complex<int>, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMD_SYMD][std::complex<int>][100]"
              << ((!runTest<std::complex<int>, 100>(TEST_MULT_SYMD_SYMD<std::complex<int>, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMD_SYMD][std::complex<double>][10]"
              << ((!runTest<std::complex<double>, 10>(TEST_MULT_SYMD_SYMD<std::complex<double>, 10>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMD_SYMD][std::complex<double>][50]"
              << ((!runTest<std::complex<double>, 50>(TEST_MULT_SYMD_SYMD<std::complex<double>, 50>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMD_SYMD][std::complex<double>][100]"
              << ((!runTest<std::complex<double>, 100>(TEST_MULT_SYMD_SYMD<std::complex<double>, 100>))?" => PASSED\n":" => FAIL\n");
    std::cout << "[TEST_MULT_SYMD_SYMD][std::complex<double>][1000]"
              << ((!runTest<std::complex<double>, 1000>(TEST_MULT_SYMD_SYMD<std::complex<double>, 1000>))?" => PASSED\n":" => FAIL\n");
}


