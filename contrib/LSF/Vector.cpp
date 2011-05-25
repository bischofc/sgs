/*
 * Code by Peter Salz, TU Kaiserslautern, Germany, 2008
 */

#include "Vector.h"

Vector::Vector(uint size)
{
	m_Size = size;
	m_Data = new double[m_Size];
	for (uint i = 0; i < m_Size; i++)
		m_Data[i] = 0.0;
}

Vector::Vector()
{
	m_Size = 0;
	m_Data = NULL;
}

Vector::Vector(uint size, double *data)
{
	if (data == NULL)
	{
		std::cout << "Vector() got NULL parameter!" << std::endl;
		m_Size = 0;
		m_Data = NULL;
	}
	else
	{
		m_Size = size;
		m_Data = data;
	}
}

Vector::Vector(const Vector &vec)
{ 
	m_Size = vec.getSize();
	m_Data = new double[m_Size];
	for (uint i = 0; i < m_Size; i++)
		m_Data[i] = vec(i);
}

Vector::~Vector()
{
	if (m_Data != NULL)
		delete [] m_Data;
}

void Vector::setDataAt(uint index, double value)
{
	if (index >= m_Size)
	{
		std::cout << "setDataAt: index " << index << " exceeds array size!" << std::endl;
		return;
	}

	m_Data[index] = value;
}

void Vector::setSize(uint size)
{
	if (m_Data != NULL)
		delete [] m_Data;

	m_Size = size;
	m_Data = new double[m_Size];
	for (uint i = 0; i < m_Size; i++)
		m_Data[i] = 0.0;
}

uint Vector::getSize() const
{
	return m_Size;
}

double Vector::getLength() const
{
	double sqrVec = 0.0;
	for (uint i = 0; i < m_Size; i++)
		sqrVec += m_Data[i]*m_Data[i];
	return sqrt(sqrVec);
}

void Vector::normalize()
{
	double length = getLength();

	if (length == 0.0)
		return;

	for (uint i = 0; i < m_Size; i++)
		m_Data[i] /= length;
}

double &Vector::operator () (const uint index)
{
	double temp = 0.0;
	if (index >= m_Size)
	{
		std::cout << "(): index " << index << " exceeds array size!" << std::endl;
		return temp;
	}

	return m_Data[index];
}

const double &Vector::operator () (const uint index) const
{
	double temp = 0.0;
	if (index >= m_Size)
	{
		std::cout << "(): index " << index << " exceeds array size!" << std::endl;
		return temp;
	}

	return m_Data[index];
}

Vector &Vector::operator = (const Vector &vec)
{
	if (m_Size == 0)
	{
		m_Size = vec.getSize();
		m_Data = new double[m_Size];
	}

	if (vec.getSize() != m_Size)
	{
		std::cout << "= operator: not the same dimension! (" << m_Size << " != " << vec.getSize() << ")" << std::endl;
		return *this;
	}

	for (uint i = 0; i < m_Size; i++)
		m_Data[i] = vec(i);

	return *this;
}

Vector Vector::operator +(const Vector &vec)
{
	Vector result(m_Size);

	if (vec.getSize() != m_Size)
	{
		std::cout << "+ operator: not the same dimension! (" << m_Size << " != " << vec.getSize() << ")" << std::endl;
		return result;
	}

	for (uint i = 0; i < m_Size; i++)
		result(i) =  m_Data[i] + vec(i);

	return result;
}
	
Vector Vector::operator -(const Vector &vec)
{
	Vector result(m_Size);

	if (vec.getSize() != m_Size)
	{
		std::cout << "- operator: not the same dimension! (" << m_Size << " != " << vec.getSize() << ")" << std::endl;
		return result;
	}

	for (uint i = 0; i < m_Size; i++)
		result.setDataAt(i, m_Data[i] - vec(i));

	return result;
}
	
Vector Vector::operator -()
{
	Vector result(m_Size);

	for (uint i = 0; i < m_Size; i++)
	{
		if (m_Data[i] != 0.0)
			result.setDataAt(i, -m_Data[i]);
	}

	return result;
}

double Vector::operator *(Vector &vec)
{
	if (m_Size != vec.getSize())
	{
		std::cout << "* operator: not the same dimension! (" << m_Size << " != " << vec.getSize() << ")" << std::endl;
		return 0.0;
	}

	double result = 0.0;

	for (uint i = 0; i < m_Size; i++)
		result += m_Data[i] * vec(i);

	return result;
}
	
Vector Vector::operator *(double scale)
{
	Vector result(m_Size);

	for (uint i = 0; i < m_Size; i++)
		result(i) *= scale;

	return result;
}

Vector Vector::operator %(Vector &vec)
{
	Vector result(m_Size);

	if ((m_Size != vec.getSize()) && (m_Size != 3))
	{
		std::cout << "% operator: only 3-dimensional!! (" << m_Size << " != " << vec.getSize() << ")" << std::endl;
		return result;
	}

	result(0) = m_Data[1]*vec(2) - m_Data[2]*vec(1);
	result(1) = m_Data[2]*vec(0) - m_Data[0]*vec(2);
	result(2) = m_Data[0]*vec(1) - m_Data[1]*vec(0);

	return result;
}

Vector Vector::operator *(Matrix &mat)
{
	Vector result(mat.getNumberRows());

	if (m_Size != mat.getNumberColumns())
	{
		std::cout << "* operator: not the same dimension! (" << m_Size << " != " << mat.getNumberColumns() << ")" << std::endl;
		return result;
	}

	for (uint j = 0; j < m_Size; j++)
		for (uint i = 0; i < mat.getNumberRows(); i++)
			result(i) += m_Data[j] * mat(i,j);

	return result;
}

Vector Vector::operator += (const Vector &vec)
{
	if (m_Size != vec.getSize())
	{
		std::cout << "+= operator: not the same dimension! (" << m_Size << " != " << vec.getSize() << ")" << std::endl;
		return Vector(m_Size);
	}

	for (uint i = 0; i < m_Size; i++)
		m_Data[i] += vec(i);

	return *this;
}

Vector Vector::operator -= (const Vector &vec)
{
	if (m_Size != vec.getSize())
	{
		std::cout << "-= operator: not the same dimension! (" << m_Size << " != " << vec.getSize() << ")" << std::endl;
		return Vector(m_Size);
	}

	for (uint i = 0; i < m_Size; i++)
		m_Data[i] -= vec(i);

	return *this;	
}

Vector Vector::operator %= (const Vector &vec)
{
	Vector result(m_Size);

	if ((m_Size != vec.getSize()) && (m_Size != 3))
	{
		std::cout << "%= operator: only 3-dimensional!! (" << m_Size << " != " << vec.getSize() << ")" << std::endl;
		return result;
	}

	result(0) = m_Data[1]*vec(2) - m_Data[2]*vec(1);
	result(1) = m_Data[2]*vec(0) - m_Data[0]*vec(2);
	result(2) = m_Data[0]*vec(1) - m_Data[1]*vec(0);

	m_Data[0] = result(0);
	m_Data[1] = result(1);
	m_Data[2] = result(2);

	return *this;
}

Vector Vector::operator *= (const double scale)
{
	for (uint i = 0; i < m_Size; i++)
		m_Data[i] *= scale;

	return *this;	
}
	
