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


#ifndef TRACY_PLANE_H
#define TRACY_PLANE_H


#include "object.h"

class Plane : public Object {
protected:
    Vector3 m_normal;

public:
    Plane() {
        m_origin = Vector3(0.0, 0.0, 0.0);
        m_normal = Vector3(0.0, 0.0, 0.0);
    }

    Plane(Vector3 point1, Vector3 point2, Vector3 point3, bool invertNormal = false) {
        m_origin = point1;
        m_normal = cross(point2-point1, point3-point1).normalize();
        m_invertNormals = invertNormal;
    }

    Plane(Vector3 point, Vector3 normal, bool invertNormal = false){
        m_origin = point;
        m_normal = normal;
        m_invertNormals = invertNormal;
    }

    inline friend std::ostream& operator << (std::ostream& os, const Plane& rhs) {
       return os << "Point=" << rhs.m_origin << ", Normal=" << rhs.m_normal;
    }

    Vector3 getOrigin() const override {
       return m_origin;
    }

    Vector3 getNormal (Vector3 intersection) const override {
        if (m_invertNormals){
            return -1.0*m_normal;
        } else{
            return m_normal;
        }
    }

    void setOrigin(Vector3 newOrigin) override {
       m_origin = newOrigin;
    }

    // Return the signed perpendicular distance between the plane
    // and the point. The positive side of the plane is determined
    // by the direction of the normal vector.
    double getSignedDist(const Vector3& point) const {
       return dot(point-m_origin, m_normal);
    }

    // Returns a positive parameter for appropriate intersections.
    double intersectParam (Ray ray) const override {
        double dotProduct = dot(ray.getDirection(),m_normal);
        // Below this is regarded as zero
        const double epsilon = 0.001;

        if (std::abs(dotProduct) > epsilon) {
           return dot(m_origin-ray.getOrigin(), m_normal)/dotProduct;
        } else {
           return std::numeric_limits<double>::infinity();
        }
    }

    void setInvertNormals(bool invertNormals) override {
        m_invertNormals = invertNormals;
    }

};


#endif //TRACY_PLANE_H
