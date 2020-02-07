//
// Created by mike on 06/02/2020.
//

#include <random>
#include "objects/box.h"

static std::default_random_engine             generator;
static std::normal_distribution<double>       normalDistribution(0.0, 1.0);
static std::uniform_real_distribution<double> uniformDistribution(0.0, 1.0);

static Vector3 getRandomVector3()
{
   return Vector3(normalDistribution(generator),
                  normalDistribution(generator),
                  normalDistribution(generator));
}

static Ray getRandomRayTowardsPoint(const Vector3& point)
{
   // A random direction
   const Vector3 direction = getRandomVector3().normalize();

   // A random distance away from the point
   const double dist = -log(uniformDistribution(generator));

   // A temporaryy ray through the given point
   Ray tempRay(point, direction);

   // A point far away from the given, in the backwards direction.
   Vector3 newPoint = tempRay.getPtAtParameter(-dist);

   // Return ray pointing towards the given point.
   return Ray(newPoint, direction);
}

static Vector3 getRandomPerpendicularDirection(const Vector3& direction)
{
   const double epsilon = 0.001;
   const Vector3 someOtherDirection = getRandomVector3();
   return cross(someOtherDirection, direction).normalize();
}

static Vector3 getPerpendicularDirection(const Vector3& vector1, const Vector3& vector2)
{
   return cross(vector1, vector2).normalize();
}

static void verify_plane(const Plane& plane, const Ray& ray, const Vector3& exp_intersection, int line)
{
   // Calculate paramter for rays intersection with plane.
   double t = plane.intersectParam(ray);
   
   Vector3 intersection = ray.getPtAtParameter(t);

   double dist = (intersection-exp_intersection).norm();

   std::cerr << "Testing line " << line << " : ";

   if (dist > 0.001)
   {
      std::cerr << "FAIL" << std::endl;

      std::cout << "Plane        : " << plane << std::endl;
      std::cout << "Ray          : " << ray << std::endl;
      std::cout << "t            : " << t << std::endl;
      std::cout << "intersection : " << intersection << std::endl;
      std::cout << "expected     : " << exp_intersection << std::endl;

      std::cerr << std::endl;
   } else {
      std::cerr << "Success!" << std::endl;
   }
}

static void test_plane()
{
   for (int i=0; i<100; ++i)
   {
      // Setup parameters for test:
      Vector3 point1 = getRandomVector3();
      Vector3 point2 = getRandomVector3();
      Vector3 point3 = getRandomVector3();

      // Calculate plane through these three given points.
      Plane plane(point1, point2, point3);

      const double alpha = -log(uniformDistribution(generator));
      const double beta  = -log(uniformDistribution(generator));

      // Calculate some random point in the plane.
      Vector3 point = point1 + alpha*(point2-point1) + beta*(point3-point1);

      // Calculate a ray intersecting the plane at a given point.
      Ray ray = getRandomRayTowardsPoint(point);

      verify_plane(plane, ray, point, i);
   }
}

static void verify_box(const Box& box, const Ray& ray, bool expected, int line)
{
   double returned = box.intersectParam(ray);
   bool value = (returned > 0.0 );

   std::cerr << "Testing line : " << line;

   if (value != expected)
   {
      std::cerr << "FAIL" << std::endl;
      std::cerr << "Box          : " << box << std::endl;
      std::cerr << "Ray          : " << ray << std::endl;
      std::cerr << "Returned     : " << returned << std::endl;
      std::cerr << std::endl;
   } else {
      std::cerr << "Success!" << std::endl;
   }
}

static void test_box()
{
   // Setup variables for the test:
   // box  : A random box somewhere far from the origin.
   // ray  : Some random ray passing through the centre of the box.
   // dir1 & dir2 : Two normalized perpendicular vectors, each perpendicular to the ray.

   Vector3 centre(500.0, 600.0, 900.0);               // TODO
   Vector3 lengths(13.0, 15.0, 17.0);                 // TODO
   Box box(lengths, centre);
   //Ray ray(Vector3(0.0,0.0,0.0),Vector3(1.0,0.0,0.0));

   Ray ray = getRandomRayTowardsPoint(centre);
   Vector3 dir1 = getRandomPerpendicularDirection(ray.getDirection());
   Vector3 dir2 = getPerpendicularDirection(ray.getDirection(), dir1);

   verify_box(box, ray, true, __LINE__);

   verify_box(box, ray+100*ray.getDirection(), true, __LINE__);
   verify_box(box, ray-100*ray.getDirection(), true, __LINE__);

   verify_box(box, ray+100*dir1, false, __LINE__);
   verify_box(box, ray-100*dir1, false, __LINE__);

   verify_box(box, ray+100*dir2, false, __LINE__);
   verify_box(box, ray-100*dir2, false, __LINE__);
}

int main()
{
    test_plane();
//    test_box();

//    Vector3 centre(5.0, 5.0, 5.0);
//    Vector3 lengths(1.0, 1.0,1.0);
//    Box box(lengths, centre);
//    Ray ray(Vector3(0.0,0.0,0.0),Vector3(1.0,0.0,0.0));
//    box.intersectParam(ray);
}

