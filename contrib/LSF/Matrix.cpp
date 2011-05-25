/*
 * Code by Peter Salz, TU Kaiserslautern, Germany, 2008
 */

#include "Matrix.h"
#include "Vector.h"

Matrix::Matrix()
{
	m_NumberRows = 0;
	m_NumberColumns = 0;
	m_Data = NULL;
	m_RowSwaps = NULL;
}

Matrix::Matrix(uint numberRows, uint numberColumns)
{
	m_NumberRows = numberRows;
	m_NumberColumns = numberColumns;
	m_Data = new double[numberRows*numberColumns];
	m_RowSwaps = new uint[numberRows];

	// Initialize array for row swapping
	for (uint i = 0; i < m_NumberRows; i++)
		m_RowSwaps[i] = i;

	// i: row, j: column
	for (uint i = 0; i < m_NumberRows; i++)
		for (uint j = 0; j < m_NumberColumns; j++)
			m_Data[i*m_NumberColumns + j] = 0.0;
}

Matrix::Matrix(uint numberRows, uint numberColumns, double *data)
{
	if (data == NULL)
	{
		std::cout << "Vector() got NULL parameter!" << std::endl;
		m_NumberRows = 0;
		m_NumberColumns = 0;
		m_Data = NULL;
		m_RowSwaps = NULL;
	}
	else
	{
		m_NumberRows = numberRows;
		m_NumberColumns = numberColumns;
		m_Data = data;
		m_RowSwaps = new uint[m_NumberRows];

		// Initialize array for row swapping
		for (uint i = 0; i < m_NumberRows; i++)
			m_RowSwaps[i] = i;
	}
}	

Matrix::Matrix (const Matrix &mat)
{
	m_NumberRows = mat.getNumberRows();
	m_NumberColumns = mat.getNumberColumns();
	m_Data = new double[m_NumberRows*m_NumberColumns];

	for (uint i = 0; i < m_NumberRows; i++)
		for (uint j = 0; j < m_NumberColumns; j++)
			m_Data[i*m_NumberColumns + j] = mat(i,j);

	m_RowSwaps = new uint[m_NumberRows];
	// Initialize array for row swapping
	for (uint i = 0; i < m_NumberRows; i++)
		m_RowSwaps[i] = i;
}

Matrix::~Matrix()
{
	if (m_Data != NULL)
		delete [] m_Data;
	if (m_RowSwaps != NULL)
		delete [] m_RowSwaps;
}

uint Matrix::getNumberRows() const
{
	return m_NumberRows;
}

uint Matrix::getNumberColumns() const
{
	return m_NumberColumns;
}

void Matrix::setSize(uint numberRows, uint numberColumns)
{

}

Vector Matrix::getColumn(const uint &index) const
{
	Vector result(m_NumberRows);

	if (index >= m_NumberColumns)
	{
		std::cout << "getColumn: index " << index << " exceeds column number!" << std::endl;
		return result;
	}

	for (uint i = 0; i < m_NumberRows; i++)
		result(i) = m_Data[i*m_NumberColumns + index];

	return result;
}

Vector Matrix::getRow(const uint &index) const
{
	Vector result(m_NumberColumns);

	if (index >= m_NumberRows)
	{
		std::cout << "getRow: index " << index << " exceeds matrix size!" << std::endl;
		return result;
	}

	for (uint j = 0; j < m_NumberColumns; j++)
		result(j) = m_Data[index*m_NumberColumns + j];

	return result;
}

void Matrix::setColumn(const uint &index, const Vector &vec)
{
	if (vec.getSize() != m_NumberRows)
	{
		std::cout << "setColumn: not the same dimension! (" << m_NumberRows << " != " << vec.getSize() << ")" << std::endl;
		return;
	}
	if (index >= m_NumberColumns)
	{
		std::cout << "setColumn: index " << index << " exceeds matrix size!" << std::endl;
		return;
	}

	for (uint i = 0; i < m_NumberRows; i++)
		m_Data[i*m_NumberColumns + index] = vec(i);
}

void Matrix::setRow(const uint &index, const Vector &vec)
{
	if (vec.getSize() != m_NumberColumns)
	{
		std::cout << "setRow: not the same dimension! (" << m_NumberColumns << " != " << vec.getSize() << ")" << std::endl;
		return;
	}
	if (index >= m_NumberRows)
	{
		std::cout << "setRow: index " << index << " exceeds matrix size!" << std::endl;
		return;
	}

	for (uint j = 0; j < m_NumberColumns; j++)
		m_Data[index*m_NumberColumns + j] = vec(j);
}

