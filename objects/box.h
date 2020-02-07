//
// Created by mads on 05/02/2020.
//

#ifndef TRACY_BOX_H
#define TRACY_BOX_H


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
        double z0 = origin[2] - m_lengths[2]/2.0;

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
        m_corners[4] = m_corners[4] - deltaZ;
        m_corners[5] = m_corners[0] - deltaZ;
        m_corners[6] = m_corners[3] - deltaZ;
        m_corners[7] = m_corners[2] - deltaZ;

        m_planes[0] = Plane(m_corners[0], m_corners[1], m_corners[2]);  // Front
        m_planes[1] = Plane(m_corners[2], m_corners[7], m_corners[6]);  // Top
        m_planes[2] = Plane(m_corners[1], m_corners[4], m_corners[7]);  // Right

        m_planes[3] = Plane(m_corners[4], m_corners[5], m_corners[6]);  // Back
        m_planes[4] = Plane(m_corners[1], m_corners[0], m_corners[5]);  // Bottom
        m_planes[5] = Plane(m_corners[0], m_corners[3], m_corners[6]);  // Left

        for (int i=0; i<6; ++i)
        {
           std::cout << m_plane_names[i] << " : " << m_planes[i] << std::endl;
        }

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

//        std::cout << m_plane_names[plane1] << "   : " << a << ",   ";
//        std::cout << m_plane_names[plane2] << "   : " << b << std::endl;

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

            if (dist1 < 0.0 && dist2 < 0.0) {
               lambda_plus  = -std::numeric_limits<double>::infinity();
               lambda_minus = std::numeric_limits<double>::infinity();
            } else {
               lambda_plus  = std::numeric_limits<double>::infinity();
               lambda_minus = -std::numeric_limits<double>::infinity();
            }
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

        for (double j : lambda) {
            if ((lambda_max <= j) && (j <= lambda_min))
            {
                return j;
            }
        }

        return -1.0;


        // if no valid intersection return negative number


    }

    Vector3 getNormal(Vector3 intersection) const override {
//          // Below this is regarded as zero
//          double epsilon = 0.001;
//  
//          for (int i = 0; i < 6; ++i) {
//              if (m_planes[i].intersectParam(ray) < epsilon) {
//                  return m_planes[i].getNormal(intersection);
//              }
//          }
        return Vector3(0.0, 0.0, 0.0); // TODO
    }
};


#endif //TRACY_BOX_H
