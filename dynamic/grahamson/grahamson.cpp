#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
};

Point p0; // Global variable to store the point with the lowest y-coordinate

// Function to compare points for sorting based on polar angle
bool comparePoints(Point p1, Point p2) {
    int orientation = (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
    if (orientation == 0) {
        // If two points have the same angle, choose the one closer to p0
        return (p1.x - p0.x) * (p1.x - p0.x) + (p1.y - p0.y) * (p1.y - p0.y) >= (p2.x - p0.x) * (p2.x - p0.x) + (p2.y - p0.y) * (p2.y - p0.y);
    }
    return orientation > 0;
}

// Function to calculate the square of the Euclidean distance between two points
int distSquare(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

// Function to find the orientation of three points (p, q, r)
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;     // Collinear
    return (val > 0) ? 1 : 2;  // Clockwise or counterclockwise
}

// Graham Scan algorithm
vector<Point> grahamScan(vector<Point> points) {
    int n = points.size();
    if (n < 3) {
        // Convex hull not possible with less than 3 points
        return vector<Point>();
    }

    // Find the point with the lowest y-coordinate (and leftmost if tied)
    int minY = points[0].y, minIndex = 0;
    for (int i = 1; i < n; i++) {
        int y = points[i].y;
        if ((y < minY) || (y == minY && points[i].x < points[minIndex].x)) {
            minY = y;
            minIndex = i;
        }
    }

    // Swap the lowest point with the first point
    swap(points[0], points[minIndex]);
    p0 = points[0];

    // Sort the remaining points by polar angle with respect to p0
    sort(points.begin() + 1, points.end(), comparePoints);

    // Initialize the convex hull
    stack<Point> convexHull;
    convexHull.push(points[0]);
    convexHull.push(points[1]);

    for (int i = 2; i < n; i++) {
        while (convexHull.size() > 1 && orientation(convexHull.top(), points[i], convexHull.top()) != 2) {
            convexHull.pop();
        }
        convexHull.push(points[i]);
    }

    // Create a vector to store the convex hull points
    vector<Point> result;
    while (!convexHull.empty()) {
        result.push_back(convexHull.top());
        convexHull.pop();
    }

    reverse(result.begin(), result.end()); // Reversing the order to get counterclockwise order

    return result;
}

int main() {
    vector<Point> points = { {0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3} };

    vector<Point> convexHull = grahamScan(points);

    for (Point p : convexHull) {
        cout << "(" << p.x << ", " << p.y << ")" << endl;
    }

    return 0;
}

