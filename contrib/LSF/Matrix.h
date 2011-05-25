/*
 * Code by Peter Salz, TU Kaiserslautern, Germany, 2008
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>
#include <iostream>

#include "Vector.h"

typedef unsigned int uint;

class Vector;

enum LRMODE { DIAGONAL, COLUMNMAX, RELCOLUMNMAX };

class Matrix
{
public:
	Matrix();
	Matrix(uint numberRows, uint numberColumns);
	Matrix(uint numerRows, uint numberColumns, double *data);
	Matrix (const Matrix &mat);
	~Matrix();

	uint getNumberRows() const;
	uint getNumberColumns() const;
	void setSize(uint numberRows, uint numberColumns);
	Vector getColumn(const uint &index) const;
	Vector getRow(const uint &index) const;
	void setColumn(const uint &index, const Vector &vec);
	void setRow(const uint &index, const Vector &vec);

	Vector backwardSubstitution(const Vector &rightSide);
	void lrDecomposition(enum LRMODE);
	void choleskyDecomposition();
	Vector solve(const Vector &rightSide);
	Matrix inverseMatrix();
	Vector leastSquares(const Vector &rightSide);

	double &operator () (const uint i, const uint j);
	const double &operator () (const uint i, const uint j) const;
	Matrix &operator = (const Matrix &mat);
	Matrix operator + (const Matrix &mat);
	Matrix operator - (const Matrix &mat);
	Matrix operator - ();
	Matrix operator * (const Matrix &mat);
	Matrix operator * (const double &scale);
	Vector operator * (const Vector &vec);

protected:
	double *m_Data;
	uint m_NumberRows;
	uint m_NumberColumns;
	uint *m_RowSwaps;
};


#endif // MATRIX_H
