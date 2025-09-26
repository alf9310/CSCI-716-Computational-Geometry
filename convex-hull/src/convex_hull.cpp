#include "../utils/convex_hull.hpp"

// Compute angle for sorting
double angle(const Point &origin, const Point &p)
{
    return std::atan2(p.second - origin.second, p.first - origin.first);
}

/**
 * @brief Computes the convex hull of a set of 2D points using the brute-force method.
 *
 * @param points A vector of 2D points represented as pairs of integers.
 * @return A vector of points that form the convex hull in counter-clockwise order.
 */
std::vector<Point> brute_force_convex_hull(const std::vector<Point> &points)
{
    std::vector<Point> hull;
    // For all ordered pairs non-equal points (p, q)
    for (size_t i = 0; i < points.size(); ++i)
    {
        for (size_t j = 0; j < points.size(); ++j)
        {
            // Assume (p, q) is part of the hull
            bool valid = true;

            if (j == i)
                continue; // Skip the same point

            // For all other points r
            for (size_t k = 0; k < points.size(); ++k)
            {
                if (k == i || k == j)
                    continue; // Skip points p and q

                // Check if point r is to the left of line (p, q)
                int cross_product = (points[k].first - points[i].first) * (points[j].second - points[i].second) -
                                    (points[k].second - points[i].second) * (points[j].first - points[i].first);

                if (cross_product >= 0)
                {
                    valid = false; // Point r is to the left, so (p, q) cannot be part of the hull
                    break;
                }
            }
            if (valid)
            {
                // Add points p and q to the hull if not already present
                if (std::find(hull.begin(), hull.end(), points[i]) == hull.end())
                {
                    hull.push_back(points[i]);
                }
                if (std::find(hull.begin(), hull.end(), points[j]) == hull.end())
                {
                    hull.push_back(points[j]);
                }
            }
        }
    }

    // Sort hull points in counter-clockwise order

    // 1. find lowest (y, then x)
    Point origin = *std::min_element(hull.begin(), hull.end(),
                                     [](const Point &a, const Point &b)
                                     {
                                         return (a.second < b.second) || (a.second == b.second && a.first < b.first);
                                     });

    // 2. sort by polar angle around origin
    std::sort(hull.begin(), hull.end(),
              [&](const Point &a, const Point &b)
              {
                  double angA = angle(origin, a);
                  double angB = angle(origin, b);
                  if (fabs(angA - angB) < 1e-9)
                  {
                      // tie-break by distance
                      long long da = 1LL * (a.first - origin.first) * (a.first - origin.first) +
                                     1LL * (a.second - origin.second) * (a.second - origin.second);
                      long long db = 1LL * (b.first - origin.first) * (b.first - origin.first) +
                                     1LL * (b.second - origin.second) * (b.second - origin.second);
                      return da < db;
                  }
                  return angA < angB;
              });

    return hull;
}

// Helper function to determine the orientation of the triplet (p, q, r)
// Returns: 0 if collinear, 1 if clockwise, -1 if counterclockwise
int orientation(const Point &p, const Point &q, const Point &r)
{
    int determinant = p.first * (q.second - r.second) +
                      q.first * (r.second - p.second) +
                      r.first * (p.second - q.second);
    if (determinant == 0)
        return 0;                      // collinear
    return (determinant > 0) ? 1 : -1; // clock or counterclock wise
}

/*
 * Helper function to compute one half of the convex hull (either upper or lower)
 * Returns the points in counter-clockwise order
 */
std::vector<Point> single_hull(std::vector<Point> points)
{
    // Store points of the hull in a stack
    std::vector<Point> hull;

    // ----- Generate one hull -----
    for (const auto &p : points)
    {
        while (hull.size() >= 2)
        {
            // Check the orientation of the last two points in the hull and the current point
            const auto &q = hull[hull.size() - 1];
            const auto &r = hull[hull.size() - 2];
            if (orientation(r, q, p) != -1)
            {                    // Not a left turn
                hull.pop_back(); // Remove the last point
            }
            else
            {
                break; // Left turn, keep the point
            }
        }
        hull.push_back(p);
    }

    return hull;
}

std::vector<Point> graham_scan_convex_hull(std::vector<Point> points)
{
    if (points.size() < 3)
        return points;

    // Sort by x, then y
    std::sort(points.begin(), points.end());

    // ----- Build lower hull from left to right -----
    std::vector<Point> lower = single_hull(points);

    // ----- Build upper hull from right to left -----
    std::vector<Point> reversed(points.rbegin(), points.rend());
    std::vector<Point> upper = single_hull(reversed);

    // Concatenate lower + upper (skip last point of each to avoid duplication)
    lower.pop_back();
    upper.pop_back();
    lower.insert(lower.end(), upper.begin(), upper.end());

    // Reverse to get counter-clockwise order starting from the leftmost point
    std::reverse(lower.begin(), lower.end());

    return lower;
}
