#include "matrix.hpp"

int main() {
    size_t q = 2, z = 3;

    Matrix<int> a(q, z);
    Matrix<double> b;
    Matrix<double> c({ { 2., 3. }, { 3., 4. } });

    c.fill(c.begin(), c.end(), 2.22);

    auto it = c.begin();
    auto it2 = it + q;
    it2 += 2;

    for (const auto &elem: c)
        std::cout << elem << ' ';

    std::cout << static_cast<int>(c == a);
    return 0;
}
