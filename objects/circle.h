//
// Created by mads on 11/02/2020.
//

#ifndef TRACY_CIRCLE_H
#define TRACY_CIRCLE_H


#include "object.h"
#include "plane.h"

class Circle : public Object {

protected:

    Plane m_circle_plane;
    double m_radius;

    Vector3 getOrigin() const override {
        return m_origin;
    }

public:
    Circle(Vector3 center, Vector3 normal, double radius){
        m_radius = radius;
        m_origin = center;
        m_circle_plane = Plane(center, normal);
    }

    double intersectParam(Ray ray) const override {
        double planeIntersectParam = m_circle_plane.intersectParam(ray);
        if (planeIntersectParam != std::numeric_limits<double>::infinity()){
            if ((ray.getPtAtParameter(planeIntersectParam)-m_origin).norm() < m_radius){
                return planeIntersectParam;
            } else {
                return std::numeric_limits<double>::infinity();
            }
        } else {
            return std::numeric_limits<double>::infinity();
        }
    }

};


#endif //TRACY_CIRCLE_H
