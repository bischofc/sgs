/*
 * Code by Peter Salz, TU Kaiserslautern, Germany, 2008
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include <iostream>

#include "Matrix.h"

typedef unsigned int uint;

class Matrix;

class Vector
{
public:
	Vector();
	Vector(uint size);
	Vector(uint size, double *data);
	Vector (const Vector &vec);
	~Vector();

	void setDataAt(uint index, double value);
	void setSize(uint size);
	uint getSize() const;

	double getLength() const;
	void normalize();

	double &operator ()(uint index);
	const double &operator ()(uint index) const;

	Vector &operator =(const Vector &vec);
	Vector operator +(const Vector &vec);
	Vector operator -(const Vector &vec);
	Vector operator -();

	double operator *(Vector &vec);
	Vector operator *(double scale);
	Vector operator %(Vector &vec);
	Vector operator *(Matrix &mat);

	Vector operator += (const Vector &vec);
	Vector operator -= (const Vector &vec);
	Vector operator %= (const Vector &vec);
	Vector operator *= (const double scale);

	//friend std::ostream &operator << (std::ostream &s, const Vector &v);

protected:
	double *m_Data;
	uint m_Size;
};


#endif // VECTOR_H
