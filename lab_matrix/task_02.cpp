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
	fin.close();
	A.solve_with_0();

	return 0;
}
