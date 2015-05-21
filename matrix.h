#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <fstream>

class MyMatrix
{
		int *ptr;
		size_t width;
		size_t height;
	public:
		MyMatrix();
		~MyMatrix();
		MyMatrix (const size_t arrHeight, const size_t arrWidth);
		MyMatrix (const int *const array, const size_t arrHeight, const size_t arrWidth);
		MyMatrix (const int **const array, const size_t arrHeight, const size_t arrWidth);
		MyMatrix (const MyMatrix &mat);

		MyMatrix minorMatrix (const size_t ver, const size_t hor) const;
		bool setSize (const size_t arrHeight, const size_t arrWidth);
		bool setValue (const int *const array);
		bool setValue (const int *const array, const size_t arrHeight, const size_t arrWidth);
		int det() const;
		MyMatrix inverse() const;
		MyMatrix trans() const;
		int trace() const;

		MyMatrix operator + (const int c) const;
		MyMatrix operator + (const MyMatrix &mat) const;
		MyMatrix operator * (const int c) const;
		MyMatrix operator * (const MyMatrix &mat) const;
		bool operator == (const MyMatrix &mat) const;
		MyMatrix &operator = (const MyMatrix &mat);
		int &operator () (const size_t n, const size_t m) const;

		friend std::ostream &operator<< (std::ostream &out, const MyMatrix &mat);
		friend std::istream &operator>> (std::istream &in, MyMatrix &mat);

		friend std::ofstream &operator<< (std::ofstream &file, const MyMatrix &mat);
		friend std::ifstream &operator>> (std::ifstream &file,  MyMatrix &mat);
};

#endif // MATRIX_H
