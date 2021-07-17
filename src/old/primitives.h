#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "AMvector.h"

class primitive { // parent class for primitives
public:
  virtual hitrecord intersect(ray r) const = 0; // pure virtual, base undefined
};

// -----
class sphere : public primitive {
public:
  sphere(vec3 c, base_type r, int m) : center(c), radius(r), material(m) { }
  hitrecord intersect(ray r) const override;
private:  // geometry parameters
  vec3 center;
  base_type radius;
  int material;
};

// -----
class triangle : public primitive {
public:
  triangle(vec3 p0, vec3 p1, vec3 p2, int m) : points{p0, p1, p2}, material(m) { }
  hitrecord intersect(ray r) const override;
private:  // geometry parameters
  vec3 points[3];
  int material;
};

// TODO:
  // plane
  // aabb or obb

#endif
