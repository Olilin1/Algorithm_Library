/*
    AUTHOR: Oliver Lindgren
*/

#ifndef COVER_HPP
#define COVER_HPP

#include<vector>
#include<utility>
#include<algorithm>

/*
Takes an interval to be covered as a pair of doubles, with the first pair value being the left bound of the interval,
and the second pair value being the right bound of the interval. It also takes a list of intervals that should be used to
try and cover this interval. Returns a vector containing the indices in the intervals vector relating to the intervals that need to be used.
If it is not possible to cover interval then an empty vector is returned.
O(n log(n)) - where n is the size of the intervals vector.

TODO: Template it & convert intervals to be range based.
*/
std::vector<size_t> cover(std::pair<double, double> interval, const std::vector<std::pair<double, double>>& intervals);

#endif