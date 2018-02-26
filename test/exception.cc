#include <iostream>
#include <SymmetricMatrix.h>
#include <eigen3/Eigen/Eigen>

int main() {
    int nExc = 13;
    int index = 1;
    // Construct symmetric matrix from non-square matrix
    try {
        Eigen::MatrixXi eigenmat = Eigen::MatrixXi::Random(4, 6);
        SymmetricMatrixXi symmat(eigenmat);
    } catch (std::exception& ex) {
        std::cout << "[" << index << "]" << "[Non-square construction]:\n  " 
                  << ex.what() << std::endl;
    }
    ++index;
    try {
        Eigen::MatrixXi eigenmat = Eigen::MatrixXi::Random(6, 4);
        SymmetricMatrixXi symmat(eigenmat);
    } catch (std::exception& ex) {
        std::cout << "[" << index << "]" << "[Non-square construction]:\n  " 
                  << ex.what() << std::endl;
    }
    ++index;
    // Add matrices of different dimension
    try {
        SymmetricMatrixXi symmat1 = SymmetricMatrixXi::Random(4);
        SymmetricMatrixXi symmat2 = SymmetricMatrixXi::Random(6);
        symmat1 + symmat2;
    } catch (std::exception& ex) {
        std::cout << "[" << index << "]" << "[Different dimension +]:\n  " 
                  << ex.what() << std::endl;
    }
    ++index;
    try {
        SymmetricMatrixXi symmat1 = SymmetricMatrixXi::Random(4);
        SymmetricMatrixXi symmat2 = SymmetricMatrixXi::Random(6);
        symmat2 + symmat1;
    } catch (std::exception& ex) {
        std::cout << "[" << index << "]" << "[Different dimension +]:\n  " 
                  << ex.what() << std::endl;
    }
    ++index;
    try {
        SymmetricMatrix4i symmat1 = SymmetricMatrix4i::Random();
        SymmetricMatrixXi symmat2 = SymmetricMatrixXi::Random(6);
        symmat1 + symmat2;
    } catch (std::exception& ex) {
        std::cout << "[" << index << "]" << "[Different dimension +]:\n  " 
                  << ex.what() << std::endl;
    }
    ++index;
    try {
        Eigen::Matrix4i eigenmat = Eigen::Matrix4i::Random();
        SymmetricMatrixXi symmat = SymmetricMatrixXi::Random(6);
        symmat + eigenmat;
    } catch (std::exception& ex) {
        std::cout << "[" << index << "]" << "[Different dimension +]:\n  " 
                  << ex.what() << std::endl;
    }
    ++index;
     try {
        Eigen::MatrixXi eigenmat = Eigen::MatrixXi::Random(4, 4);
        SymmetricMatrixXi symmat = SymmetricMatrixXi::Random(6);
        symmat - eigenmat;
    } catch (std::exception& ex) {
        std::cout << "[" << index << "]" << "[Different dimension +]:\n  " 
                  << ex.what() << std::endl;
    }
    ++index;
    // Subtract matrices of different dimension
    try {
        SymmetricMatrixXi symmat1 = SymmetricMatrixXi::Random(4);
        SymmetricMatrixXi symmat2 = SymmetricMatrixXi::Random(6);
        symmat1 - symmat2;
    } catch (std::exception& ex) {
        std::cout << "[" << index << "]" << "[Different dimension -]:\n  " 
                  << ex.what() << std::endl;
    }
    ++index;
    try {
        SymmetricMatrixXi symmat1 = SymmetricMatrixXi::Random(4);
        SymmetricMatrixXi symmat2 = SymmetricMatrixXi::Random(6);
        symmat2 - symmat1;
    } catch (std::exception& ex) {
        std::cout << "[" << index << "]" << "[Different dimension -]:\n  " 
                  << ex.what() << std::endl;
    }
    ++index;
    try {
        SymmetricMatrix4i symmat1 = SymmetricMatrix4i::Random();
        SymmetricMatrixXi symmat2 = SymmetricMatrixXi::Random(6);
        symmat1 - symmat2;
    } catch (std::exception& ex) {
        std::cout << "[" << index << "]" << "[Different dimension -]:\n  " 
                  << ex.what() << std::endl;
    }
    ++index;
    try {
        SymmetricMatrix4i symmat1 = SymmetricMatrix4i::Random();
        SymmetricMatrixXi symmat2 = SymmetricMatrixXi::Random(-1);
        symmat1 - symmat2;
    } catch (std::exception& ex) {
        std::cout << "[" << index << "]" << "[Different dimension -]:\n  " 
                  << ex.what() << std::endl;
    }
    ++index;
    try {
        Eigen::Matrix4i eigenmat = Eigen::Matrix4i::Random();
        SymmetricMatrixXi symmat = SymmetricMatrixXi::Random(6);
        symmat - eigenmat;
    } catch (std::exception& ex) {
        std::cout << "[" << index << "]" << "[Different dimension -]:\n  " 
                  << ex.what() << std::endl;
    }
    ++index;
    try {
        Eigen::MatrixXi eigenmat = Eigen::MatrixXi::Random(4, 4);
        SymmetricMatrixXi symmat = SymmetricMatrixXi::Random(6);
        symmat - eigenmat;
    } catch (std::exception& ex) {
        std::cout << "[" << index << "]" << "[Different dimension -]:\n  " 
                  << ex.what() << std::endl;
    }
    std::cout << "=> " << index << "/" << nExc << " exceptions caught.\n";
}