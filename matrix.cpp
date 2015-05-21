#include <cmath>
#include <cassert>
#include"matrix.h"

using std::cout;
using std::endl;
using std::cin;

MyMatrix::MyMatrix()
{
	ptr = nullptr;
	width = 0;
	height = 0;
}

MyMatrix::MyMatrix (const size_t arrHeight, const size_t arrWidth)
{
	ptr = new int[arrHeight * arrWidth];
	height = arrHeight;
	width = arrWidth;
}

MyMatrix::MyMatrix (const int *const array, const size_t arrHeight, const size_t arrWidth)
{
	ptr = new int[arrHeight * arrWidth];
	for (size_t i = 0; i < arrHeight * arrWidth; i++)
	{
		ptr[i] = array[i];
	}
	width = arrWidth;
	height = arrHeight;
}

MyMatrix::MyMatrix (const int **const array, const size_t arrHeight, const size_t arrWidth)
{
	ptr = new int[arrHeight * arrWidth];
	for (size_t i = 0; i < arrHeight  ; i++)
	{
		for (size_t j = 0; j < arrWidth; j++)
		{
			ptr[i * arrWidth + j] = array[i][j];
		}
	}
	height = arrHeight;
	width = arrWidth;
}

MyMatrix::MyMatrix (const MyMatrix &mat)
{
	size_t len = mat.height * mat.width;
	ptr = new int[len];
	for (size_t i = 0; i < len ; i++)
	{
		ptr[i] = mat.ptr[i];
	}
	height = mat.height;
	width = mat.width;
}

MyMatrix::~MyMatrix()
{
	delete []ptr;
	ptr = nullptr;
}


MyMatrix MyMatrix::minorMatrix (const size_t ver,const  size_t hor) const
{
	MyMatrix result;
	result.ptr = new int[ (width - 1) * (height - 1)];
	if (width == height && width > 1)
	{
		result.width = width - 1;
		result.height = height - 1;
		size_t p = 0;
		for (size_t i = 0; i < height; i++)
		{
			for (size_t j = 0; j < width; j++)
			{
				if (j == hor - 1 || i == ver - 1)
				{
				}
				else
				{
					result.ptr [p] = ptr[i * width + j];
					p++;
				}
			}
		}
	}
	return result;
}

bool MyMatrix::setSize (const size_t arrHeight,const  size_t arrWidth)
{
	bool success = false;
	if (arrHeight != height || arrWidth != width)
	{
		if (arrHeight != 0 && arrWidth != 0)
		{
			height = arrHeight;
			width = arrWidth;
		}
		else
		{
			delete[] ptr;
			ptr = nullptr;
			height = 0;
			width = 0;
		}
		success = true;
	}
	return success;
}

bool MyMatrix::setValue (const int *const array)
{
	bool success = false;
	if (array != nullptr)
	{
		for (size_t i = 0; i < height * width; i++)
		{
			ptr[i] = array[i];
		}
		success = true;
	}
	return success;
}

bool MyMatrix::setValue (const int *const array,const  size_t arrHeight, const size_t arrWidth)
{
	bool success = false;
	if (arrHeight > 0 && arrWidth > 0 && array != nullptr)
	{
		delete []ptr;
		ptr = new int[arrHeight * arrWidth];
		for (size_t i = 0; i < arrHeight * arrWidth; i++)
		{
			ptr[i] = array[i];
		}
		width = arrWidth;
		height = arrHeight;
		success = true;
	}
	else if (arrHeight == 0 || arrWidth == 0)
	{
		delete []ptr;
		ptr = nullptr;
		success = true;
		width = 0;
		height = 0;
	}
	return success;
}

int MyMatrix::det() const
{
	int result = 0;
	if (width == height)
	{
		if (width > 1)
		{
			for (size_t i = 0; i < width ; i++)
			{
				MyMatrix tempMat (minorMatrix (1, i + 1));
				if ( (i) % 2 == 0)
				{
					result = result + ptr[i] * tempMat.det();
				}
				else
				{
					result = result - ptr[i] * tempMat.det();
				}
			}
		}
		else if (width == 1)
		{
			result = ptr[0];
		}
	}
	return result;
}

MyMatrix MyMatrix::inverse() const
{
	MyMatrix result;
	int detA = det();
	if (detA == 1 || detA == -1)
	{
		result.setValue (ptr, height, width);
		for (size_t i = 0; i < height; i++)
		{
			for (size_t j = 0; j < width ; j++)
			{
				if ( (i + 1 + j + 1) % 2 == 0)
				{
					result.ptr[i * width + j] = minorMatrix (i + 1, j + 1).det() / detA;
				}
				else
				{
					result.ptr[i * width + j] = -minorMatrix (i + 1, j + 1).det() / detA;
				}
			}
		}
	}
	return result.trans();
}

MyMatrix MyMatrix::trans() const
{
	MyMatrix result (ptr, width, height);
	for (size_t i = 0; i < result.height; i++)
	{
		for (size_t j = 0; j < result.width ; j++)
		{
			result.ptr[i * result.width + j] = ptr[j * width + i];
		}
	}
	return result;
}

int MyMatrix::trace() const
{
	int result = 0;
	for (size_t  i = 0; i < width; i++)
	{
		result = result + ptr[i * width + i];
	}
	return result;
}

