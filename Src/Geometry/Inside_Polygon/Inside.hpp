/*
Author: Oliver Lindgren
*/

#ifndef POLYGON_POINT_INSIDE_HPP
#define POLYGON_POINT_INSIDE_HPP
#include"Geometry\Points\Points.hpp"
#include<vector>
#include<stdexcept>
#include<utility>
#include<stddef.h>
#include<iostream>
#include<cmath>

enum Status{Outside, OnEdge, Inside};

//For some reason the normal abs function didn't work
double myAbs(double y){
    if(y < 0) return -y;
    else return y;
}


/*
Function to determine if a point lies on a segment.
Takes as input a pair containing the two endPoints of the segment, as well as a point.
Returns true if the point lies on the segment.

Should probably take some sort of epsilon as a value too
*/
template <typename T>
bool onSegment(std::pair<Point<T>, Point<T>> segment, Point<T> q){
    auto x = dist(segment.first, segment.second);
    auto a = dist(q, segment.first);
    auto b = dist(q, segment.second);
    auto y = x - a - b;
    double t = myAbs(y); //For some reason abs(y) returned 0 even when y == 0.7.... something
    return t < 0.00001;
}

/*
Function to determine if a point is inside, outside, or on the edge of a simple polygon.
Takes as input a vector containing the points of the simple polygon and a point p.
Returns a Status enum.
If the point is inside the polygon Status::Inside is returned.
If the point is outside the polygon Status::Outside is returned.
If the point is on the edge of the polygon Status::OnEdge is returned.
Time complexity: O(N)
*/
template <typename T>
Status inside_poly(std::vector<Point<T>> const & polygon, Point<T> const & p){
    double angleSum = 0;
    size_t n = polygon.size();
    for(size_t i = 0; i < n; i++){
        if(onSegment({polygon[i], polygon[(i+1)%n]}, p)){
            std::cerr << i << ' ' << ((i+1)%n) << '\n';
            return OnEdge;
        } 
        angleSum += angle(subtract(polygon[i], p), subtract(polygon[(i+1)%n], p));
    }


    if(abs(angleSum) < 0.00001) return Outside;
    if(abs(abs(angleSum) - 2.0*(3.141592)) < 00001) return Inside;
    
    throw std::logic_error("Can't determine point position");
}

#endif