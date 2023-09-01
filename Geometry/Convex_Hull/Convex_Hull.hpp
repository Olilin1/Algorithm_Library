/*
Author: Oliver Lindgren
*/

#ifndef CONVEX_HULL_HPP
#define CONVEX_HULL_HPP
#include"Geometry\Points\Points.hpp"
#include<vector>
#include<algorithm>

/*
Function that takes a vector of points and returns the convex hull encircling them.
The hull is given as a list of points in counterclockwise order, each point being a node in the hull.
If the points are all colinear then the two endpoints are given.

Time Complexity: O(N log(n))
*/

template<typename T>
std::vector<Point<T>> convex_hull(std::vector<Point<T>> points){
    int leftMostPoint = 0;
    Point<T> org = {0,0};
    std::vector<Point<T>> hull;

    //This is to later remove duplicates
    //This has a potential bug, if two points are colinear and same size but in opposite directions, and there are multiple of each, then they may overlap in a bad way, exempting them from removal.
    std::sort(points.begin(), points.end(), [&org](Point<T> const & a, Point<T> const & b){
        T cross = cross_product(subtract(a, org), subtract(b, org));
        if(cross == 0) return distSquared(org, a) > distSquared(org, b); //De är ko-linjära
        else return cross > 0;
    });

    //remove duplicates
    std::vector<Point<T>> newPoints;
    newPoints.push_back(points[0]);
    for(int i = 1; i < points.size(); i++){
        if(points[i] != *(newPoints.rbegin())) newPoints.push_back(points[i]);
    }


    points.swap(newPoints);

    //Find the leftmost point that is definitely on the hull
    for(int i = 1; i < points.size(); i++){
        if(points[i].x < points[leftMostPoint].x) leftMostPoint = i;
        else if(points[i].x == points[leftMostPoint].x && points[i].y > points[leftMostPoint].y) leftMostPoint = i;
    }

    org = points[leftMostPoint];
    hull.push_back(points[leftMostPoint]);
    points.erase(points.begin() + leftMostPoint);

    //Sort the points based on angle from the previously determined point
    std::sort(points.begin(), points.end(), [&org](Point<T> const & a, Point<T> const & b){
        T cross = cross_product(subtract(a, org), subtract(b, org));
        if(cross == 0) return distSquared(org, a) < distSquared(org, b); //De är ko-linjära
        else return cross > 0;
    });

    //add points to the hull
    for(Point<T> & p : points){

        //if we are doing a rightturn pop last point of hull.
        while(hull.size() >= 2 && cross_product(subtract(hull[hull.size()-1], hull[hull.size()-2]), subtract(p, hull[hull.size()-2])) <= 0) hull.pop_back();
        hull.push_back(p);
    }
    return hull;
}

#endif