    //
// Created by mads on 02/02/2020.
//

#ifndef TRACY_OBJECT_H
#define TRACY_OBJECT_H

#include "../vector3.h"
#include "../ray.h"

class Object {
protected:
    // x, y, z coordinate of the origin
    Vector3 m_origin;

    Vector3 getOrigin(){
        return m_origin;
    }


public:
    virtual Vector3 getNormal (Vector3 intersection);

    virtual double doesIntersect(Ray ray);

    void setOrigin(Vector3 newOrigin){
        m_origin = newOrigin;
    }

};


#endif //TRACY_OBJECT_H
