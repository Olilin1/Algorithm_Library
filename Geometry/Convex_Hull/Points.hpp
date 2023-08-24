/*
Author: Oliver Lindgren
*/

#ifndef POINTS_HPP
#define POINTS_HPP
#include<cmath>
#include<iostream>
#include<vector>

template<typename T>
struct Point{
    T x, y;

    double length(){
        return sqrt(x*x + y*y);
    }

    double magnitude(){
        return length();
    }

    T lengthSquared(){
        return x*x + y*y;
    }

    T magnitudeSquared(){
        return lengthSquared();
    }

    bool operator==(Point<T> const & other){
        return x == other.x && y == other.y;
    }

    bool operator!=(Point<T> const & other){
        return x != other.x || y != other.y;
    }

    Point<T> operator+(Point<T> const & other){
        return {x + other.x, y + other.y};
    }

    Point<T> operator-(Point<T> const & other){
        return {x - other.x, y - other.y};
    }
};

template<typename T>
std::ostream& operator<< (std::ostream& out, Point<T>& point){
    out << point.x << ' ' << point.y;
    return out;
}

template<typename T>
std::istream& operator>> (std::istream& in, Point<T>& point){
    in >> point.x >> point.y;
    return in;
}

template<typename T>
Point<T> add(Point<T> const & a, Point<T> const & b){
    return {a.x + b.x, a.y + b.y};
}

template<typename T>
Point<T> subtract(Point<T> const & a, Point<T> const & b){
    return {a.x - b.x, a.y - b.y};
}

template<typename T>
Point<T> scalar_multiplication(Point<T> const & point, T scalar){
    return {point.x * scalar, point.y * scalar};
}

template<typename T>
T dot_product(Point<T> const & a, Point<T> const & b){
    return a.x * b.x + a.y * b.y;
}

template<typename T>
T cross_product(Point<T> const & a, Point<T> const & b){
    return a.x * b.y - b.x * a.y;
}

template<typename T>
double length(Point<T> const & a){
    return sqrt(a.x*a.x + a.y*a.y);
}

template<typename T>
double lengthSquared(Point<T> const & a){
    return a.x*a.x + a.y*a.y;
}

template<typename T>
double dist(Point<T> const & a, Point<T> const & b){
    return length(subtract(a, b));
}

template<typename T>
double distSquared(Point<T> const & a, Point<T> const & b){
    return lengthSquared(subtract(a, b));
}

template<typename T>
double angle(Point<T> const & a, Point<T> const & b){
    return atan2(cross_product(a,b), dot_product(a,b));
}

template<typename T>
bool intersect(Point<T> const & p1, Point<T> const & p2, Point<T> const & q1, Point<T> const & q2){
    return (((((p1.x-q1.x) * (p2.y - q1.y)) - ((p2.x-q1.x) * (p1.y - q1.y)) > 0) == //First determinant
             (((p1.x-q2.x) * (p2.y - q2.y)) - ((p2.x-q2.x) * (p1.y - q2.y)) < 0)) && //Second
            ((((q1.x-p1.x) * (q2.y - p1.y)) - ((q2.x-p1.x) * (q1.y - p1.y)) > 0) == //Third determinant
             (((q1.x-p2.x) * (q2.y - p2.y)) - ((q2.x-p2.x) * (q1.y - p2.y)) < 0))
    );
} 
/* Source that this works
https://stackoverflow.com/a/3842157
http://www.cs.cmu.edu/~quake/robust.html
*/

template<typename T>
bool simple_polygon(std::vector<Point<T>> const & v){
    size_t n = v.size();
    bool ans = true;
    for(int i = 2; i < n; i++){
        for(int j = (i == 6 ? 1 : 0); j < i-1; j++){
            ans &= !intersect(v[i], v[(i+1)%n], v[j], v[(j+1)%n]);
        }
    }
    return ans;
}

#endif