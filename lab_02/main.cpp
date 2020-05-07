#include "matrix.h"

int main() {
    size_t q = 2, z = 3;
    Matrix<int> a(q, z);
    Matrix<double> b;
    Matrix<double> c({ { 2., 3. }, { 3., 4. } });
    c.fill(c.begin(), c.end(), 2.22);
    for (const auto &elem: c)
        std::cout << elem << ' ';
    return 0;
}
