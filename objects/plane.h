//
// Created by mike on 07/02/2020.
//

#ifndef TRACY_PLANE_H
#define TRACY_PLANE_H


#include "object.h"

class Plane : public Object {
protected:
    Vector3 m_pointInPlane;
    Vector3 m_normal;

public:
    Plane() {
        m_pointInPlane = Vector3(0.0, 0.0, 0.0);
        m_normal = Vector3(0.0, 0.0, 0.0);
    }

    Plane(Vector3 point1, Vector3 point2, Vector3 point3) {
        m_pointInPlane = point1;
        m_normal = cross(point2-point1, point3-point1).normalize();
    }

    inline friend std::ostream& operator << (std::ostream& os, const Plane& rhs) {
       return os << rhs.m_pointInPlane << " , " << rhs.m_normal;
    }

    Vector3 getOrigin() const override {
       return m_pointInPlane;
    }

    Vector3 getNormal (Vector3 intersection) const override {
       return m_normal;
    }

    void setOrigin(Vector3 newOrigin) override {
       m_pointInPlane = newOrigin;
    }


    // Returns a positive parameter for appropriate intersections.
    double intersectParam (Ray ray) const override {
        double dotProduct = dot(ray.getDirection(),m_normal);
        // Below this is regarded as zero
        double epsilon = 0.001;

        if (std::abs(dotProduct) > epsilon) {
           return dot(m_pointInPlane-ray.getOrigin(), m_normal)/dotProduct;
        } else {
           return std::numeric_limits<double>::infinity();
        }
    }

};


#endif //TRACY_PLANE_H
