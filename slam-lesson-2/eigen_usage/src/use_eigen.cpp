#include <iostream>
#include <eigen3/Eigen/Eigen>
#include <eigen3/Eigen/Cholesky>
#include <eigen3/Eigen/QR>

int main(int argc, char const *argv[])
{
    std::cout << "solve A*x=b use get inverse():" << std::endl;
    Eigen::Matrix<double, 100, 100> A;
    A = Eigen::MatrixXd::Random(100, 100);
    std::cout << "A:" << std::endl;
    std::cout << A << std::endl;
    Eigen::Matrix<double, 100, 1> b;
    b = Eigen::MatrixXd::Random(100, 1);
    std::cout << "b:" << std::endl;
    std::cout << b << std::endl;
    Eigen::Matrix<double, 100, 1> x = A.inverse() * b;
    std::cout << "x:" << std::endl;
    std::cout << x << std::endl;

    std::cout << "solve A*x=b by QR decomposition:" << std::endl;
    x = A.colPivHouseholderQr().solve(b);
    std::cout << "x:" << std::endl;
    std::cout << x << std::endl;
    
    std::cout << "solve A*x=b by Cholesky decomposition:" << std::endl;
    x = A.ldlt().solve(b);
    std::cout << "x:" << std::endl;
    std::cout << x << std::endl;
    
    return 0;
}
