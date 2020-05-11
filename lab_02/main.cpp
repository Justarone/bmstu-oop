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
    } catch (ExceptionMatrix &err){
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

    std::cout << "Check of transpose method on matrix c (but first - resize (+ 2 rows)):\n";
    std::cout << "Command: c.resizeRows(c.GetRows() + 2, 32.10);\n";
    c.resizeRows(c.GetRows() + 2, 32.10);
    std::cout << "Result: \n" << c << "\n\n";
    std::cout << "Command: c.transpose();\n";
    c.transpose();
    std::cout << "Result: \n" << c << "\n\n";

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

    std::cout << "Test fill [from, to, filler]:\n";
    new_m.fill(new_m.end() - static_cast<int>(new_m.GetColumns()), new_m.end(), "filler_for_last_line");
    std::cout << new_m << "\n\n";

    std::cout << "Test fill from another matrix container via iterators:\n";
    Matrix<string> test_m = {{"test1", "test2", "test3"}, {"test4", "test5", "test6"}};
    new_m.fill(new_m.end() - static_cast<int>(new_m.GetColumns()), test_m.begin(), test_m.end());
    std::cout << new_m << "\n\n";

    std::cout << "Reverse method check (reverseSeq first line): \n";
    new_m.reverseSeq(new_m.begin(), new_m.begin() + static_cast<int>(new_m.GetColumns()));
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
    std::cout << "Insert command: new_m.fill(new_m.begin(), const_m.begin(), const_m.begin() + 3);\n";
    new_m.fill(new_m.begin(), const_m.begin(), const_m.begin() + 3);
    std::cout << "new_m matrix after insertion: \n" << new_m << "\n\n";

    std::cout << "Check of cbegin and cend methods of non-constant object (new_m matrix):\n";
    for (auto it = new_m.cbegin(); it < new_m.cend(); it++)
        std::cout << *it << "; ";
    std::cout << "\n\n";
    std::cout << "CONST ITERATORS AND OBJECTS SECTION ENDS\n\n";

    std::cout << "MATH OPERATIONS SECTION\n\n";
    Matrix<double> math_matrix = { { 1, 2, 3, 4 }, {7, 9, 11, 13}, {4, 2, 0, -2}, {1, 4, 7, 10} };
    std::cout << "Matrix to work with here (math_matrix): \n";
    std::cout << math_matrix << "\n\n";

    std::cout << "Operation: math_matrix += 2.5;\n";
    math_matrix += 2.5;
    std::cout << "matrix after operation:\n";
    std::cout << math_matrix << "\n\n";
    std::cout << "Operation: math_matrix -= 2.5;\n";
    math_matrix -= 2.5;
    std::cout << "matrix after operation:\n";
    std::cout << math_matrix << "\n\n";
    std::cout << "Operation: math_matrix *= 2.5;\n";
    math_matrix *= 2.5;
    std::cout << "matrix after operation:\n";
    std::cout << math_matrix << "\n\n";
    std::cout << "Operation: math_matrix *= 0.4;\n";
    math_matrix *= 0.4;
    std::cout << "matrix after operation:\n";
    std::cout << math_matrix << "\n\n";

    Matrix<double> tmp;

    std::cout << "Operation: tmp = math_matrix + 2.5;\n";
    tmp = math_matrix + 2.5;
    std::cout << "matrix after operation:\n";
    std::cout << tmp << "\n\n";
    std::cout << "Operation: tmp = math_matrix - 2.5;\n";
    tmp = math_matrix - 2.5;
    std::cout << "matrix after operation:\n";
    std::cout << tmp << "\n\n";
    std::cout << "Operation: tmp = math_matrix * 2.5;\n";
    tmp = math_matrix * 2.5;
    std::cout << "matrix after operation:\n";
    std::cout << tmp << "\n\n";
    std::cout << "Operation: tmp = math_matrix * 0.4;\n";
    tmp = math_matrix * 0.4;
    std::cout << "matrix after operation:\n";
    std::cout << tmp << "\n\n";

    Matrix<int> det_matrix = { { 38, 382, 21, 9 }, { 21, 1, 9, 11 }, { 118, 5, 85, 2 }, { 10, 8, 22, 13 } };
    std::cout << "det_matrix:\n" << det_matrix << "\n\n";
    std::cout << "Operation: det_matrix.determinant();\n";
    std::cout << "Result: " << det_matrix.determinant() << "\n";

    std::cout << "Matrix multiplication check: \n";
    Matrix<double> res;
    Matrix<double> m1 = { { 1 }, { 2 }, { 3 } }, m2 = { { 1, 2 } };
    std::cout << "Operation: m1 * m2 (m1 = { { 1 }, { 2 }, { 3 } }, m2 = { { 1, 2 } })\n";
    res = m1 * m2;
    std::cout << "Result:\n" << res << "\n\n";

    std::cout << "MATH OPERATIONS SECTION END\n\n";

    return 0;
}
