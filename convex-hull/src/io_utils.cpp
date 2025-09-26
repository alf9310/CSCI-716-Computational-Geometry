#include "../utils/io_utils.hpp"

/**
 * Reads points from a file. The first line of the file should contain the number of points,
 * followed by lines with x and y coordinates of each point.
 */
std::vector<Point> read_points_from_file(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile) throw std::runtime_error("Cannot open file: " + filename);

    // First line is # of points
    int num_points;
    infile >> num_points;

    std::vector<Point> points;
    double x, y;
    for (int i = 0; i < num_points; ++i) {
        if (infile >> x >> y) {
            points.emplace_back(x, y);
        }
    }
    return points;
}

/**
 * Generates a specified number of random 2D points within given x and y ranges.
 */
std::vector<Point> generate_random_points(int num_points, int x_range, int y_range){
    std::vector<Point> points;
    points.reserve(num_points);
    for (int i = 0; i < num_points; ++i) {
        int x = rand() % x_range;
        int y = rand() % y_range;
        points.emplace_back(x, y);
    }
    return points;
}

/**
 * Writes a set of 2D points to a file. The first line of the file will contain the number of points,
 * followed by lines with x and y coordinates of each point.
 */
void write_points_to_file(const std::vector<Point>& points, const std::string& filename) {
    // Create or overwrite the file
    std::ofstream outfile(filename);

    // First line is # of points
    outfile << points.size() << "\n";
    
    for (auto [x, y] : points) {
        outfile << x << " " << y << "\n";
    }
}
