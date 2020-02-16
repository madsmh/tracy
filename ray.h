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


#ifndef TRACY_RAY_H
#define TRACY_RAY_H


#include "vector3.h"

class Ray {
private:
    Vector3 m_origin;
    Vector3 m_direction;
public:
    Ray (Vector3 origin, Vector3 direction){
        m_origin = origin;
        m_direction = direction.normalize();
    }

    Vector3 getOrigin() const {
        return m_origin;
    }
    Vector3 getDirection() const {
        return m_direction;
    }
    //Vector3 getPtAtParameter(double t) const {
    //    return m_origin + t*m_direction;
    //}
    void setOrigin(Vector3 new_origin){
        m_origin = new_origin;
    }

    inline friend Ray operator + (const Ray& lhs, const Vector3& rhs ) {
        return Ray(lhs.getOrigin()+rhs, lhs.getDirection());;
    }

    inline friend Ray operator - (const Ray& lhs, const Vector3& rhs ) {
        return Ray(lhs.getOrigin()-rhs, lhs.getDirection());;
    }

    inline friend std::ostream& operator << (std::ostream& os, const Ray& rhs) {
       return os << "Origin=" << rhs.m_origin << ", Direction=" << rhs.m_direction;
    }

    // Regard a ray as a function of a single parameter t.
    inline Vector3 operator() (double t) const {
        return m_origin + t*m_direction;
    }
};


#endif //TRACY_RAY_H
