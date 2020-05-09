#include <vector>
#include <iostream>
#include <algorithm>
#include "matrix.hpp"

template <typename T>
using vector = std::vector<T>;

int main() {
    std::cout << "CONSTRUCTOR TESTING SECTION:" << "\n\n";
    try {
        std::cout << "Attempt to create matrix with negative size" << 
            " (conversion to very big size_t number)" << std::endl;
        Matrix<int> err_m(-1, 2);
    } catch (MemoryError &err){
        std::cerr << err.what() << "\n\n";
    }

    size_t q = 2, z = 3;
    std::cout << "Constructor with two size_t numbers:\n";
    Matrix<int> a(q, z);
    std::cout << a << "\n\n";

    std::cout << "Constructor with one zero size:\n";
    Matrix<int> ab(0, 3);
    std::cout << "Sizes of matrix: " << ab.GetRows() << " and " << ab.GetColumns() << "\n\n";
    std::cout << "insert row with filler 2 in this matrix: \n";
    ab.insertRow(0, 2);
    std::cout << ab << "\n\n";
    std::cout << "Constructor with filler [Matrix<double> b(3, 2, 12)]:\n";
    Matrix<double> b(q, z, 12);
    std::cout << b << "\n\n";
    std::cout << "Constructor with initialization list [Matrix<double> c({ { 2., 3. }, { 3., 4. } })]:\n";
    Matrix<double> c({ { 2., 3. }, { 3., 4. } });
    std::cout << c << "\n\n";
    std::cout << "CONSTRUCTOR SECTION END\n\n\n";


    std::cout << "INSERT-DELETE-RESIZE OPERATIONS TESTING SECTION:\n\n";
    std::cout << "Working with matrix c:\n";
    std::cout << c << "\n\n";

    std::cout << "Command: c.insertRow(1, 3.33);\n";
    c.insertRow(1, 3.33);
    std::cout << c << "\n\n";

    std::cout << "Command: c.insertCol(1, 4.321);\n";
    c.insertCol(1, 4.321);
    std::cout << c << "\n\n";

    std::cout << "Command: c.deleteCol(1);\n";
    c.deleteCol(1);
    std::cout << c << "\n\n";

    std::cout << "Command: c.deleteRow(0);\n";
    c.deleteRow(0);
    std::cout << c << "\n\n";

    std::cout << "Command: c.resizeRows(c.GetRows() + 1);\n";
    c.resizeRows(c.GetRows() + 1);
    std::cout << c << "\n\n";

    std::cout << "Command: c.resizeCols(c.GetColumns() + 1);\n";
    c.resizeCols(c.GetColumns() + 1);
    std::cout << c << "\n\n";

    std::cout << "Command: c.resizeRows(c.GetRows() + 1, 34);\n";
    c.resizeRows(c.GetRows() + 1, 34);
    std::cout << c << "\n\n";

    std::cout << "Command: c.resizeCols(c.GetColumns() + 1, 43);\n";
    c.resizeCols(c.GetColumns() + 1, 43);
    std::cout << c << "\n\n";

    std::cout << "Command: c.resize(c.GetRows() + 2, c.GetColumns() + 1);\n";
    c.resize(c.GetRows() + 2, c.GetColumns() + 1);
    std::cout << c << "\n\n";

    std::cout << "Command: c.resize(c.GetRows() - 2, c.GetColumns() - 1);\n";
    c.resize(c.GetRows() - 2, c.GetColumns() - 1);
    std::cout << c << "\n\n";
    std::cout << "INSERT-DELETE-RESIZE OPERATIONS SECTION END\n\n\n";


    std::cout << "GET ELEMENT METHODS SECTION:\n\n";
    Matrix<string> new_m = { { "a1", "a2", "a3" }, { "b1", "b2", "b3" }, { "c1", "c2", "c3" } };
    std::cout << "Working with matrix new_m: \n" << new_m << "\n\n";

    std::cout << "Commands: new_m[1][1] and new_m.at(1, 1)\n";
    std::cout << new_m[1][1] << " / " << new_m.at(1, 1) << "\n\n";

    std::cout << "Commands: new_m[1][1] = new1 and new_m.at(1, 2) = new2\n";
    new_m[1][1] = "new1"; new_m.at(1, 2) = "new2";
    std::cout << "new_m[1][1] = " << new_m[1][1] << ", new_m[1][2] = " << new_m[1][2] << "\n\n";
    std::cout << "GET ELEMENT METHODS SECTION END\n\n\n";


    std::cout << "ITERATORS SECTION\n\n";
    std::cout << "Matrix from previos section:\n";
    std::cout << new_m << "\n\n";

    std::cout << "Command: range-based for cycle (const elem &), ' ' as delimiter\n";
    for (const auto &elem: new_m)
        std::cout << elem << ' ';
    std::cout << "\n\n";

    size_t cnt = 0;
    std::cout << "Range-based for filling matrix with string \"new_test<number>\":\n";
    for (auto &elem: new_m)
        elem = "new_test" + std::to_string(++cnt);
    std::cout << new_m << "\n\n";

    std::cout << "Test insert [from, to, filler]:\n";
    new_m.insert(new_m.end() - static_cast<int>(new_m.GetColumns()), new_m.end(), "filler_for_last_line");
    std::cout << new_m << "\n\n";

    std::cout << "Test insert from another matrix container via iterators:\n";
    Matrix<string> test_m = {{"test1", "test2", "test3"}, {"test4", "test5", "test6"}};
    new_m.insert(new_m.end() - static_cast<int>(new_m.GetColumns()), test_m.begin(), test_m.end());
    std::cout << new_m << "\n\n";

    std::cout << "Reverse method check (reverse first line): \n";
    new_m.reverse(new_m.begin(), new_m.begin() + static_cast<int>(new_m.GetColumns()));
    std::cout << new_m << "\n\n";

    std::cout << "ITERATORS SECTION ENDS\n\n";


    std::cout << "CONST ITERATORS AND OBJECTS SECTION\n\n";

    std::cout << "Create const matrix = { { '11', '12', '13' }, { '21', '22', '23' } }\n";
    const Matrix<string> const_m = { { "11", "12", "13" }, { "21", "22", "23" } };
    std::cout << "Range-based for cycle for const matrix:\n";
    for (const auto &elem: const_m)
        std::cout << elem << "; ";
    std::cout << "\n\n";

    std::cout << "Insert in new_m matrix from const matrix:\n";
    std::cout << "new_m matrix:\n" << new_m << "\n\n";
    std::cout << "Insert command: new_m.insert(new_m.begin(), const_m.begin(), const_m.begin() + 3);\n";
    new_m.insert(new_m.begin(), const_m.begin(), const_m.begin() + 3);
    std::cout << "new_m matrix after insertion: \n" << new_m << "\n\n";

    std::cout << "Check of cbegin and cend methods of non-constant object (new_m matrix):\n";
    for (auto it = new_m.cbegin(); it < new_m.cend(); it++)
        std::cout << *it << "; ";
    std::cout << "\n\n";
    std::cout << "CONST ITERATORS AND OBJECTS SECTION ENDS\n\n";


    return 0;
}
