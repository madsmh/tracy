/* Copyright (c) 2020 By the Authors
 *
 * This file is part of Tracy.

 Tracy is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Tracy is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Tracy.  If not, see <http://www.gnu.org/licenses/>.
 *
 * */

#ifndef TRACY_BOX_H
#define TRACY_BOX_H

#include <limits>
#include "object.h"
#include "plane.h"

class Box : public Object {
protected:

    // Length of the box's sides (x, y, z)
    Vector3 m_lengths;

    // Array for the 8 vertices
    Vector3 m_corners [8];

    Plane m_planes[6];

    // Below this is regarded as zero
    const double m_epsilon = 0.001;

    Vector3 getOrigin() const override {
        return m_origin;
    }


    void originLength2coordsNorms ( Vector3 sideLengths, Vector3 origin){
        m_lengths = sideLengths;

        Vector3 deltaX(m_lengths[0], 0.0, 0.0);
        Vector3 deltaY(0.0, m_lengths[1], 0.0);
        Vector3 deltaZ(0.0, 0.0, m_lengths[2]);

        // Calculate the vertices of the box and store in array m_corners
        double x0 = origin[0] - m_lengths[0]/2.0;
        double y0 = origin[1] - m_lengths[1]/2.0;
        double z0 = origin[2] + m_lengths[2]/2.0;

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

        m_corners[0] = Vector3(x0, y0, z0);
        m_corners[1] = m_corners[0] + deltaX;
        m_corners[2] = m_corners[0] + deltaX + deltaY;
        m_corners[3] = m_corners[0] + deltaY;
        m_corners[4] = m_corners[1] - deltaZ;
        m_corners[5] = m_corners[0] - deltaZ;
        m_corners[6] = m_corners[3] - deltaZ;
        m_corners[7] = m_corners[2] - deltaZ;

        m_planes[0] = Plane(m_corners[0], m_corners[2], m_corners[1]);  // Front
        m_planes[1] = Plane(m_corners[2], m_corners[7], m_corners[6]);  // Top
        m_planes[2] = Plane(m_corners[1], m_corners[4], m_corners[7]);  // Right

        m_planes[3] = Plane(m_corners[4], m_corners[6], m_corners[5]);  // Back
        m_planes[4] = Plane(m_corners[1], m_corners[0], m_corners[5]);  // Bottom
        m_planes[5] = Plane(m_corners[0], m_corners[3], m_corners[6]);  // Left


        /*
         * Pairs of parallel planes:
         * 0 and 3
         * 1 and 4
         * 2 and 5
         */
    }

    const std::vector<std::string> m_plane_names = {"Front ", "Top   ", "Right ", "Back  ", "Bottom", "Left  "};

    void calcLambda (Ray ray, double& lambda_plus, double& lambda_minus, int plane1, int plane2) const {
        double a = m_planes[plane1].intersectParam(ray);
        double b = m_planes[plane2].intersectParam(ray);

        lambda_plus  = std::min(a, b);
        lambda_minus = std::max(a, b);

        if (a == b) {
            // This occurs if the ray is parallel with the two
            // planes.
            // In this case we must determine, whether the ray
            // is *between* the two planes.
            // This occurs if the ray is "below" both planes.
            double dist1 = m_planes[plane1].getSignedDist(ray.getOrigin());
            double dist2 = m_planes[plane2].getSignedDist(ray.getOrigin());

            // std::cout << "dist1: " << dist1 << std::endl;
            // std::cout << "dist2: " << dist2 << std::endl;


            /*
             * Case 1: dist1 <0 && dist2 <0 meaning that the ray is in between two planes
             *
             * Case 2: (dist1 < 0 && dist2 > ) || (dist 1 > 0 && dist2 < 0) meaning the ray is NOT
             * inbetween the two planes in question
             *
             * Case 3: dist1 > 0 && dist2 > 0 empty
             * ...
             *
             */

            if (dist1 < 0.0 && dist2 < 0.0 ) {
               lambda_plus  = -std::numeric_limits<double>::infinity();
               lambda_minus = std::numeric_limits<double>::infinity();
            } else if ((dist1> 0 && dist2 < 0) || (dist1 < 0 && dist2 > 0)){
               lambda_plus  = std::numeric_limits<double>::infinity();
               lambda_minus = -std::numeric_limits<double>::infinity();
            } else {
                lambda_plus  = -std::numeric_limits<double>::infinity();
                lambda_minus = std::numeric_limits<double>::infinity();
            }
        }
        //std::cout << m_plane_names[plane1] << "   : " << a << ",   ";
        //std::cout << m_plane_names[plane2] << "   : " << b << std::endl;
    }
public:

    explicit Box (Vector3 sideLengths, Vector3 origin = Vector3(0,0,0), bool invertNormals = false){

        m_lengths = sideLengths;
        m_origin = origin;
        m_invertNormals = invertNormals;
        originLength2coordsNorms(m_lengths, m_origin);

        if (m_invertNormals){
            for (int i = 0; i < 6 ; ++i) {
                m_planes[i].setInvertNormals(m_invertNormals);
            }
        }

    }

    inline friend std::ostream& operator << (std::ostream& os, const Box& rhs) {

        for (int i=0; i<6; ++i)
        {
          os << rhs.m_plane_names[i] << " : " << rhs.m_planes[i].getNormal(Vector3()) << std::endl;
        }

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
         * 0 and 3
         * 1 and 4
         * 2 and 5
         *
         * Indices 0, 1, 2 are the + planes in that order
         * and 5, 3, 4 are - planes in that order
         */

        // lambda+ index 0-2, lambda- index 3-5
        double  lambda[6];

        calcLambda(ray, lambda[0], lambda[3], 0, 3);  // Front and Back
        calcLambda(ray, lambda[1], lambda[4], 1, 4);  // Top and Bottom
        calcLambda(ray, lambda[2], lambda[5], 2, 5);  // Right and Left

        // Check for valid intersections

        double lambda_max = std::max(lambda[0], std::max(lambda[1], lambda[2]));
        double lambda_min = std::min(lambda[3], std::min(lambda[4], lambda[5]));

        // std::cout << "front lambda: " << lambda[0] << ", " << "back Lambda  : " << lambda[3] << std::endl;
        // std::cout << "top lambda  : " << lambda[1] << ", " << "bottom Lambda: " << lambda[4] << std::endl;
        // std::cout << "right lambda: " << lambda[2] << ", " << "left Lambda  : " << lambda[5] << std::endl;

        for (double j : lambda) {
            if ((lambda_max <= j) && (j <= lambda_min))
            {
                // std::cout << "Intersect: " << j << std::endl;
                return j;
            }
        }

        return std::numeric_limits<double>::infinity();


        // if no valid intersections are found, infinity will be returned.


    }

    Vector3 getNormal(Vector3 intersection) const override {

        /*
         * If intersection lies in one of the planes of this Box
         * the normal vector of that plane will be returned.
         *
         * If it does not, a zero-vector will be returned.
         *
         */

        for (const auto &m_plane : m_planes) {
            double abs_dotProduct = std::abs(dot(m_plane.getOrigin() - intersection, m_plane.getNormal(intersection)));

            if (abs_dotProduct < m_epsilon) {

                return m_plane.getNormal(intersection);
            }
        }

        return Vector3();

    }

    void setInvertNormals(bool invertNormals) override {
        m_invertNormals = invertNormals;

        for (int i = 0; i < 6 ; ++i) {
            m_planes[i].setInvertNormals(m_invertNormals);
        }
    }
};


#endif //TRACY_BOX_H
