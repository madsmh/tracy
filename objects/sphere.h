//
// Created by mads on 03/02/2020.
//

#ifndef TRACY_SPHERE_H
#define TRACY_SPHERE_H


#include "object.h"

class Sphere : public Object {
protected:
    double m_radius = 1;

    Vector3 getOrigin() const override {
        return m_origin;
    };

public:
    Sphere(double radius, Vector3 origin){
        m_radius = radius;
        m_origin = origin;
    }

    Vector3 getNormal(Vector3 intersection) const override{
        return (intersection-m_origin).normalize();
    }

    double intersectParam(Ray ray) const override {

        // Returns the parameter at which the ray intersects.
        // Only positive parameters are used, returns -1.0 if
        // no intersection.

        double a = dot(ray.getDirection(), ray.getDirection());
        double b = 2.0 * dot(ray.getOrigin(), ray.getDirection()-m_origin);
        double c = dot(ray.getOrigin()-m_origin, ray.getOrigin()-m_origin) - m_radius * m_radius;
        double d = b*b-4.0*a*c;

        if (d < 0){
            return std::numeric_limits<double>::infinity();
        } else {
            return (-b - std::sqrt(d)) / (2.0 * a);
        }
    }

    void setOrigin(Vector3 newOrigin) override {

        m_origin = newOrigin;
    }

};


#endif //TRACY_SPHERE_H
