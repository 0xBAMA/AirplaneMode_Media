#ifndef VECTOR
#define VECTOR

#define base_type double // easiest way to swap this I think is to have it here

template <class T>
class vector2{
public:
  T values [2];

  vector2 ()         { values[0]=T(0); values[1]=T(0); }
  vector2 (T x, T y) { values[0]=x;    values[1]=y;    }

  //  +,- operators
  const vector2<T> operator+(const vector2<T>& other) const { return vector2(this->values[0]+other.values[0], this->values[1]+other.values[1]); }
  const vector2<T>& operator+=(const vector2<T>& other) { this->values[0]+=other.values[0], this->values[1]+=other.values[1]; }

  const vector2<T> operator-(const vector2<T>& other) const { return vector2(this->values[0]-other.values[0], this->values[1]-other.values[1]); }
  const vector2<T>& operator-=(const vector2<T>& other) { this->values[0]-=other.values[0], this->values[1]-=other.values[1]; }

  //  multiplication/division by a scalar of the same type - scale each element
  const vector2<T> operator*(const T& scalar) const { return vector2(this->values[0]*scalar, this->values[1]*scalar); }
  const vector2<T>& operator*=(const T& scalar) { this->values[0]*=scalar, this->values[1]*=scalar; return *this; }

  const vector2<T> operator/(const T& scalar) const { return vector2(this->values[0]/scalar, this->values[1]/scalar); }
  const vector2<T>& operator/=(const T& scalar) { this->values[0]/=scalar, this->values[1]/=scalar; return *this; }

  //  multiplication by a vector of the same type - elementwise multiply (hadamard product)
  const vector2<T> operator*(const vector2<T>& other) const { return vector2(this->values[0]*other.values[0], this->values[1]*other.values[1]); }
  const vector2<T>& operator*=(const vector2<T>& other) { this->values[0]*=other.values[0], this->values[1]*=other.values[1]; return *this; }
};

template <class T>
T dot(vector2<T> v1, vector2<T> v2) { return v1[0]*v2[0] + v1[1]*v2[1]; }

template <class T> // squared length
T len2(vector2<T> v) { return dot(v,v); }

template <class T> // vector length
T len(vector2<T> v) { return sqrt(len2(v)); }

template <class T> // return unit length colinear vector
vector2<T> normalize(vector2<T> in) { T length = len(in); return in/length; }

using vector2f = vector2<float>;
using vector2d = vector2<double>;

// --------
// --------
// --------

template <class T>
class vector3{
public:
  T values [3];

  vector3 ()              { values[0]=T(0); values[1]=T(0);  values[2]=T(0); }
  vector3 (T x, T y, T z) { values[0]=x;    values[1]=y;     values[2]=z;    }

  //  +,- operators
  const vector3<T> operator+(const vector3<T>& other) const { return vector3(this->values[0]+other.values[0], this->values[1]+other.values[1], this->values[2]+other.values[2]); }
  const vector3<T>& operator+=(const vector3<T>& other) { this->values[0]+=other.values[0], this->values[1]+=other.values[1], this->values[2]+=other.values[2]; return *this; }

  const vector3<T> operator-(const vector3<T>& other) const { return vector3(this->values[0]-other.values[0], this->values[1]-other.values[1], this->values[2]-other.values[2]); }
  const vector3<T>& operator-=(const vector3<T>& other) { this->values[0]-=other.values[0], this->values[1]-=other.values[1], this->values[2]-=other.values[2]; return *this; }

  //  multiplication/division by a scalar of the same type - scale each element
  const vector3<T> operator*(const T& scalar) const { return vector3(this->values[0]*scalar, this->values[1]*scalar, this->values[2]*scalar); }
  const vector3<T>& operator*=(const T& scalar) { this->values[0]*=scalar, this->values[1]*=scalar, this->values[2]*=scalar; return *this; }

  const vector3<T> operator/(const T& scalar) const { return vector3(this->values[0]/scalar, this->values[1]/scalar, this->values[2]/scalar); }
  const vector3<T>& operator/=(const T& scalar) { this->values[0]/=scalar, this->values[1]/=scalar, this->values[2]/=scalar; return *this; }

  //  multiplication by a vector of the same type - elementwise multiply (hadamard product)
  const vector3<T> operator*(const vector3<T>& other) const { return vector3(this->values[0]*other.values[0], this->values[1]*other.values[1], this->values[2]*other.values[2]); }
  const vector3<T>& operator*=(const vector3<T>& other) { this->values[0]*=other.values[0], this->values[1]*=other.values[1], this->values[2]*=other.values[2]; return *this; }
};

template <class T>
const T dot(vector3<T> v1, vector3<T> v2) { return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2]; }

template <class T> // squared length
const T len2(vector3<T> v) { return dot(v,v); }

template <class T> // vector length
const T len(vector3<T> v) { return sqrt(len2(v)); }

template <class T> // return unit length colinear vector
const vector3<T> normalize(vector3<T> in) { T length = len(in); return in/length; }

template <class T> //  cross product
const vector3<T> cross(vector3<T> a, vector3<T> b) {
  vector3<T> product;
  product.values[0] =   a.values[1] * b.values[2] - a.values[2] * b.values[1];
  product.values[1] = -(a.values[0] * b.values[2] - a.values[2] * b.values[0]);
  product.values[2] =   a.values[0] * b.values[1] - a.values[1] * b.values[0];
  return product;
}

// default types, using base_type above
using vector3f = vector3<float>;
using vector3d = vector3<double>;
using vec2 = vector2<base_type>;
using vec3 = vector3<base_type>;

#endif
