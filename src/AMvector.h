#ifndef VECTOR
#define VECTOR


template <class T>
class vec2{
public:
  T values [2];

  vec2 ()         { values[0]=T(0); values[1]=T(0); }
  vec2 (T x, T y) { values[0]=x;    values[1]=y;    }

  //  +,- operators
  const vec2<T> operator+(const vec2<T>& other) const { return vec2(this->values[0]+other.values[0], this->values[1]+other.values[1]); }
  const vec2<T> operator-(const vec2<T>& other) const { return vec2(this->values[0]-other.values[0], this->values[1]-other.values[1]); }

  //  multiplication/division by a scalar of the same type - scale each element
  const vec2<T> operator*(const T& scalar) const { return vec2(this->values[0]*scalar, this->values[1]*scalar); }

  //  multiplication/division by a vector of the same type - elementwise multiply (hadamard product)
  const vec2<T> operator*(const vec2<T>& other) const { return vec2(this->values[0]*other.values[0], this->values[1]*other.values[1]); }
};

template <class T>
T dot(vec2<T> v1, vec2<T> v2) { return v1[0]*v2[0] + v1[1]*v2[1]; }

template <class T> // squared length
T len2(vec2<T> v) { return dot(v,v); }

template <class T> // vector length
T len(vec2<T> v) { return sqrt(len2(v)); }

template <class T> // return unit length colinear vector
vec2<T> normalize(vec2<T> in) { T length = len(in); return in/length; }

using vec2f = vec2<float>;
using vec2d = vec2<double>;

// --------
// --------
// --------


template <class T>
class vec3{
public:
  T values [3];

  vec3 ()              { values[0]=T(0); values[1]=T(0);  values[2]=T(0); }
  vec3 (T x, T y, T z) { values[0]=x;    values[1]=y;     values[2]=z;    }

  //  +,- operators
  const vec3<T> operator+(const vec3<T>& other) const { return vec3(this->values[0]+other.values[0], this->values[1]+other.values[1], this->values[2]+other.values[2]); }
  const vec3<T> operator-(const vec3<T>& other) const { return vec3(this->values[0]-other.values[0], this->values[1]-other.values[1], this->values[2]-other.values[2]); }

  //  multiplication/division by a scalar of the same type - scale each element
  const vec3<T> operator*(const T& scalar) const { return vec3(this->values[0]*scalar, this->values[1]*scalar, this->values[2]*scalar); }

  //  multiplication/division by a vector of the same type - elementwise multiply (hadamard product)
  const vec3<T> operator*(const vec3<T>& other) const { return vec3(this->values[0]*other.values[0], this->values[1]*other.values[1], this->values[2]*other.values[2]); }
};

template <class T>
const T dot(vec3<T> v1, vec3<T> v2) { return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2]; }

template <class T> // squared length
const T len2(vec3<T> v) { return dot(v,v); }

template <class T> // vector length
const T len(vec3<T> v) { return sqrt(len2(v)); }

template <class T> // return unit length colinear vector
const vec3<T> normalize(vec3<T> in) { T length = len(in); return in/length; }

template <class T> //  cross product
const vec3<T> cross(vec3<T> a, vec3<T> b) {
  vec3<T> product;
  product.values[0] =   a.values[1] * b.values[2] - a.values[2] * b.values[1];
  product.values[1] = -(a.values[0] * b.values[2] - a.values[2] * b.values[0]);
  product.values[2] =   a.values[0] * b.values[1] - a.values[1] * b.values[0];
  return product;
}

using vec3f = vec3<float>;
using vec3d = vec3<double>;

#endif
