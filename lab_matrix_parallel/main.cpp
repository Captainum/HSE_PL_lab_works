#include "Matrix.hpp"

#include <iostream>

int main() {
    std::ifstream fin("in.txt");

    if (!fin.good()) {
	    std::cerr << "Cannot open input file" << std::endl;
	    exit(1);
    }

    size_t k;
    fin >> k;
    Matrix<double>::SetParallel(k);

    Matrix<double> A;
    Matrix<double> B;
    
    A.LoadMatrix(fin);
    B.LoadMatrix(fin);

    Matrix<double> C;
    
    C = A * B;

    C.SaveMatrix("out.txt"); 

    fin.close();
    return 0;
}
