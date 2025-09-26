#include "../utils/io_utils.hpp"

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

void write_points_to_file(const std::vector<Point>& points, const std::string& filename) {
    // Create or overwrite the file
    std::ofstream outfile(filename);

    // First line is # of points
    outfile << points.size() << "\n";
    
    for (auto [x, y] : points) {
        outfile << x << " " << y << "\n";
    }
}
