#include "matrix.hpp"
#include <vector>
#include <iostream>

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


    //std::cout << "Command: c.fill(c.begin() + 1, c.end() - 1, 2.22);\n";
    //c.fill(c.begin() + 1, c.end() - 1, 2.22);
    std::cout << c << "\n\n";

    //for (const auto &elem: c)
        //std::cout << elem << ' ';
    //std::cout << std::endl;

    std::cout << std::endl << std::endl << c.GetRows() << ' ' << c.GetColumns() << std::endl << std::endl;

    std::cout << c << std::endl;

    Matrix<vector<int>> v(3, 3, vector<int>(3, 3));

    //auto it = v.begin();
    //auto it2 = it - q;
    //it2 += 2;
    //it2 = v.end();

    //auto it3 = c.end();
    //std::cout << *it3;

    //std::cout << it2->at(1) << std::endl;
    

    std::cout << c << std::endl;

    std::cout << static_cast<int>(c == a) << std::endl;
    return 0;
}
