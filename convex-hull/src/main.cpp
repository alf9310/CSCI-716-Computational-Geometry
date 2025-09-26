/*
 * main.cpp
 *
 * Author: Audrey Fuller (alf9310@rit.edu)
 * Date: 9/25/2025
 *
 * Reads in an input file containing a set of 2D points and computes their
 * convex hull using either the brute-force method or Graham's scan algorithm.
 *
 * The program outputs the points in a .txt file that form the convex hull in
 * counter-clockwise order.
 */
#include <iostream>
#include <vector>
#include <string>

// Include utilities for file handling and the hull algorithms
#include "io_utils.cpp"
#include "convex_hull.cpp"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }
    string input_filename = argv[1];

    // Parse input file to extract points
    vector<Point> points = read_points_from_file(input_filename);

    // For testing: generate random points instead of reading from file
    // string input_filename = "C:\\Users\\alynf\\OneDrive\\Documents\\CSCI-716-Computational-Geometry\\CSCI-716-Computational-Geometry\\convex-hull\\input\\example_points.txt";
    // std::vector<Point> points = generate_random_points(8000, 100000, 100000);

    printf("Points read from file:\n");
    for (const auto &p : points)
    {
        printf("(%d, %d)\n", p.first, p.second);
    }
    printf("\n");

    // Run Graham's scan and brute-force algorithms on the points
    vector<Point> brute_force_hull;
    vector<Point> graham_scan_hull;

    // Initialize timers for performance measurement
    clock_t start, end;

    start = clock();
    brute_force_hull = brute_force_convex_hull(points);
    end = clock();
    double brute_force_time = double(end - start) / CLOCKS_PER_SEC;

    start = clock();
    graham_scan_hull = graham_scan_convex_hull(points);
    end = clock();
    double graham_scan_time = double(end - start) / CLOCKS_PER_SEC;

    printf("brute-force runtime: %.6f seconds\n", brute_force_time);
    printf("graham-scan runtime: %.6f seconds\n", graham_scan_time);

    // Output the convex hull points to a .txt file
    // Go up a directory and into the outputs folder
    size_t last_slash = input_filename.find_last_of("\\");
    string graham_scan_filename = input_filename.substr(0, last_slash - 6) + "\\output\\graham_scan_convex_hull.txt";
    string brute_force_filename = input_filename.substr(0, last_slash - 6) + "\\output\\brute_force_convex_hull.txt";

    printf("\nWriting Graham's scan convex hull to %s\n", graham_scan_filename.c_str());
    printf("Writing brute-force convex hull to %s\n", brute_force_filename.c_str());

    write_points_to_file(brute_force_hull, brute_force_filename);
    write_points_to_file(graham_scan_hull, graham_scan_filename);
}
