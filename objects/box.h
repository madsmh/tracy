//
// Created by mads on 05/02/2020.
//

#ifndef TRACY_BOX_H
#define TRACY_BOX_H


#include "object.h"

class Box : public Object {
protected:

    // Length of the box's sides (x, y, z)
    Vector3 m_lengths;
    Vector3 m_corners [8];
    Vector3 m_normals [6];
    Vector3 m_pointsInPlanes [6];

    void originLength2coordsNorms ( Vector3 sideLengths, Vector3 origin){
        // Calculate the vertices of the box and store in array m_corners
        double x0 = origin[0] - sideLengths[0]/2.0;
        double y0 = origin[1] - sideLengths[1]/2.0;
        double z0 = origin[2] - sideLengths[2]/2.0;

        m_corners[0] = Vector3(x0, y0, z0);

        double x1 = origin[0] + sideLengths[0]/2.0;
        double y1 = y0;
        double z1 = z0;

        m_corners[1] = Vector3(x1, y1, z1);

        double x2 = x1;
        double y2 = origin[1] + sideLengths[1]/2.0;
        double z2 = z0;

        m_corners[2] = Vector3(x2, y2, z2);

        double x3 = x0;
        double y3 = y2;
        double z3 = z0;

        m_corners[3] = Vector3(x3, y3, z3);

        double x4 = x1;
        double y4 = y1;
        double z4 = origin[2] + sideLengths[2]/2.0;

        m_corners[4] = Vector3(x4, y4, z4);

        double x5 = x0;
        double y5 = y0;
        double z5 = z4;

        m_corners[5] = Vector3(x5, y5, z5);

        double x6 = x3;
        double y6 = y3;
        double z6 = z4;

        m_corners[6] = Vector3(x6, y6, z6);

        double x7 = x2;
        double y7 = y2;
        double z7 = z4;

        m_corners[7] = Vector3(x7, y7, z7);

        // Calculate the normals of sides
        m_normals[0] = cross(m_corners[2] - m_corners[1], m_corners[0] - m_corners[1]).normalize();
        m_normals[1] = cross(m_corners[7] - m_corners[2], m_corners[3] - m_corners[2]).normalize();
        m_normals[2] = cross(m_corners[7] - m_corners[4], m_corners[1] - m_corners[4]).normalize();
        m_normals[3] = cross(m_corners[0] - m_corners[1], m_corners[4] - m_corners[1]).normalize();
        m_normals[4] = cross(m_corners[6] - m_corners[3], m_corners[0] - m_corners[3]).normalize();
        m_normals[5] = cross(m_corners[5] - m_corners[4], m_corners[7] - m_corners[4]).normalize();

        // selects points in the place defined by the normal vector in m_normals[k]
        m_pointsInPlanes[0] = m_corners[0];
        m_pointsInPlanes[1] = m_corners[2];
        m_pointsInPlanes[2] = m_corners[1];
        m_pointsInPlanes[3] = m_corners[1];
        m_pointsInPlanes[4] = m_corners[3];
        m_pointsInPlanes[5] = m_corners[7];
    }

public:

    explicit Box (Vector3 sideLengths, Vector3 origin = Vector3(0,0,0)){

        m_lengths = sideLengths;
        m_origin = origin;
        originLength2coordsNorms(m_lengths, m_origin);

    }

    void setOrigin(Vector3 newOrigin) override{
        originLength2coordsNorms(m_lengths, newOrigin);
    }

    double doesIntersect (Ray ray) override {

        double dotProducts[6];
        double epsilon = 0.001;
        double t[6];
        double inf = std::numeric_limits<double>::infinity();



        for (int i = 0; i < 6 ; ++i) {

            dotProducts[i] = dot(ray.getDirection(), m_normals[i]);

            if (std::abs(dotProducts[i]) > epsilon){
                t[i] = dot(m_pointsInPlanes[i]-ray.getOrigin(), m_normals[i])/(dotProducts[i]);
            } else if (i<3) {
                t[i] = inf;
            } else if (i>=3){
                t[i] = -inf;
            }
        }

        for (double j : t) {
            if (std::max(t[3], std::max(t[4], t[5]))<= j <= std::min(t[0],std::min(t[1],t[2]))){
                return j;
            }
        }

        return -1.0;

    }
};


#endif //TRACY_BOX_H
