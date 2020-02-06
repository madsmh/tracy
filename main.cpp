//
// Created by mike on 06/02/2020.
//

#include <assert.h>
#include "objects/box.h"

Ray getRandomRayThroughPoint(const Vector3& point)
{
   // A random direction
   const Vector3 direction(3.0, 2.0, 1.0);         // TODO

   // A random distance away from the point
   const double dist = 200.0;                      // TODO

   // A temporaryy ray through the given point
   Ray tempRay(point, direction);

   // A point far away from the given
   Vector3 newPoint = tempRay.getPtAtParameter(dist);

   return Ray(newPoint, direction);
}

Ray getRandomPerpendicularRay(const Ray& ray)
{
   const double epsilon = 0.001;
   const Vector3 direction(1.0, 1.0, 1.0 + epsilon);
   const Vector3 newDirection = cross(ray.getDirection(), direction).normalize();
   return Ray(ray.getOrigin(), newDirection);
}

Ray getPerpendicularRay(const Ray& ray1, const Ray& ray2)
{
   const Vector3 newDirection = cross(ray1.getDirection(), ray2.getDirection()).normalize();
   return Ray(ray1.getOrigin(), newDirection);
}

void verify(const Box& box, const Ray& ray, bool expected)
{
   bool value = box.doesIntersect(ray) != -1.0;

   assert (value == expected);
}

int main()
{
   // A random box somewhere far from the origin
   Vector3 centre(100.0, 150.0, 350.0);               // TODO
   Vector3 lengths(13.0, 15.0, 17.0);                 // TODO
   Box box(lengths, centre);

   // A ray through the centre of the box.
   Ray ray = getRandomRayThroughPoint(centre);

   // A second ray perpendicular to the first
   Ray ray2 = getRandomPerpendicularRay(ray);

   // A third ray perpendicular to the first two
   Ray ray3 = getPerpendicularRay(ray, ray2);

   verify(box, ray, true);

   verify(box, ray+100*ray.getDirection(), true);
   verify(box, ray-100*ray.getDirection(), true);

   verify(box, ray+100*ray2.getDirection(), false);
   verify(box, ray-100*ray2.getDirection(), false);

   verify(box, ray+100*ray3.getDirection(), false);
   verify(box, ray-100*ray3.getDirection(), false);
}

