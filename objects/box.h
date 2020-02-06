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

    // Array for the 8 vertices
    Vector3 m_corners [8];

    // Array for the 6 normal vectors
    Vector3 m_normals [6];

    // Array for point in each plane given by the normal vectors
    Vector3 m_pointsInPlanes [6];

    // Below this is regarded as zero
    const double m_epsilon = 0.001;

    Vector3 getOrigin() const override {
        return m_origin;
    }

    void originLength2coordsNorms ( Vector3 sideLengths, Vector3 origin){

        m_lengths = sideLengths;

        // Calculate the vertices of the box and store in array m_corners
        double x0 = origin[0] - m_lengths[0]/2.0;
        double y0 = origin[1] - m_lengths[1]/2.0;
        double z0 = origin[2] - m_lengths[2]/2.0;

        m_corners[0] = Vector3(x0, y0, z0);

        double x1 = origin[0] + m_lengths[0]/2.0;
        double y1 = y0;
        double z1 = z0;

        m_corners[1] = Vector3(x1, y1, z1);

        double x2 = x1;
        double y2 = origin[1] + m_lengths[1]/2.0;
        double z2 = z0;

        m_corners[2] = Vector3(x2, y2, z2);

        double x3 = x0;
        double y3 = y2;
        double z3 = z0;

        m_corners[3] = Vector3(x3, y3, z3);

        double x4 = x1;
        double y4 = y1;
        double z4 = origin[2] + m_lengths[2]/2.0;

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


        /*
         * Sketch of the points m_corners[k]
         *
         *    6 +--------------+ 7
         *     /|             /|
         *    / |            / |
         * 3 *--------------* 2|
         *   |  |           |  |
         *   |  |           |  |
         *   |  |           |  |
         *   |5 +-----------|--+ 4
         *   | /            | /
         *   |/             |/
         * 0 *--------------* 1
         *
         *
         */


        // Calculate the normals of sides
        m_normals[0] = cross(m_corners[2] - m_corners[1], m_corners[0] - m_corners[1]).normalize();
        m_normals[1] = cross(m_corners[7] - m_corners[2], m_corners[3] - m_corners[2]).normalize();
        m_normals[2] = cross(m_corners[7] - m_corners[4], m_corners[1] - m_corners[4]).normalize();
        m_normals[3] = cross(m_corners[0] - m_corners[1], m_corners[4] - m_corners[1]).normalize();
        m_normals[4] = cross(m_corners[6] - m_corners[3], m_corners[0] - m_corners[3]).normalize();
        m_normals[5] = cross(m_corners[5] - m_corners[4], m_corners[7] - m_corners[4]).normalize();


        /*
         * Pairs of anti-parallel normal vectors:
         * 0 and 5
         * 1 and 3
         * 2 and 4
         */


        // selects points in the place defined by the normal vector in m_normals[k]
        m_pointsInPlanes[0] = m_corners[0];
        m_pointsInPlanes[1] = m_corners[2];
        m_pointsInPlanes[2] = m_corners[1];
        m_pointsInPlanes[3] = m_corners[1];
        m_pointsInPlanes[4] = m_corners[3];
        m_pointsInPlanes[5] = m_corners[7];
    }

    void calcLambda (Ray ray, double (&intersect_candidates)[6], int indexPlus, int indexMinus, int normalPlus, int normalMinus) const {

        double dotProduct1, dotProduct2;
        double inf = std::numeric_limits<double>::infinity();

        dotProduct1 = dot(ray.getDirection(),m_normals[normalPlus]);
        dotProduct2 = dot(ray.getDirection(),m_normals[normalMinus]);

        if (std::abs(dotProduct1) > m_epsilon){
            double a = dot(m_pointsInPlanes[normalPlus]-ray.getOrigin(), m_normals[normalPlus])/(dotProduct1);
            double b = dot(m_pointsInPlanes[normalMinus]-ray.getOrigin(), m_normals[normalMinus])/(dotProduct2);

            //lambda +
            intersect_candidates[indexPlus] = std::min(a, b);
            //lambda -
            intersect_candidates[indexMinus] = std::max(a, b);

        } else {

            //lambda +
            intersect_candidates[indexPlus] = -1.0 * inf;
            // lambda0 -
            intersect_candidates[indexMinus] = inf;
        }
    }
public:

    explicit Box (Vector3 sideLengths, Vector3 origin = Vector3(0,0,0)){

        m_lengths = sideLengths;
        m_origin = origin;
        originLength2coordsNorms(m_lengths, m_origin);

    }

    inline friend std::ostream& operator << (std::ostream& os, const Box& rhs) {
       return os << rhs.m_lengths << " , " << rhs.m_origin;
    }

    void setOrigin(Vector3 newOrigin) override{
        originLength2coordsNorms(m_lengths, newOrigin);
    }

    double intersectParam (Ray ray) const override {

        /* Returns the parameter at which the ray intersects.
         * Only positive parameters are used, returns -1.0 if
         * no intersection.
         *
         *
         * Have used the method described in
         * https://math.stackexchange.com/a/1477956/89850
         *
         *
         * Index of pairs of anti-parallel normal vectors:
         * 0 and 5
         * 1 and 3
         * 2 and 4
         *
         * Indices 0, 1, 2 are the + planes in that order
         * and 5, 3, 4 are - planes in that order
         */

        // lambda+ index 0-2, lambda- index 3-5
        double  lambda[6];

        calcLambda(ray, lambda, 0, 3, 0, 5);
        calcLambda(ray, lambda, 1, 4, 1, 3);
        calcLambda(ray, lambda, 2, 5, 2, 4);

        // Check for valid intersections

        for (double j : lambda) {
            if (std::max(lambda[0], std::max(lambda[1], lambda[2])) <= j <= std::min(lambda[3],std::min(lambda[4],lambda[5])))
            {
                return j;
            }
        }

        // if no valid intersection return negative number
        return -1.0;

    }

    Vector3 getNormal(Vector3 intersection) const override {
        for (int i = 0; i < 6; ++i) {
            if (std::abs(dot(m_pointsInPlanes[i]-intersection, m_normals[i])) < m_epsilon){
                return m_normals[i];
            }
        }
        return Vector3(0.0, 0.0, 0.0); // TODO
    }
};


#endif //TRACY_BOX_H
