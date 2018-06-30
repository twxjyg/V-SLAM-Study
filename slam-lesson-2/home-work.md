# 2 熟悉 Eigen 矩阵运算 (3 分,约 2 小时)

设线性方程 Ax = b,在 A 为方阵的前提下,请回答以下问题:

1. 在什么条件下,x 有解且唯一?

    A 满秩时x有唯一解
---
2. 高斯消元法的原理是什么?

    高斯消元法主要用于求解线性方程组，其基本步骤是：
    
    1. 求行列式矩阵的h行阶梯矩阵

    ```
    比如:线性方程组的矩阵表达：

        4 2 -9 | 3
        2 1 3  | 5
        5 2 1  | 2
    做如下转换：    
        R2 - 0.5*R1
        R3 - 1.25*R1
    得到：
        4  2   -9    | 3
        0 -0.5 12.25 | -1.75
        0  0   7.5   | 3.5

    ```

    2. s使用向后替换算法逐步求出所有解
    ```
        从R3开始计算然后将一个解带入R2，以此类推求出所有解
    ```
---
3. QR 分解的原理是什么?
---
4. Cholesky 分解的原理是什么?

    若 $A \in R^{n×n}$，R对称正定，则存在一个对角元素为正的下三角矩阵$L \in R^{n×n}$，使得$A = LL^{T}$成立。
    那么在求解线性方程组$Ax=b$,A对称正定,时就可以有如下步骤:
    1. 求A的Cholesky分解，得到：$A=LL^{T}$
    2. 求解$Ly=b$得到y
    3. 求解$L^{T}x=y$得到x

    那么现在关键的问题时如何对A进行Cholesky分解:
    假设:
    $
    L=
    \begin{vmatrix}
        l_{11}  &   0   &   ⋯   &   0 \\
        l_{21}  &   l_{22}  &   ⋯   &   0 \\
        ⋮   &  ⋮    &   ⋱   &   ⋮ \\
        l_{n1}  &   l_{n2}  &   ⋯   &   l_{nn}
    \end{vmatrix}
    L^{T}=\begin{vmatrix}
        l_{11}  &   l_{21}   &   ⋯   &   l_{n1} \\
        0  &   l_{22}  &   ⋯   &   l_{n2} \\
        ⋮   &  ⋮    &   ⋱   &   ⋮ \\
        0  &   0  &   ⋯   &   l_{nn}
    \end{vmatrix}$ 
    通过$A=LL^{T}$比较两边关系可得:
    $a_{11}=l_{11}^2 ⟹ l_{11} = \sqrt{a_{11}}$
    再由:
    $
    a_{i1} = l_{11}l_{i1} ⟹ l_{i1} = \dfrac {a_{i1}}{l_{11}}, 
    i \in (2,3,...,n)
    $
    这样就得到了矩阵$L$的第一列元素，假设已经算出了$L$的前$k-1$列的元素,通过：
    $
    a_{kk} = \sum_{i=1}^kl_{ki}^2 
    $
    $
    ⟹
    $
    $ 
    l_{kk} = \sqrt{a_{kk} - \sum_{i=1}^{k-1}l_{ki}^2}
    $
    $
    ⟹
    $
    $
    a_{ik} = \sum_{j=1}^{k-1}l_{ij}l_{kj} + l_{ik}l_{kk},i \in (k+1,…,n)
    $
    $
    ⟹
    $
    $
    l_{ik} = \dfrac{ a_{ik}-\sum_{j=1}^{k-1}l_{ij}l_{kj} }{ l_{kk} }, i \in (k+1, …, n)
    $
    这样便通过$L$的前$k-1$列求出了第$k$列,一直地推下去可求得$L$, 这种方法c称为平方更法。
---
5. 编程实现 A 为 100 × 100 随机矩阵时,用 QR 和 Cholesky 分解求 x 的程序。你可以参考本次课用到的 useEigen 例程。

```
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

```

---
# 3几何运算练习(2分，约1小时)

1. 下面我们来练习如何使用Eigen/Geometry计算一个具体的例子。

```
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
```

# 4 旋转的表达 (2 分,约 1 小时)

1. 设有旋转矩阵 $R$,证明 $R^TR = I$ 且 $det R = +1^{2}$

    解：
    $\because$旋转矩阵的定义为：$a' = Ra$ 那么我们也可以认为R是一组基向量:
    $
    (e1,e2,e3), e_i^Te_j=I(i=j)=
    \begin{cases}
        1, i=j \\
        0, i \not =j
    \end{cases}
    $
    $\therefore$
    $
    R^TR =
    \begin{vmatrix}
        e_1^T\\
        e_2^T\\
        e_3^T\\
    \end{vmatrix}
    \cdot
    \begin{vmatrix}
        e_1 && e_2 && e_3
    \end{vmatrix}=
    \begin{vmatrix}
        e_1^Te_1 && e_1^Te_2 && e_1^Te_3 \\
        e_2^Te_1 && e_2^Te_2 && e_2^Te_3 \\
        e_3^Te_1 && e_3^Te_2 && e_3^Te_3 \\
    \end{vmatrix}=
    \begin{vmatrix}
        1 && 0 && 0 \\
        0 && 1 && 0 \\
        0 && 0 && 1 \\
    \end{vmatrix} = I
    $
    $\because det(R^TR)=det(R^T)det(R)=det(R)^2=det(I)=1$
    $\therefore |det(R)|=+1$由定义有det(R)=I 

2. 设有四元数 q,我们把虚部记为 ε,实部记为 η,那么 q = (ε, η)。请说明 ε 和 η 的维度。
    $\because ε \in R^3, η \in R^1$
    $\therefore ε$的维度为3,$η$的维度为1
3. 证明 $ q_1 q_2 = q_1 ^ + q_2 = q_2^\oplus q_1 $
    $\because q_1^+q_2 = 
    \begin{vmatrix} 
        η_1I + ε_1^\times && ε_1 \\
        -ε_1^T           && η_1 \\   
    \end{vmatrix} \cdot
    \begin{vmatrix}
        ε_2 \\
        η_2 \\
    \end{vmatrix}=
    \begin{vmatrix}
        η_1ε_2 + ε_1^\timesε_2 + ε_1η_2 \\
        η_1η_2 - ε_1^Tε_2 \\
    \end{vmatrix} = q_1q_2
    $
    $\because q_2^\oplus q_1 =
    \begin{vmatrix} 
        η_2I - ε_2^\times && ε_2 \\
        -ε_2T           && η_2 \\   
    \end{vmatrix} \cdot
    \begin{vmatrix}
        ε_1 \\
        η_1 \\
    \end{vmatrix}=
     \begin{vmatrix}
        η_1ε_2 + ε_1^\timesε_2 + ε_1η_2 \\
        η_1η_2 - ε_1^Tε_2 \\
    \end{vmatrix} = q_1q_2
    $
    $\therefore q_1 q_2 = q_1 ^ + q_2 = q_2^\oplus q_1$

# 5 罗德里格斯公式的证明 (2 分,约 1 小时)
TODO
# 6 四元数运算性质的验证 (1 分,约 1 小时)
TODO
# 7 * 熟悉 C++11 (2 分,约 1 小时)
```
vector<A> avec{a1, a2, a3}; // 初始化列表
std::sort(avec.begin(), avec.end(), [](const A&a1, const A&a2) {return a1.index<a2.index;}); // lambda 表达式
for ( auto& a: avec ) cout<<a.index<<" "; // auto 类型自动推倒
```