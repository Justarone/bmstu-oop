#include "matrix.hpp"
#include <vector>

template <typename T>
using vector = std::vector<T>;

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
    std::cout << c;

    c.insertRow(1, 3.33);
    std::cout << c;


    Matrix<vector<int>> v(3, 3, vector<int>(3, 3));

    auto it = v.begin();
    auto it2 = it - q;
    it2 += 2;
    it2 = v.end();

    auto it3 = c.end();
    std::cout << *it3;

    std::cout << it2->at(1) << std::endl;
    

    for (const auto &elem: c)
        std::cout << elem << ' ';
    std::cout << std::endl;

    std::cout << c << std::endl;

    std::cout << static_cast<int>(c == a) << std::endl;
    return 0;
}
