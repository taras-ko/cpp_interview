// From C++ Interview Questions by Dr. Fatih Kocan,
// Wael Kdouh and Kathryn Patterson
// question from pg.27
#include <stdexcept>
#include <iostream>
#include <functional>

class Matrix {
public:
    Matrix(int rows, int cols);
    double& operator() (int row, int col);
//    double operator() (int row, int col) const;
    ~Matrix();

    //Matrix(const Matrix& m);
    //Matrix& operator=(const Matrix& m);

private:
    int m_rows, m_cols;
    double* m_data;
};

inline
Matrix::Matrix(int rows, int cols)
    : m_rows {rows}
    , m_cols {cols}
{
    std::cout << "Matrix(" << rows << "x" << cols << ")\n";
    if (rows <= 0 || cols <= 0)
        throw std::out_of_range("Matrix constructor has 0 or negative size");

    m_data = new double[rows * cols];
    for (int i = 0; i < rows*cols; i++)
        m_data[i] = 0;
}

inline
double& Matrix::operator() (int row, int col)
{
    std::cout << "double& operator()" << std::endl;
    if (row >= m_rows || col >= m_cols)
        throw std::out_of_range("Matrix subscript out of bounds");

    return m_data[m_cols*row + col];
}

inline
double Matrix::operator() (int row, int col) const
{
    std::cout << "double operator() const" << std::endl;
    if (row >= m_rows || col >= m_cols)
        throw std::out_of_range("Matrix subscript out of bounds");
    return m_data[m_cols*row + col];
}

inline Matrix::~Matrix()
{
    delete[] m_data;
}

int main()
{
    Matrix m(10,10);
    const Matrix cm(10,10);

    m(5,8) = 105.12;

    std::cout << m(5,8) << std::endl;
    std::cout << cm(5,8) << std::endl;
}

