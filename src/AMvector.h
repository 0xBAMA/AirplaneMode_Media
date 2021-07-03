#include "includes.h"


template <class T>
class vec2{
  T values [2];
public:
  vec2 ()         { values[0]=T(0); values[1]=T(0); }
  vec2 (T x, T y) { values[0]=x;    values[1]=y;    }

  //  +,- operators
  vec2<T> operator+(const vec2<T>& other) { return vec2(this->values[0]+other.values[0], this->values[1]+other.values[1]); }
  vec2<T> operator-(const vec2<T>& other) { return vec2(this->values[0]-other.values[0], this->values[1]-other.values[1]); }

  //  multiplication/division by a scalar of the same type - scale each element
  vec2<T> operator*(const T& scalar) { return vec2(this->values[0]*scalar, this->values[1]*scalar); }

  //  multiplication/division by a vector of the same type - elementwise multiply (hadamard product)
  vec2<T> operator*(const vec2<T>& other) { return vec2(this->values[0]*other.values[0], this->values[1]*other.values[1]); }
};

template <class T>
T dot(vec2<T> v1, vec2<T> v2) { return v1[0]*v2[0] + v1[1]*v2[1]; }

template <class T> // squared length
T len2(vec2<T> v) { return dot(v,v); }

template <class T> // vector length
T len(vec2<T> v) { return sqrt(len2(v)); }

template <class T> // return unit length colinear vector
vec2<T> normalize(vec2<T> in) { T length = len(in); return in/length; }


// --------
// --------
// --------


template <class T>
class vec3{
  T values [3];
public:
  vec3 ()              { values[0]=T(0); values[1]=T(0);  values[2]=T(0); }
  vec3 (T x, T y, T z) { values[0]=x;    values[1]=y;     values[2]=z;    }

  //  +,- operators
  vec3<T> operator+(const vec3<T>& other) { return vec3(this->values[0]+other.values[0], this->values[1]+other.values[1], this->values[2]+other.values[2]); }
  vec3<T> operator-(const vec3<T>& other) { return vec3(this->values[0]-other.values[0], this->values[1]-other.values[1], this->values[2]-other.values[2]); }

  //  multiplication/division by a scalar of the same type - scale each element
  vec3<T> operator*(const T& scalar) { return vec3(this->values[0]*scalar, this->values[1]*scalar, this->values[2]*scalar); }

  //  multiplication/division by a vector of the same type - elementwise multiply (hadamard product)
  vec3<T> operator*(const vec3<T>& other) { return vec3(this->values[0]*other.values[0], this->values[1]*other.values[1], this->values[2]*other.values[2]); }
};

template <class T>
T dot(vec3<T> v1, vec3<T> v2) { return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2]; }

template <class T> // squared length
T len2(vec3<T> v) { return dot(v,v); }

template <class T> // vector length
T len(vec3<T> v) { return sqrt(len2(v)); }

template <class T> // return unit length colinear vector
vec3<T> normalize(vec3<T> in) { T length = len(in); return in/length; }

template <class T> //  cross product
vec3<T> cross(vec3<T> a, vec3<T> b) {
  vec3<T> product;
  product.values[0] =   a.values[1] * b.values[2] - a.values[2] * b.values[1];
  product.values[1] = -(a.values[0] * b.values[2] - a.values[2] * b.values[0]);
  product.values[2] =   a.values[0] * b.values[1] - a.values[1] * b.values[0];
  return product;
}
