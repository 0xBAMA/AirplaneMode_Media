#include "primitives.h"

// // represents a ray hit and the associated information
// struct hitrecord {          // hit record
//     bool hit = false;      // did it hit anything?
//     vec3 position;        // position
//     vec3 normal;         // normal
//     base_type dtransit; // how far the ray traveled
//     int material = 0;  // material (indexed)
// };

hitrecord sphere::intersect(ray r) const{
  hitrecord h;   h.material = material;   h.dtransit = DMAX;

  // This is based on a quadratic expression, derived from substituting the equation
  //  of the line associated with the ray into the sphere equation.

  // This will have three distinct cases - 0, 1 or 2 hits, which correspond to
  //  different values of the determinant while solving this quadratic.
  vec3 disp = r.origin - center;

  base_type b = dot(r.direction, disp);
  base_type c = dot(disp, disp) - radius*radius;

  base_type des = b * b - c; // b squared minus c - discriminant of the quadratic

  if(des >= 0){ // hit at either one or two poitns
    // solve for distances - we want the closest one, which is still in front of the camera

    // solve for root(s) of the quadratic ( -b +/- sqrt(descriminant) )
    h.dtransit = std::min( -b + sqrt(des), -b - sqrt(des) );

    // figure out hit location from the nearest value of t
    // assign h.position by the hit location
    h.position = r.origin + h.dtransit * r.direction;

    // get h.normal from the displacement from the center point
    h.normal = normalize(h.position - center);
  }
  return h;
}

hitrecord triangle::intersect(ray r) const{
  hitrecord hit;  hit.material = material;  hit.dtransit = DMAX;

  const vec3 edge1 = points[1] - points[0];
  const vec3 edge2 = points[2] - points[0];
  const vec3 pvec = cross(r.direction, edge2);
  const base_type det = dot(edge1, pvec);


  static const base_type Epsilon = std::numeric_limits<base_type>::epsilon();

  if (det > -Epsilon && det < Epsilon)
    return hit;

  const base_type invDet = 1.0f / det;
  const vec3 tvec = r.origin - points[0];
  hit.uv.values[0] = dot(tvec, pvec) * invDet; // u value
  if (hit.uv.values[0] < 0.0f || hit.uv.values[0] > 1.0f)
    return hit;

  const vec3 qvec = cross(tvec, edge1);
  hit.uv.values[1] = dot(r.direction, qvec) * invDet; // v value
  if (hit.uv.values[1] < 0.0f || hit.uv.values[0] + hit.uv.values[1] > 1.0f)
    return hit;

  hit.dtransit = dot(edge2, qvec) * invDet; // dtransit
  hit.position = points[0] + hit.uv.values[0] * edge2 + hit.uv.values[1] * edge1;
  hit.normal = cross(edge1, edge2);

  return hit;
}
