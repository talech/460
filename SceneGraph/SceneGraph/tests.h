#ifndef TESTS_H
#define TESTS_H


void RunTests();

// Tries to find the intersection of a ray and a sphere.
// P0 is the position from which the ray emanates; V0 is the (normalized)
// direction of the ray.
// matrix is the transformation matrix of the sphere. It is expressed in
// column-major format: The first four elements are the first column of the 
// matrix, from bottom to top, and so on. This is the order in which OpenGL
// expects matrices to be formatted.
// This function should return the smallest positive t-value of the intersection
// (a point such that P0+t*V0 intersects the sphere), or -1 if there is no
// intersection.
double Test_RaySphereIntersect(
	const double P0[3], const double V0[3], 
	const double matrix[16],vec3& normOut, vec3& inPoint);

// Tries to find the intersection of a ray and a triangle.
// This is just like the above function, but it intersects the ray with a
// triangle instead. The parameters p1, p2, and p3 specify the three
// points of the triangle, in object space.
double Test_RayPolyIntersect(
	const double P0[3], const double V0[3], 
	const double p1[3], const double p2[3], const double p3[3], 
	const double matrix[16], vec3& normOut,vec3& inPoint);

// This is just like Test_RaySphereIntersect, but with a unit cube instead of a 
// sphere. A unit cube extends from -0.5 to 0.5 in all axes.
double Test_RayCubeIntersect(
	const double P0[3], const double V0[3], 
	const double matrix[16], vec3& normOut, vec3& inPoint);

double Test_RayPlaneIntersect(
	const double P0[3], const double V0[3], 
	const double p1[3], const double p2[3], const double p3[3],const double p4[3], 
	const double matrix[16],vec3& normOut, vec3& inPoint);

#endif