Vector Matrix::backwardSubstitution(const Vector &rightSide)
{
	Vector result(m_NumberRows);

	if (m_NumberRows != m_NumberColumns)
	{
		std::cout << "backwardSubstitution: matrix is not quadratic." << std::endl;
		return result;
	}

	uint n = m_NumberRows-1;

	if (rightSide.getSize() != m_NumberRows)
	{
		std::cout << "backwardSubstitution: not the same dimension! (" << m_NumberRows << " != " << rightSide.getSize() << ")" << std::endl;
		return result;
	}

	// Check if upper triangle matrix
	for (uint i = 0; i < m_NumberRows; i++)
	{
		for (uint j = 0; j < i; j++)
		{
			if (m_Data[i*m_NumberColumns + j] != 0.0)
			{
				std::cout << "backwardSubstitution: Matrix is not of upper triangle form!" << std::endl;
				return result;
			}
		}
	}

	// Does a solution exist?
	if (m_Data[n*m_NumberColumns + n] == 0.0)
	{
		if (rightSide(n) == 0.0)
		{
			std::cout << "System has infinite many solutions!" << std::endl;
		}
		else
		{
			std::cout << "System has no solution!" << std::endl;
		}
		return result;
	}

	// Backward substitution
	std::cout << "Matrix is all right for substitution!" << std::endl;
	result(n) = rightSide(n) / m_Data[n*m_NumberColumns + n];

	for (int i = n-1; i >= 0; i--)
	{
		result(i) = rightSide(i);
		
		for (uint j = i+1; j <= n; j++)
		{
			std::cout << "(i,j) = (" << i << ", " << j << ")" << std::endl;
			result(i) -= (m_Data[i*m_NumberColumns + j] * result(j));
		}

		if (m_Data[i*m_NumberColumns + i] != 0.0)
			result(i) /= m_Data[i*m_NumberColumns + i];
		else
		{
			std::cout << "Found a 0 in row " << i << std::endl;
			return Vector(m_NumberRows);
		}
	}

	return result;
}

void Matrix::lrDecomposition(enum LRMODE mode)
{
	uint n = m_NumberRows-1;

	if (m_NumberRows != m_NumberColumns)
	{
		std::cout << "lrDecomposition: matrix is not quadratic." << std::endl;
		return;
	}

	for (uint k = 0; k < n; k++)
	{
		double max = 0.0;
		//m_RowSwaps[k] = 0;
		uint p_k = 0;
		double q;

		if (mode == COLUMNMAX)
		{
			// Search for the largest element in the 
			// k-th column and remember the corresponding
			// row number
			for (uint i = k; i <= n; i++)
			{
				if (fabs(m_Data[i*m_NumberColumns + k]) > max)
				{
					max = fabs(m_Data[i*m_NumberColumns + k]);
					p_k = i;
				}
			}
			m_RowSwaps[k] = p_k;
		}
		else if (mode == RELCOLUMNMAX)
		{
			// Compute the relative sum for each row
			// and remember the one with |a_ik|/s = max
			for (uint i = k; i <= n; i++)
			{
				double s = 0.0;
				for (uint j = k; j <= n; j++)
					s += fabs(m_Data[i*m_NumberColumns + j]);

				if (s == 0.0)
				{
					std::cout << "s = 0.0: Stopping." << std::endl;
					return;
				}

				q = fabs(m_Data[i*m_NumberColumns + k]) / s;
				if (q > max)
				{
					max = q;
					p_k = i;
				}
			}
			m_RowSwaps[k] = p_k;
		}

		if ((mode != DIAGONAL) && (max == 0.0))
		{
			std::cout << "max = 0.0: Stopping." << std::endl;
			return;
		}

		// Swap needed, so swap the rows
		if (m_RowSwaps[k] != k)
		{
			double temp;
			for (uint j = 0; j <= n; j++)
			{
				temp = m_Data[k*m_NumberColumns + j];
				m_Data[k*m_NumberColumns + j] = m_Data[m_RowSwaps[k]*m_NumberColumns + j];
				m_Data[m_RowSwaps[k]*m_NumberColumns + j] = temp;
			}
		}

		// Normal LR-Decomposition
		for (uint i = k+1; i <= n; i++)
		{
			if (m_Data[k*m_NumberColumns + k] == 0.0)
			{
				std::cout << "Found a 0 at a_{" << k << "," << k << "}^" << k << std::endl;
				return;
			}
		
			m_Data[i*m_NumberColumns + k] /= m_Data[k*m_NumberColumns + k];

			for (uint j = k+1; j <= n; j++)
				m_Data[i*m_NumberColumns + j] -= m_Data[i*m_NumberColumns + k]*m_Data[k*m_NumberColumns + j];
		}

		if (m_Data[n*m_NumberColumns + n] == 0.0)
		{
			std::cout << "a_nn = 0.0. Stopping." << std::endl;
			break;
		}
	}
}

