#include "Matrix.hpp"

int main() {
	ifstream fin("./in.txt");
	double k;
	size_t n, m;
	fin >> k;
	
	fin >> n >> m;
	Matrix<double> A(n, m);
	fin >> A;
	
	fin >> n >> m;
	Matrix<double> B(n, m);
	fin >> B;
	
	fin >> n >> m;
	Matrix<double> C(n, m);
	
	fin >> C;
	fin.close();
	
	Matrix<double> D;
	D = A + k * B.transpose() * C.inverse();
	ofstream fout("./out.txt");
	if (!fout.is_open()) {
		cout << "Cannot open output file" << endl;
		exit(0);
	}
	fout << 1 << endl;
	fout << D.det() << endl;
	fout << D.get_rows() << " " << D.get_cols() << endl;
	fout << D;
	fout.close();

	return 0;
}
