/* Copyright (c) 2020 By the Authors
 *
 * This file is part of Tracy.

 Tracy is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Tracy is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Tracy.  If not, see <http://www.gnu.org/licenses/>.
 *
 * */


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
   //const Vector3 direction = getRandomVector3().normalize();
   const Vector3 direction(0.0, 0.0, 1.0);

   // A random distance away from the point
   const double dist = -log(uniformDistribution(generator));

   // A temporaryy ray through the given point
   Ray tempRay(point, direction);

   // A point far away from the given, in the backwards direction.
   Vector3 newPoint = tempRay(-dist);

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
   // Calculate parameter for rays intersection with plane.
   double t = plane.intersectParam(ray);
   
   Vector3 intersection = ray(t);

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
   std::cerr << "Testing line "   << line << " : ";
   double returned = box.intersectParam(ray);

   bool value = (returned > 0.0 );

   if (value != expected)
   {
      std::cerr << "FAIL" << std::endl;
      std::cerr << "Box      : " << box << std::endl;
      std::cerr << "Ray      : " << ray << std::endl;
      std::cerr << "Returned : " << returned << std::endl;
      std::cerr << std::endl;
   } else {
      std::cerr << "Success!" << std::endl;
   }
}

static void test_box(Vector3 centre, Vector3 lengths)
{
   // Setup variables for the test:
   // box  : A random box somewhere far from the origin.
   // ray  : Some random ray passing through the centre of the box.
   // dir1 & dir2 : Two normalized perpendicular vectors, each perpendicular to the ray.

   //Vector3 centre(10.0, 0.0, 0.0);               // TODO
   //Vector3 lengths(2.0, 2.0, 2.0);                 // TODO
   Box box(lengths, centre);
   //Ray ray(Vector3(0.0,0.0,0.0),Vector3(1.0,0.0,0.0));

   Ray ray = getRandomRayTowardsPoint(centre);
   Vector3 dir1 = getRandomPerpendicularDirection(ray.getDirection());
   Vector3 dir2 = getPerpendicularDirection(ray.getDirection(), dir1);

   std::cerr << std::endl << std::endl;

   verify_box(box, ray, true, __LINE__);

   verify_box(box, ray+100*ray.getDirection(), false, __LINE__);
   verify_box(box, ray-100*ray.getDirection(), true, __LINE__);

   verify_box(box, ray+100*dir1, false, __LINE__);
   verify_box(box, ray-100*dir1, false, __LINE__);

   verify_box(box, ray+100*dir2, false, __LINE__);
   verify_box(box, ray-100*dir2, false, __LINE__);
}

int main()
{
//    test_plane();
    //test_box(Vector3(0, 55, 0), Vector3(4,4,4));
    //test_box(Vector3(10, 0 ,0), Vector3(2, 2, 2));
     //test_box(Vector3(0,0,77.6), Vector3(3,2,2));

//    Vector3 centre(5.0, 5.0, 5.0);
//    Vector3 lengths(1.0, 1.0,1.0);
//    Box box(lengths, centre);
//    Ray ray(Vector3(0.0,0.0,0.0),Vector3(1.0,0.0,0.0));
//    box.intersectParam(ray);
}

