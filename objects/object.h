    //
// Created by mads on 02/02/2020.
//

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

    void setInvertNormals (bool invertNormals){

        m_invertNormals = invertNormals;
    }

};


#endif //TRACY_OBJECT_H
