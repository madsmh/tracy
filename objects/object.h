    //
// Created by mads on 02/02/2020.
//

#ifndef TRACY_OBJECT_H
#define TRACY_OBJECT_H

#include "../vector3.h"
#include "../ray.h"

class Object {
public:
    virtual ~Object() {}

protected:
    // x, y, z coordinate of the origin
    Vector3 m_origin;

    virtual Vector3 getOrigin() const;


public:
    virtual Vector3 getNormal (Vector3 intersection) const;

    virtual double doesIntersect(Ray ray) const;

    virtual void setOrigin(Vector3 newOrigin);

};


#endif //TRACY_OBJECT_H
