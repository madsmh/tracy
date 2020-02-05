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
    Vector3 corners [8];
    Vector3 normals [6];

public:

    Box (Vector3 sideLengths, Vector3 origin = Vector3(0,0,0)){

        // Calculate the vertices of the box and store in array corners
        m_lengths = sideLengths;

        double x0 = origin[0] - sideLengths[0]/2.0;
        double y0 = origin[1] - sideLengths[1]/2.0;
        double z0 = origin[2] - sideLengths[2]/2.0;

        corners[0] = Vector3(x0, y0, z0);

        double x1 = origin[0] + sideLengths[0]/2.0;
        double y1 = y0;
        double z1 = z0;

        corners[1] = Vector3(x1, y1, z1);

        double x2 = x1;
        double y2 = origin[1] + sideLengths[1]/2.0;
        double z2 = z0;

        corners[2] = Vector3(x2, y2, z2);

        double x3 = x0;
        double y3 = y2;
        double z3 = z0;

        corners[3] = Vector3(x3, y3, z3);

        double x4 = x1;
        double y4 = y1;
        double z4 = origin[2] + sideLengths[2]/2.0;

        corners[4] = Vector3(x4, y4, z4);

        double x5 = x0;
        double y5 = y0;
        double z5 = z4;

        corners[5] = Vector3(x5, y5, z5);

        double x6 = x3;
        double y6 = y3;
        double z6 = z4;

        corners[6] = Vector3(x6, y6, z6);

        double x7 = x2;
        double y7 = y2;
        double z7 = z4;

        corners[7] = Vector3(x7, y7, z7);

        normals[0] = cross(corners[2]-corners[1], corners[0]-corners[1]).normalize();
        normals[1] = cross(corners[7]-corners[2], corners[3]-corners[2]).normalize();
        normals[2] = cross(corners[7]-corners[4], corners[1]-corners[4]).normalize();
        normals[3] = cross(corners[0]-corners[1], corners[4]-corners[1]).normalize();
        normals[4] = cross(corners[6]-corners[3], corners[0]-corners[3]).normalize();
        normals[5] = cross(corners[5]-corners[4], corners[7]-corners[4]).normalize();
    }
};


#endif //TRACY_BOX_H
