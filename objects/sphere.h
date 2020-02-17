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
