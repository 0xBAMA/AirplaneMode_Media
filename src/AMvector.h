#ifndef VECTOR
#define VECTOR

#include <cmath>
#include <random>
#include <chrono>

// easiest way to swap type behavior
#define base_type double

// pi define
#define PI 3.1415926535897932384626433832795

template <class T>
class vector2{
public:
  T values [2];

  vector2 ()         { values[0]=T(0); values[1]=T(0); }
  vector2 (T val)    { values[0]=val;  values[1]=val;  }
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

  //  division by a vector of the same type - elementwise divide
  const vector2<T> operator/(const vector2<T>& other) const { return vector2(this->values[0]/other.values[0], this->values[1]/other.values[1]); }
  const vector2<T>& operator/=(const vector2<T>& other) { this->values[0]/=other.values[0], this->values[1]/=other.values[1]; return *this; }
};

// addition/subtraction in the other order
template <class T>
const vector2<T> operator+(const T& scalar, const vector2<T>& vec) { return vector2<T>(vec.values[0]+scalar, vec.values[1]+scalar); }
template <class T>
const vector2<T> operator-(const T& scalar, const vector2<T>& vec) { return vector2<T>(vec.values[0]-scalar, vec.values[1]-scalar); }

// multiplication/division in the other order
template <class T>
const vector2<T> operator*(const T& scalar, const vector2<T>& vec) { return vector2<T>(vec.values[0]*scalar, vec.values[1]*scalar); }
template <class T>
const vector2<T> operator/(const T& scalar, const vector2<T>& vec) { return vector2<T>(vec.values[0]/scalar, vec.values[1]/scalar); }

template <class T>
T dot(vector2<T> v1, vector2<T> v2) { return v1.values[0]*v2.values[0] + v1.values[1]*v2.values[1]; }

template <class T> // squared length
T len2(vector2<T> v) { return dot(v,v); }

template <class T> // vector length
T len(vector2<T> v) { return sqrt(len2(v)); }

template <class T> // return unit length colinear vector
vector2<T> normalize(vector2<T> in) { T length = len(in); return in/length; }

// --------
// --------
// --------

template <class T>
class vector3{
public:
  T values [3];

  vector3 ()              { values[0]=T(0); values[1]=T(0);  values[2]=T(0); }
  vector3 (T val)         { values[0]=val;  values[1]=val;   values[2]=val;  }
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

  //  division by a vector of the same type - elementwise divide
  const vector3<T> operator/(const vector3<T>& other) const { return vector3(this->values[0]/other.values[0], this->values[1]/other.values[1], this->values[2]/other.values[2]); }
  const vector3<T>& operator/=(const vector3<T>& other) { this->values[0]/=other.values[0], this->values[1]/=other.values[1], this->values[2]/=other.values[2]; return *this; }
};

// addition/subtraction in the other order
template <class T>
const vector3<T> operator+(const T& scalar, const vector3<T>& vec) { return vector3<T>(vec.values[0]+scalar, vec.values[1]+scalar, vec.values[2]+scalar); }
template <class T>
const vector3<T> operator-(const T& scalar, const vector3<T>& vec) { return vector3<T>(vec.values[0]-scalar, vec.values[1]-scalar, vec.values[2]-scalar); }

// multiplication/division in the other order
template <class T>
const vector3<T> operator*(const T& scalar, const vector3<T>& vec) { return vector3<T>(vec.values[0]*scalar, vec.values[1]*scalar, vec.values[2]*scalar); }
template <class T>
const vector3<T> operator/(const T& scalar, const vector3<T>& vec) { return vector3<T>(vec.values[0]/scalar, vec.values[1]/scalar, vec.values[2]/scalar); }

template <class T>
const T dot(vector3<T> v1, vector3<T> v2) { return v1.values[0]*v2.values[0] + v1.values[1]*v2.values[1] + v1.values[2]*v2.values[2]; }

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
using vec2 = vector2<base_type>;
using vec3 = vector3<base_type>;

// ray representation (origin+direction)
struct ray{
  vec3 origin;
  vec3 direction;
};

// constants
const base_type EPSILON = 0.0000001;
// std::numeric_limits<base_type>::epsilon();
const base_type DMAX    = 99999999.;


// represents a ray hit and the associated information
struct hitrecord {                // hit record
    vec3 position;               // position
    vec3 normal;                // normal
    base_type dtransit = DMAX; // how far the ray traveled
    int material_index = 0;         // material (indexed)
    vec2 uv;                 // used for triangles, barycentric coords
    bool front;
};


// Random Vector Utilities

// Wang hash - Thomas Wang
// https://burtleburtle.net/bob/hash/integer.html
static uint wang_hash(){
  static uint seed = 0;
  seed = uint(seed ^ uint(61)) ^ uint(seed >> uint(16));
  seed *= uint(9);
  seed = seed ^ (seed >> 4);
  seed *= uint(0x27d4eb2d);
  seed = seed ^ (seed >> 15);
  return seed;
}
// static base_type rng() { // random value 0-1
//   return base_type(wang_hash()) / 4294967296.0;
// }

static base_type rng(){ // this will be handled differently
  thread_local std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_real_distribution<base_type> distribution(0., 1.);
  return distribution(generator);
}

static vec3 random_unit_vector(){ // random direction vector (unit length)
  base_type z = rng() * 2.0f - 1.0f;
  base_type a = rng() * 2. * PI;
  base_type r = sqrt(1.0f - z * z);
  base_type x = r * cos(a);
  base_type y = r * sin(a);
  return vec3(x, y, z);
}

static vec3 random_in_unit_disk(){ // random in unit disk (xy plane)
  vec3 val = random_unit_vector();
  return vec3(val.values[0], val.values[1], 0.);
}

#endif
