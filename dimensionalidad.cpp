#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <map>
#include <fstream>

using namespace std;

struct Point {
    vector<double> coordinates;
};

// Funci�n para generar puntos aleatorios en una dimensi�n d
vector<Point> generateRandomPoints(int d, int numPoints) {
    vector<Point> points(numPoints);

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0.0, 1.0);

    for (int i = 0; i < numPoints; i++) {
        Point point;
        for (int j = 0; j < d; j++) {
            point.coordinates.push_back(dis(gen));
        }
        points[i] = point;
    }

    return points;
}

// Funci�n para calcular la distancia euclidiana entre dos puntos
double calculateEuclideanDistance(const Point& point1, const Point& point2) {
    double distance = 0.0;
    for (size_t i = 0; i < point1.coordinates.size(); i++) {
        distance += pow(point1.coordinates[i] - point2.coordinates[i], 2);
    }
    return sqrt(distance);
}

// Funci�n para generar un histograma de distancias
map<int, int> generateDistanceHistogram(const vector<Point>& points) {
    map<int, int> histogram;

    for (size_t i = 0; i < points.size(); i++) {
        for (size_t j = i + 1; j < points.size(); j++) {
            int distance = static_cast<int>(calculateEuclideanDistance(points[i], points[j]));
            histogram[distance]++;
        }
    }

    return histogram;
}

int main() {
    vector<int> dimensions = {10, 50, 100, 500, 1000, 2000, 5000};
    int numPoints = 100;

    for (int dimension : dimensions) {
        vector<Point> points = generateRandomPoints(dimension, numPoints);
        map<int, int> distanceHistogram = generateDistanceHistogram(points);

        ofstream outputFile("distance_histogram_d" + to_string(dimension) + ".txt");
        if (!outputFile.is_open()) {
            cerr << "Error opening the output file for dimension " << dimension << ".\n";
            return 1;
        }

        for (const auto& entry : distanceHistogram) {
            outputFile << "Distance: " << entry.first << ", Frequency: " << entry.second << "\n";
        }

        outputFile.close();

        cout << "Histogram data for dimension " << dimension << " -Saved to distance histogram d" << dimension << ".txt\n";
    }

    return 0;
}