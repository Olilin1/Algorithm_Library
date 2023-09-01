/*
Author: Oliver Lindgren
*/

#ifndef LINE_INTERSECTION_HPP
#define LINE_INTERSECTION_HPP

#include"Geometry\Points\Points.hpp"
#include <vector>
#include<utility>

template<typename T>
std::vector<std::pair<Point<double>, Point<double>>> line_intersection(Point<T> p1,Point<T> p2, Point<T> q1, Point<T> q2){
    Point<T> deltaP = subtract(p2, p1);
    Point<T> deltaQ = subtract(q2, q1);

    T cross = cross_product(deltaP, deltaQ);
    if(cross == 0){
        Point<T> x = subtract(q1, p1);
        if(cross_product(x, deltaP) == 0) return{p1, p2};
        else return {};
    }
    else{
        double s = (double) cross_product(subtract(q1, p1), deltaP) / (double)cross;
        double t = (double) cross_product(subtract(p1, q1), deltaQ) / (double)cross;
    }
}


#endif