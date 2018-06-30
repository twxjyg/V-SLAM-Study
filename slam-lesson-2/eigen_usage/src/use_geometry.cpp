#include <eigen3/Eigen/Geometry>
#include <iostream>

int main(int argc, char const *argv[])
{
    Eigen::Quaterniond q1(0.55, 0.3, 0.2, 0.2);
    q1.normalize();
    Eigen::Vector3d t1(0.7, 1.1, 0.2);

    Eigen::Quaterniond q2(-0.1, 0.3, -0.7, 0.2);
    q2.normalize();
    Eigen::Vector3d t2(-0.1, 0.4, 0.8);

    Eigen::Vector3d p1(0.5, -0.1, 0.2);


    // p1 = R1 * w + t1
    // p2 = R2 * w + t2
    // w = R1.inverse() * (p1 - t1)
    // p2 = R2 * (R1.inverse() * (p1 - t1)) + t2

    Eigen::Vector3d p2 = q2.matrix() * (q1.matrix().inverse() * (p1 - t1)) + t2;
    std::cout << "p2:" << p2.transpose() << std::endl;

    return 0;
}