void Matrix::choleskyDecomposition()
{
	uint n = m_NumberRows-1;

	if (m_NumberRows != m_NumberColumns)
	{
		std::cout << "choleskyDecomposition: matrix is not quadratic." << std::endl;
		return;
	}

	// Check symmetry:
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (m_Data[i*m_NumberColumns + j] != m_Data[j*m_NumberColumns + i])
			{
				std::cout << "choleskyDecomposition: matrix is not symmetric." << std::endl;
				return;
			}
		}
	}

	// Cholesky
	for (uint k = 0; k <= n; k++)
	{
		if (m_Data[k*m_NumberColumns + k] == 0.0)
		{
			std::cout << "choleskyDecomposition: matrix is not positive definit." << std::endl;
			return;
		}

		m_Data[k*m_NumberColumns + k] = sqrt(m_Data[k*m_NumberColumns + k]);

		for (uint j = k+1; j <= n; j++)
		{
			m_Data[k*m_NumberColumns + j] /= m_Data[k*m_NumberColumns + k];
		}

		for (uint i = k+1; i <= n; i++)
			for (uint j = i; j <=n; j++)
				m_Data[i*m_NumberColumns + j] -= m_Data[k*m_NumberColumns + i] * m_Data[k*m_NumberColumns + j];
	}

	// Use symmetry of A = C^T  * C to construct the lower left part
	for (int i = 0; i <= n; i++)
		for (int j = 0; j < i; j++)
			m_Data[i*m_NumberColumns + j] = m_Data[j*m_NumberColumns + i];
}

Matrix Matrix::inverseMatrix()
{
	Matrix result(m_NumberRows, m_NumberColumns);

	if (m_NumberRows != m_NumberColumns)
	{
		std::cout << "inverseMatrix: matrix is not quadratic." << std::endl;
		return result;
	}

	lrDecomposition(RELCOLUMNMAX);

	for (uint k = 0; k < m_NumberRows; k++)
	{
		Vector rightSide(m_NumberRows);
		rightSide(k) = 1.0;
		Vector vec = solve(rightSide);
		result.setColumn(k, vec);
	}
	
	return result;
}

Vector Matrix::solve(const Vector &rightSide)
{
	uint n = m_NumberRows-1;

	Vector result(m_NumberRows);

	if (m_NumberRows != rightSide.getSize())
	{
		std::cout << "solve: not the same dimension! (" << m_NumberRows << " != " << rightSide.getSize() << ")" << std::endl;
		return result;
	}

	Vector b = rightSide;

	// Swap rows of rightSide
	double temp;
	for (uint k = 0; k < n; k++)
	{
		uint p_k = m_RowSwaps[k];

		if (p_k != k)
		{
			temp = b(k);
			b(k) = b(p_k);
			b(p_k) = temp;
		}
	}

	Vector c(m_NumberRows);

	// Forward substitution
	for (int i = 0; i <=n; i++)
	{
		c(i) = b(i);
		for (int j = 0; j <= i-1; j++)
			c(i) -= m_Data[i*m_NumberColumns + j] * c(j);
	}

	// Backward subsitution
	for (int i = n; i >= 0; i--)
	{
		double s = c(i);

		for (uint k = i+1; k <= n; k++)
			s -= m_Data[i*m_NumberColumns + k] * result(k);

		if (m_Data[i*m_NumberColumns + i] == 0.0)
		{
			std::cout << "a_{" << i << "," << i << "} = 0.0. " << std::endl;
			return Vector(m_NumberRows);
		}

		result(i) = s / m_Data[i*m_NumberColumns + i];
	}

	return result;
}

Vector Matrix::leastSquares(const Vector &rightSide)
{
	// A is m x n-Matrix, and b has to be of dimension m.
	if (rightSide.getSize() != m_NumberRows)
	{
		std::cout << "leastSquares: dimensions don't fit." << std::endl;
		return Vector(m_NumberRows);
	}

	// Compute A^T:
	Matrix at(m_NumberColumns, m_NumberRows);

	for (uint i = 0; i < m_NumberRows; i++)
		for	(uint j = 0; j < m_NumberColumns; j++)
			at(j,i) = m_Data[i*m_NumberColumns + j];

//	for (uint i = 0; i < at.getNumberRows(); i++)
//	{
//		std::cout << "[ ";
//		for (uint j = 0; j < at.getNumberColumns(); j++)
//		{
//			std::cout << at(i,j) << " ";
//		}
//		std::cout << "]" << std::endl;
//	}
//	std::cout << std::endl;
	// Computer A^T * A:
	Matrix ata = at * (*this);

//	for (uint i = 0; i < ata.getNumberRows(); i++)
//	{
//		std::cout << "[ ";
//		for (uint j = 0; j < ata.getNumberColumns(); j++)
//		{
//			std::cout << ata(i,j) << " ";
//		}
//		std::cout << "]" << std::endl;
//	}

	Vector atb = at*rightSide;

//	std::cout << "(";
//	for (uint i = 0; i < atb.getSize()-1; i++)
//		std::cout << atb(i) << ", ";
//	std::cout << atb(atb.getSize()-1) << ")" << std::endl;

	ata.lrDecomposition(RELCOLUMNMAX);
	return ata.solve(atb);
}

