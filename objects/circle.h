/* Copyright (c) 2020 By the Authors
 *
 * This file is part of Tracy.

 MMRenderer is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 MMRenderer is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with MMRender.  If not, see <http://www.gnu.org/licenses/>.
 *
 * */


#ifndef TRACY_CIRCLE_H
#define TRACY_CIRCLE_H


#include "object.h"
#include "plane.h"

class Circle : public Object {

protected:

    Plane m_circle_plane;
    double m_radius;

    Vector3 getOrigin() const override {
        return m_origin;
    }

public:
    Circle(Vector3 center, Vector3 normal, double radius){
        m_radius = radius;
        m_origin = center;
        m_circle_plane = Plane(center, normal);
    }

    double intersectParam(Ray ray) const override {
        double planeIntersectParam = m_circle_plane.intersectParam(ray);
        if (planeIntersectParam != std::numeric_limits<double>::infinity()){
            if ((ray(planeIntersectParam)-m_origin).norm() < m_radius){
                return planeIntersectParam;
            } else {
                return std::numeric_limits<double>::infinity();
            }
        } else {
            return std::numeric_limits<double>::infinity();
        }
    }

};


#endif //TRACY_CIRCLE_H
