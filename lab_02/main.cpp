#include "matrix.hpp"

int main() {
    size_t q = 2, z = 3;

    try {
        Matrix<int> err_m(-1, 2);
    } catch (MemoryError &err){
        std::cout << err.what() << std::endl;
    }

    Matrix<int> a(q, z);
    Matrix<double> b(q, z, 12);

    std::cout << b << std::endl;

    Matrix<double> c({ { 2., 3. }, { 3., 4. } });

    c.fill(c.begin(), c.end(), 2.22);

    auto it = c.begin();
    auto it2 = it + q;
    it2 += 2;

    for (const auto &elem: c)
        std::cout << elem << ' ';
    std::cout << std::endl;

    std::cout << c << std::endl;

    std::cout << static_cast<int>(c == a) << std::endl;
    return 0;
}
