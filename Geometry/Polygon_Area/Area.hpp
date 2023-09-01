/*
Author: Oliver Lindgren
*/

#ifndef POLYGON_AREA_HPP
#define POLYGON_AREA_HPP
#include"Geometry\Points\Points.hpp"
#include<vector>
#include<stddef.h>

/*
Computes the area of a simple polygon.
Takes as input a vector of points, the points of the polygon.
Returns the area of that polygon
Area is positive if points are given in counter-clockwise order.
Area is negative if points are given in clockwise order.

Time complexity: O(N)
*/
template<typename T>
double Polygon_area(std::vector<Point<T>> points){
    T area = 0;
    size_t n = points.size();
    for(size_t i = 0; i < n; i++){
        area += cross_product(points[i], points[(i+1)%n]);
    }
    return double(area) / 2.0;
}

#endif