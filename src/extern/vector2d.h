// GNU General Public License Agreement
// Copyright (C) 2004-2010 CodeCogs, Zyba Ltd, Broadwood, Holford, TA5 1DU, England.
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by CodeCogs. 
// You must retain a copy of this licence in all copies. 
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
// PARTICULAR PURPOSE. See the GNU General Public License for more details.
// ---------------------------------------------------------------------------------
//! \b Vector2D class is representing cartesian mathematical vector in two dimensional space. 


//! \b Vector2D class is representing cartesian mathematical vector in two dimensional space. 

#ifndef _CodeCogs_Vector2D_h
#define _CodeCogs_Vector2D_h

#include <math.h>

#include <iostream>

//using std::istream;
//using std::ostream;

using namespace std;

//! \b Vector2D class is representing cartesian mathematical vector in two dimensional space.
template <class RealType> class Vector3D;

//! \b Vector2D class is representing cartesian mathematical vector in two dimensional space.

template <class RealType>
class Vector2D{
public:

//! components of 2D vector can be accessed using different synonims or through pointer to all of them
union
{
     struct { RealType x, y; };
     struct { RealType u, v; };
     RealType xy[2];
     RealType uv[2];
   };

//! 2D vector can be initialized either passing X and Y coordinates of 2D vector, where X=0 and Y=0 are defult values if X and/or Y are not specified

Vector2D (RealType X=0, RealType Y=0) : x(X),y(Y)
{ }

//! 2D vector can also be initialized passing a pointer to RealType components (2 of them)

Vector2D (RealType coords[2])
{ x = coords[0]; y = coords[1]; }

//! operator = can be used between two 2D vectors, or 2D vector and pointer to two RealType components (describing a 2D vector)

inline void operator =(RealType coords[2])
{ x = coords[0]; y = coords[1]; }

//! getLength returns single value describing distance of Vector from Zero Vector in 2D
inline double getLength ()
{ return sqrt(x*x+y*y); }

//! additive translation

inline void operator +=(const Vector2D <RealType>&op2)
{ x+=op2.x, y+=op2.y; }

//! substractive translation

inline void operator -=(const Vector2D <RealType>&op2)
{ x-=op2.x, y-=op2.y; }

//! operator *= and /= are provided to modify initial length of vector

void operator *=(double scalar)
{ x*=scalar; y*=scalar; }


void operator /=(double scalar)
{ x/=scalar; y/=scalar; }

//! comparison of two 2D vectors are performed using standard == operators from C/C++

const bool operator ==(const Vector2D <RealType>&V)const
{ return (x == V.x && y == V.y); }

//! comparison of two 2D vectors are performed using standard != operators from C/C++

const bool operator !=(const Vector2D <RealType>&V)const
{ return !(*this == V); }

//! additive translation

Vector2D <RealType> operator +(const Vector2D <RealType>&v2)
{
     return Vector2D <RealType> (x+v2.x, y+v2.y);   
   }

//! substractive translation

Vector2D <RealType> operator -(const Vector2D <RealType>&v2)
{
     return Vector2D <RealType> (x-v2.x, y-v2.y);   
   }

//! invert sign operation (rotation by 180 degrees)

Vector2D <RealType> operator - ()const
{
     return Vector2D <RealType>(-x, -y);
   }

//! returns 2D vector representing input 2D vector stretched by scalar

Vector2D <RealType> operator *(double scalar)
{
     return Vector2D <RealType>(x*scalar, y*scalar); 
   }

//! distance of input 2D vector is divided by scalar, Zero Vector stays Zero Vector

Vector2D <RealType> operator /(double scalar)
{
     return Vector2D <RealType>(x/scalar, y/scalar); 
   }

//! operator * provides dot-product for two input 2D vectors

double operator *(const Vector2D <RealType>&v2)
{ return x*v2.x + y*v2.y; }

//! operator ^ stands for cross product of two vectors returning Vector3D which is perpendicular to both input 3D vectors

RealType operator ^(const Vector2D <RealType> &v2)
{
     return x*v2.y-v2.x*y;
   }

//! normalize modifies 2D vector so it&#039;s length becomes one, keeping same direction
void normalize ()
{ *this /= getLength(); }

//! getNormalized returns a 2D unit vector of same direction as input 2D vector
Vector2D <RealType> getNormalized ()
{ Vector2D <RealType> norm (*this); norm.normalize(); return norm; }

//! returns 2D vector but with components of double format
Vector2D <double> getDouble ()
{ return Vector2D <double> (x, y); }

//! returns 2D vector but with components of float format
Vector2D <float> getFloat ()
{ return Vector2D <float> (x, y); }

//! output of input 2D vector on the stream in "X Y" formatstream operations will work with custom data types only if << and >> are overloaded for streams

friend ostream &operator <<(ostream &os, const Vector2D <RealType> &v)
{
     os << v.x << " " << v.y;
     return os;
   }


friend istream &operator >>(istream &is, const Vector2D <RealType> &v)
{
     RealType temp;
     is >> temp; v.x = temp;
     is >> temp; v.y = temp;
     return is;
   }


bool isColinearTo(const Vector2D <RealType>& point1)
{
     if (point1.getZ() != 0) return false;
     RealType d = point1.getX()*this->y - this->x*point1.getY();

if (d == 0) return true;

else return false;

}

//! return true if this 2D vector is Zero vector in 2D
bool isZero ()
{
     if (x==0 && y==0) return true;
     else return false;
   }

//! return true if this 2D vector is Zero vector in 2D
bool isDegenerate ()
{
     if (x==0 && y==0) return true;
     else return false;
   }

//! assigns 3D vector to 2D vector ignoring Z component of 3D vector

void operator =(const Vector3D <RealType> &op2)
{
     x = op2.x;
     y = op2.y;
   }

//! get3D method returns 2D vector converted to 3D vector assuming Z=0
Vector3D <RealType> get3D ()
{
     return Vector3D <RealType> (x, y, 0);
   }

//! returns a length of the vector on the power of 2 (eg. before using sqrt which is slow)
inline RealType getPoweredLength ()
{ return x*x+y*y; }
};


//! assuming that most of the people would use 2D vectors in float or double form
//! typedefs offer a hungarian notation naming types
//! Vec2f would be 2D vector with float components
typedef Vector2D <float> Vec2f;

//! Vec2d would be 2D vector with double components
typedef Vector2D <double> Vec2d;

template <class RealType>
Vector2D<RealType> intersection(Vector2D<RealType> A, Vector2D<RealType> B, Vector2D<RealType> C, Vector2D<RealType> D, bool& intersects = false)
{
     // Line AB represented as a1x + b1y = c1
     double a = B.y - A.y;
     double b = A.x - B.x;
     double c = a*(A.x) + b*(A.y);
     // Line CD represented as a2x + b2y = c2
     double a1 = D.y - C.y;
     double b1 = C.x - D.x;
     double c1 = a1*(C.x)+ b1*(C.y);
     double det = a*b1 - a1*b;
     if (det == 0) {
          intersects = false;
          return Vector2D<RealType>();
     } else {
          intersects = true;
          double x = (b1*c - b*c1)/det;
          double y = (a*c1 - a1*c)/det;
          return {x,y};
     }
}

#endif

