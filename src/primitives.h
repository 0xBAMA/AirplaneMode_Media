#include "AMvector.h"
// base type is float, double, as desired
// vec is the vec3 of the defined base type - see AMvector.h

// hit record
  //


// primitives
class sphere{

  // center position + radius
  vec center;
  base_type radius;

};

class triangle{

  // three points in space
  vec points[3];

//from Wikipedia
      // bool RayIntersectsTriangle(Vector3D rayOrigin,
      // Vector3D rayVector,
      // Triangle* inTriangle,
      // Vector3D& outIntersectionPoint)
      // {
      // const float EPSILON = 0.0000001;
      // Vector3D vertex0 = inTriangle->vertex0;
      // Vector3D vertex1 = inTriangle->vertex1;
      // Vector3D vertex2 = inTriangle->vertex2;
      // Vector3D edge1, edge2, h, s, q;
      // float a,f,u,v;
      // edge1 = vertex1 - vertex0;
      // edge2 = vertex2 - vertex0;
      // h = rayVector.crossProduct(edge2);
      // a = edge1.dotProduct(h);
      // if (a > -EPSILON && a < EPSILON)
      // return false;    // This ray is parallel to this triangle.
      // f = 1.0/a;
      // s = rayOrigin - vertex0;
      // u = f * s.dotProduct(h);
      // if (u < 0.0 || u > 1.0)
      // return false;
      // q = s.crossProduct(edge1);
      // v = f * rayVector.dotProduct(q);
      // if (v < 0.0 || u + v > 1.0)
      // return false;
      // // At this stage we can compute t to find out where the intersection point is on the line.
      // float t = f * edge2.dotProduct(q);
      // if (t > EPSILON) // ray intersection
      // {
      // outIntersectionPoint = rayOrigin + rayVector * t;
      // return true;
      // }
      // else // This means that there is a line intersection but not a ray intersection.
      // return false;
      // }

};
