#pragma once
#include <vector>
#include <utility>   // for std::pair
#include <algorithm> // for std::find
#include <cmath> // for std::fabs

using Point = std::pair<int, int>;

std::vector<Point> brute_force_convex_hull(const std::vector<Point> &points);

std::vector<Point> graham_scan_convex_hull(std::vector<Point> points);
