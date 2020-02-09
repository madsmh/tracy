//
// Created by mads on 08/02/2020.
//

#ifndef TRACY_LAMBERTIAN_H
#define TRACY_LAMBERTIAN_H


#include "material.h"

class Lambertian : public Material {

public:

    double BDRF (Vector3 &incomming, Vector3 &outgoing){
        //TODO
        return m_reflectivity/M_PI;
    }
};


#endif //TRACY_LAMBERTIAN_H
