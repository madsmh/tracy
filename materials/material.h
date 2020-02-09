//
// Created by mads on 05/02/2020.
//

#ifndef TRACY_MATERIAL_H
#define TRACY_MATERIAL_H


#include "../vector3.h"

class Material {

protected:
    Vector3 m_diffuse,
    Vector3 emittance(0.0, 0, 0);
    double m_reflectivity = 0.0;
    double m_transparency = 0.0;

public:
    virtual double BDRF(Vector3 &incomming, Vector3 &outgoing) = 0;

    void setDiffuse (Vector3 newDiffuse){
        m_diffuse = newDiffuse;
    }

    void setReflectivity (double newReflectivity){
        m_reflectivity = newReflectivity;
    }


};


#endif //TRACY_MATERIAL_H
