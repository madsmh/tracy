//
// Created by mike on 06/02/2020.
//

#include "objects/box.h"

static Ray getRandomRayTowardsPoint(const Vector3& point)
{
   // A random direction
   const Vector3 direction(3.0, 2.0, 1.0);         // TODO

   // A random distance away from the point
   const double dist = 200.0;                      // TODO

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
   const Vector3 someOtherDirection(1.0, 1.0, 1.0 + epsilon);
   return cross(someOtherDirection, direction).normalize();
}

static Vector3 getPerpendicularDirection(const Vector3& vector1, const Vector3& vector2)
{
   return cross(vector1, vector2).normalize();
}

static void verify(const Box& box, const Ray& ray, bool expected, int line)
{
   double returned = box.intersectParam(ray);
   bool value = (returned > 0.0 );

   if (value != expected)
   {
      std::cerr << "FAIL in line : " << line << std::endl;
      std::cerr << "Box          : " << box << std::endl;
      std::cerr << "Ray          : " << ray << std::endl;
      std::cerr << "Returned     : " << returned << std::endl;
      std::cerr << std::endl;
   }
}

static void test_box()
{
   // Setup variables for the test:
   // box  : A random box somewhere far from the origin.
   // ray  : Some random ray passing through the centre of the box.
   // dir1 & dir2 : Two normalized perpendicular vectors, each perpendicular to the ray.

   Vector3 centre(5.0, 5.0, 5.0);               // TODO
   Vector3 lengths(1.0, 1.0,1.0);                 // TODO
   Box box(lengths, centre);
   Ray ray(Vector3(0.0,0.0,0.0),Vector3(1.0,0.0,0.0));
   //Ray ray = getRandomRayTowardsPoint(centre);
   //Vector3 dir1 = getRandomPerpendicularDirection(ray.getDirection());
   //Vector3 dir2 = getPerpendicularDirection(ray.getDirection(), dir1);

   verify(box, ray, true, __LINE__);

   //verify(box, ray+100*ray.getDirection(), true, __LINE__);
   //verify(box, ray-100*ray.getDirection(), true, __LINE__);

   //verify(box, ray+100*dir1, false, __LINE__);
   //verify(box, ray-100*dir1, false, __LINE__);

   //verify(box, ray+100*dir2, false, __LINE__);
   //verify(box, ray-100*dir2, false, __LINE__);
}

int main()
{
   //test_box();

    Vector3 centre(5.0, 5.0, 5.0);
    Vector3 lengths(1.0, 1.0,1.0);
    Box box(lengths, centre);
    Ray ray(Vector3(0.0,0.0,0.0),Vector3(1.0,0.0,0.0));
    box.intersectParam(ray);
}

