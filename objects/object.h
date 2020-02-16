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

#ifndef TRACY_OBJECT_H
#define TRACY_OBJECT_H

#include "../vector3.h"
#include "../ray.h"

class Object {
public:
    virtual ~Object();

protected:
    // x, y, z coordinate of the origin
    Vector3 m_origin;
    bool m_invertNormals = false;

    virtual Vector3 getOrigin() const = 0;


public:
    virtual Vector3 getNormal (Vector3 intersection) const = 0;

    // Returns the parameter at which the ray intersects.
    // Only positive parameters are used, returns -1.0 if
    // no intersection.

    virtual double intersectParam(Ray ray) const = 0;

    virtual void setOrigin(Vector3 newOrigin) = 0;

    virtual void setInvertNormals (bool invertNormals)=0;

};


#endif //TRACY_OBJECT_H