MyMatrix MyMatrix::operator + (const int c) const
{
	MyMatrix result (ptr, height, width);
	for (size_t i = 0; i < height * width; i++)
	{
		result.ptr[i] = result.ptr[i] + c;
	}
	return result;
}

MyMatrix MyMatrix::operator+ (const MyMatrix &mat) const
{
	int *arr = nullptr;
	size_t arrHeight = 0;
	size_t arrWidth = 0;
	if (height == mat.height && width == mat.width)
	{
		size_t len = mat.height * mat.width;
		arr = new int[len];
		for (size_t i = 0; i < len ; i++)
		{
			arr[i] = ptr[i] + mat.ptr[i];
		}
		arrHeight = height;
		arrWidth = width;
	}
	return MyMatrix (arr, arrHeight, arrWidth);
}

MyMatrix MyMatrix::operator* (const int c) const
{
	MyMatrix result (ptr, height, width);
	for (size_t i = 0; i < height * width; i++)
	{
		result.ptr[i] = result.ptr[i] * c;
	}
	return result;
}

MyMatrix MyMatrix::operator* (const MyMatrix &mat) const
{
	//	int *arr;
	MyMatrix result;
	if (width == mat.height)
	{
		size_t len = height * mat.width;
		result.ptr = new int[len];
		result.height = height;
		result.width = mat.width;
		for (size_t i = 0; i < len ; i++)
		{
			result.ptr[i] = 0;
		}
		for (size_t k = 0; k < result.height; k++)
		{
			for (size_t i = 0; i < result.width ; i++)
			{
				for (size_t j = 0; j < width ; j++)
				{
					result.ptr[k * result.width + i] = result.ptr[k * result.width + i] + ptr[k * width + j] * mat.ptr[j * mat.width + i];
				}
			}
		}
	}
	return result;
}

MyMatrix &MyMatrix::operator= (const MyMatrix &mat)
{
	delete []ptr;
	height = mat.height;
	width = mat.width;
	size_t len = mat.height * mat.width;
	ptr = new int[len];
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width ; j++)
		{
			ptr[i * width + j] = mat.ptr[i * width + j];
		}
	}
	return (*this);
}

bool MyMatrix::operator== (const MyMatrix &mat) const
{
	bool compare = false;
	bool flag = true;
	if (mat.width == width && mat.height == height)
	{
		compare = true;
		if (width == 0 || height == 0)
		{
		}
		else
		{
			for (size_t i = 0; i < height; i++)
			{
				for (size_t j = 0; j < width ; j++)
				{
					if (ptr[i * width + j] != mat.ptr[i * width + j])
					{
						compare = false;
						break;
						flag = false;
					}
				}
				if (flag == false)
				{
					break;
				}
			}
		}
	}
	return compare;
}

int& MyMatrix::operator ()(const size_t n, const size_t m) const
{
	assert(ptr != nullptr && width != 0 && height != 0 && n<height && m<width);
	return ptr[n*width+m];

}

std::ostream &operator<< (std::ostream &out, const MyMatrix &mat)
{
	for (size_t i = 0; i < (mat.height); i++)
	{
		for (size_t j = 0; j < (mat.width); j++)
		{
			out << mat.ptr[i * mat.width + j] << " ";
		}
		cout << endl;
	}
	return out;
}

std::istream &operator>> (std::istream &in, MyMatrix &mat)
{
	cout << "Enter width:\n";
	in >> mat.width;
	cout << "Enter height:\n";
	in >> mat.height;
	delete []mat.ptr;
	if (mat.width != 0 && mat.height != 0)
	{
		mat.ptr = new int[mat.width * mat.height];
		for (size_t i = 0; i < mat.width * mat.height; i++)
		{
			in >> mat.ptr[i];
		}
	}
	else
	{
		mat.ptr = nullptr;
	}
	return in;
}

std::ofstream &operator<< (std::ofstream &file, const MyMatrix &mat)
{
	file << "Width: " << mat.width << "\nHeight: " << mat.height << "\n";
	//	file<<mat.width<<' '<<mat.height<<'\n';
	for (size_t i = 0; i < (mat.height); i++)
	{
		for (size_t j = 0; j < (mat.width); j++)
		{
			file << mat.ptr[i * mat.width + j] << " ";
		}
		file << endl;
	}
	file << endl;
	return file;
}

std::ifstream &operator>> (std::ifstream &file, MyMatrix &mat)
{
	int flag = 0;
	while (! (file >> mat.width))
	{
		if (file.eof())
		{
			flag = 1;
			break;
		}
		file.clear();
		file.ignore (1);
	}
	while (! (file >> mat.height) && flag == 0)
	{
			file.clear();
			file.ignore (1);
	}


	if ( mat.width != 0 && mat.height != 0 && flag==0)
	{
		delete []mat.ptr;
		mat.ptr = new int[mat.width * mat.height];
		for (size_t i = 0; i < mat.width * mat.height; i++)
		{
			file >> mat.ptr[i];
		}
	}
	else if (flag==0)
	{
		mat.width = 0;
		mat.height = 0;
		mat.ptr = nullptr;
	}
	return file;
}





