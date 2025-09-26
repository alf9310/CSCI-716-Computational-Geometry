#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

#include "convex_hull.hpp"

std::vector<Point> read_points_from_file(const std::string& filename);
std::vector<Point> generate_random_points(int num_points, int x_range, int y_range);
void write_points_to_file(const std::vector<Point>& points, const std::string& filename);

