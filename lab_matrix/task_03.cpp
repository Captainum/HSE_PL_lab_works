#include "Matrix.hpp"


int main() {
	ifstream fin("./in.txt");
	if (!fin.is_open()) {
		cout << "Cannot open input file" << endl;
		exit(0);
	}
	size_t n, m;
	fin >> n >> m;
	Matrix<double> A(n, m);
	fin >> A;
	Matrix <double> B(A.get_rows(), 1);
	for (size_t i = 0; i < A.get_rows(); i++) {
		double tmp;
		fin >> tmp;
		B.set_element(i, 0, tmp);
	}
	fin.close();
	A.solve_with(B);
	return 0;
}
