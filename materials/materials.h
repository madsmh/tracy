//
// Created by mads on 05/02/2020.
//

#ifndef TRACY_MATERIALS_H
#define TRACY_MATERIALS_H


#include "../vector3.h"

class Materials {

protected:
    Vector3 m_diffuse, m_reflectance;
    double transparrency = 0.0;

public:
    virtual Vector3 BDRF(Vector3 x, Vector3 &incomming, Vector3 &outgoing);

};


#endif //TRACY_MATERIALS_H
