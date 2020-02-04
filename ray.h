//
// Created by mads on 05/08/2019.
//

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
    Vector3 getPtAtParameter(double t) const {
        return m_origin + t*m_direction;
    }
    void setOrigin(Vector3 new_origin){
        m_origin = new_origin;
    }
};


#endif //TRACY_RAY_H
