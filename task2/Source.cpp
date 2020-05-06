#include <fstream>
#include <iostream>
using namespace std;

ifstream in;
ofstream out;

struct Matrix {
	int n, m; // ����������� �������
	double* values; // ������ �� �������� ������� 
};

Matrix* read(const char* filename); // �������, �������� ������� �� �����.
double findSum(Matrix* matr); // �������, ������ �����
char* reshow(const char* file); 
void ansver();

int main() {
	
	setlocale(LC_ALL, "rus");
	system("chcp 1251");

	while (true) {
		cout << "������� 1 - ��� ���������� ����������\n\
������� 2 - ��� ������ ��������� ������;\n\
������� 3 - ��� ��������� ������� ������;\n\
������� 4 - ��� ���� �����������;\n����� ��������� ����� ����������\n";
		int step;
		cin >> step;
		switch (step) {
		case 1: {
			cout << "������� n � m - ����������� �������\n";
			int n, m;
			cin >> n >> m;
			fstream out;
			out.open("input.txt");
			out << n << ' ' << m << '\n';
			double boof;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					cin >> boof;
					out << boof << ' ';
				}
				out << endl;
			}
			out << '/';
			out << endl;

			break;
		}
		case 2: {
			char* inf = reshow("input.txt");
			cout << inf << endl << endl;
			break;
		}

		case 3: {
			cout << "����� ���������\n\n";
			ansver();
			break;
		}
		case 4: {
			char* ans = reshow("output.txt");
			cout << ans << endl << endl;
			break;
		}
		default:
			return 0;
			break;
		}
	}

	return 0;
}

void ansver() {
	Matrix* matrix = read("input.txt");
	double sum = findSum(matrix);

	out.open("output.txt");

	for (int i = 0; i < matrix->n; i++) {
		for (int j = 0; j < matrix->m; j++) {
			out << *(matrix->values + matrix->m * i + j) << ' ';
		}
		out << endl;
	}
	out << "����� �������� ��������� ��� ����� �������,\n� ������� �� ������� ��������� ����������� ��������,\n������� ������������� �������� = ";
	out << sum << '/';
	out.close();
}

char* reshow(const char* file) {
	char* text = new char[10000];
	ifstream in;
	in.open(file);
	in.get(text, 10000, '/');
	in.close();
	return text;
}
Matrix* read(const char* filename) {
	Matrix* matr = new Matrix;

	ifstream in;
	in.open(filename);
	in >> matr->n;
	in >> matr->m;
	double* mass = new double[matr->n * matr->m + 1];
	for (int i = 0; i < matr->n; i++) {
		for (int j = 0; j < matr->m; j++) {
			in >> *(mass + i * matr->m + j);
		}
	}
	in.close();

	matr->values = mass;
	return matr;
}

double findSum(Matrix* matr) {
	double sum = 0;
	for (int i = 0; i <= matr->n; i++) {
		double mx = -1111111111;
		int jj = 0;
		if (*(matr->values + i * matr->m + i) < 0) {
			for (int j = 0; j < matr->m; j++) {
				sum += *(matr->values + i * matr->m + j);
			}
		}
	}
	return sum;
}
