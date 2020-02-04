/* Copyright (c) 2019 By the Authors
 *
 * This file is part of MMRender.

 MMRenderer is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 MMRenderer is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with MMRender.  If not, see <http://www.gnu.org/licenses/>.
 *
 * */

#pragma once

#include <vector>
#include <iostream>
#include <cmath>

class Vector3 {
    static double m_coords[3];

    public:
    inline explicit Vector3(double x = 0.0, double y = 0.0, double z = 0.0) {
        m_coords[0] = x; m_coords[1] = y; m_coords[2] = z;
    }
    inline explicit Vector3(const std::vector<double>& v) {
        m_coords[0] = v[0];
        m_coords[1] = v[1];
        m_coords[2] = v[2];
    }

    inline double x() const { return m_coords[0]; }
    inline double y() const { return m_coords[1]; }
    inline double z() const { return m_coords[2]; }

    inline double norm2() const { return m_coords[0]*m_coords[0] + m_coords[1]*m_coords[1] + m_coords[2]*m_coords[2]; }
    inline double norm()  const { return std::sqrt(norm2()); }
/*
    inline Vector3 cross(const Vector3& v) const {
        double x = m_coords[1]*v[2] - m_coords[2]*v[1];
        double y = m_coords[2]*v[0] - m_coords[0]*v[2];
        double z = m_coords[0]*v[1] - m_coords[1]*v[0];
        return Vector3(x, y, z);
    }

    inline double dot(const Vector3& v) const {
        return m_coords[0]*v[0]+m_coords[1]*v[1]+m_coords[2]*v[2];
    }
*/
    inline explicit operator std::vector<double>() const  {
        return std::vector<double> {m_coords[0], m_coords[1], m_coords[2]};
    }

    inline double operator[](int i) const { return m_coords[i];}
    inline double& operator[](int i) { return m_coords[i];}

    inline Vector3 normalize() {
        double k = 1.0/norm();
        m_coords[0] *= k;
        m_coords[1] *= k;
        m_coords[2] *= k;
        return *this;
    }

    inline Vector3& operator += (const Vector3& rhs) {
        m_coords[0] += rhs[0];
        m_coords[1] += rhs[1];
        m_coords[2] += rhs[2];
        return *this;
    }

    inline Vector3& operator -= (const Vector3& rhs) {
        m_coords[0] -= rhs[0];
        m_coords[1] -= rhs[1];
        m_coords[2] -= rhs[2];
        return *this;
    }

    inline Vector3& operator *= (const double rhs) {
        m_coords[0] *= rhs;
        m_coords[1] *= rhs;
        m_coords[2] *= rhs;
        return *this;
    }

    inline Vector3& operator /= (const double rhs) {
        m_coords[0] /= rhs;
        m_coords[1] /= rhs;
        m_coords[2] /= rhs;
        return *this;
    }

    inline friend bool operator == (const Vector3& lhs, const Vector3& rhs) {
        return (lhs[0] == rhs[0]) && (lhs[1] == rhs[1]) && (lhs[2] == rhs[2]);
    }

    inline friend Vector3 operator * (Vector3 lhs, const double rhs ) {
        return lhs *= rhs;
    }

    inline friend Vector3 operator * (const double lhs, Vector3 rhs ) {
        return rhs *= lhs;
    }

    inline friend Vector3 operator * (const Vector3& lhs, const Vector3& rhs) {
        double x = lhs[0]*rhs[0];
        double y = lhs[1]*rhs[1];
        double z = lhs[2]*rhs[2];
        return Vector3(x, y, z);
    }

    inline friend Vector3 operator + (Vector3 lhs, const Vector3& rhs) {
        return lhs += rhs;
    }

    inline friend Vector3 operator - (Vector3 lhs, const Vector3& rhs) {
        return lhs -= rhs;
    }

    inline friend Vector3 operator / (Vector3 lhs, const double rhs){
        return lhs /= rhs;
    }

    inline friend std::ostream& operator << (std::ostream& os, const Vector3& rhs) {
        return os << "(" << rhs[0] << ", " << rhs[1] << ", " << rhs[2] << ")";
    }

    inline friend std::istream& operator >> (std::istream& is, Vector3& rhs) {
        is >> rhs[0] >> rhs[1] >> rhs[2];
        return is;
    }

    /*inline friend Vector3 cross(const Vector3& lhs, const Vector3& rhs) {
        double x = lhs[1]*rhs[2] - lhs[2]*rhs[1];
        double y = lhs[2]*rhs[0] - lhs[0]*rhs[2];
        double z = lhs[0]*rhs[1] - lhs[1]*rhs[0];
        return Vector3(x, y, z);
    }*/

    /*inline friend double dot(const Vector3& lhs, const Vector3& rhs) {
        return lhs[0]*rhs[0]+lhs[1]*rhs[1]+lhs[2]*rhs[2];
    }
*/
    //inline friend Vector3 unit_vector(const Vector3& arg) {
    //   return arg / arg.norm();
    //}


}; // class Vector3


inline double dot(const Vector3& lhs, const Vector3& rhs) {
    return lhs[0]*rhs[0]+lhs[1]*rhs[1]+lhs[2]*rhs[2];
}

inline Vector3 cross(const Vector3& lhs, const Vector3& rhs) {
    double x = lhs[1]*rhs[2] - lhs[2]*rhs[1];
    double y = lhs[2]*rhs[0] - lhs[0]*rhs[2];
    double z = lhs[0]*rhs[1] - lhs[1]*rhs[0];
    return Vector3(x, y, z);
}