double &Matrix::operator () (const uint i, const uint j)
{
	double temp = 0.0;
	if (i >= m_NumberRows || j >= m_NumberColumns)
	{
		std::cout << "(): indices " << i << ", " << j << " exceed matrix size!" << std::endl;
		return temp;
	}

	return m_Data[i*m_NumberColumns + j];
}

const double &Matrix::operator () (const uint i, const uint j) const
{
	double temp = 0.0;
	if (i >= m_NumberRows || j >= m_NumberColumns)
	{
		std::cout << "(): indices " << i << ", " << j << " exceed matrix size!" << std::endl;
		return temp;
	}

	return m_Data[i*m_NumberColumns + j];
}

Matrix &Matrix::operator = (const Matrix &mat)
{
	if ((m_NumberRows != mat.getNumberRows()) || (m_NumberColumns != mat.getNumberColumns()))
	{
		std::cout << "= operator: not the same dimension!" << std::endl;
		return *this;
	}

	for (uint i = 0; i < m_NumberRows; i++)
		for (uint j = 0; j < m_NumberColumns; j++)
			m_Data[i*m_NumberColumns + j] = mat(i,j);

	return *this;
}

Matrix Matrix::operator + (const Matrix &mat)
{
	Matrix result(m_NumberRows, m_NumberColumns);

	if ((m_NumberRows != mat.getNumberRows()) || (m_NumberColumns != mat.getNumberColumns()))
	{
		std::cout << "+ operator: not the same dimension!" << std::endl;
		return result;
	}

	for (uint i = 0; i < m_NumberRows; i++)
		for (uint j = 0; j < m_NumberColumns; j++)
			result(i,j) = m_Data[i*m_NumberColumns + j] + mat(i,j);

	return result;
}

Matrix Matrix::operator - (const Matrix &mat)
{
	Matrix result(m_NumberRows, m_NumberColumns);

	if ((m_NumberRows != mat.getNumberRows()) || (m_NumberColumns != mat.getNumberColumns()))
	{
		std::cout << "- operator: not the same dimension!" << std::endl;
		return result;
	}

	for (uint i = 0; i < m_NumberRows; i++)
		for (uint j = 0; j < m_NumberColumns; j++)
			result(i,j) = m_Data[i*m_NumberColumns + j] - mat(i,j);

	return result;
}

Matrix Matrix::operator - ()
{
	Matrix result(m_NumberRows, m_NumberColumns);

	for (uint i = 0; i < m_NumberRows; i++)
	{
		for (uint j = 0; j < m_NumberColumns; j++)
		{
			if (m_Data[i*m_NumberColumns + j] != 0.0)
				result(i,j) = -m_Data[i*m_NumberColumns + j];
		}
	}

	return result;
}

Matrix Matrix::operator * (const Matrix &mat)
{
	Matrix result(m_NumberRows, mat.getNumberColumns());

	if (m_NumberColumns != mat.getNumberRows())
	{
		std::cout << "* operator: not the same dimension!" << std::endl;
		return result;
	}
	
	for (uint i = 0; i < m_NumberRows; i++)
		for (uint j = 0; j < mat.getNumberColumns(); j++)
			for (uint k = 0; k < m_NumberColumns; k++)
				result(i,j) += m_Data[i*m_NumberColumns+k] * mat(k,j);
	
	return result;
}

Matrix Matrix::operator * (const double &scale)
{
	Matrix result(m_NumberRows, m_NumberColumns);

	for (uint i = 0; i < m_NumberRows; i++)
		for (uint j = 0; j < m_NumberColumns; j++)
			result(i,j) = scale * m_Data[i*m_NumberColumns + j];

	return result;
}

Vector Matrix::operator * (const Vector &vec)
{
	Vector result(m_NumberRows);

	if (m_NumberColumns != vec.getSize())
	{
		std::cout << "* operator: not the same dimension! (" << m_NumberRows << " != " << vec.getSize() << ")" << std::endl;
		return result;
	}

	for (uint j = 0; j < m_NumberColumns; j++)
		for (uint i = 0; i < m_NumberRows; i++)
			result(i) += m_Data[i*m_NumberColumns + j] * vec(j);

	return result;
}
