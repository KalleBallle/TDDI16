/*
 * fast < input.txt
 *
 * Compute and plot all line segments involving 4 points in input.txt
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include "point.h"
#include "window.h"

using namespace std;

int main(int argc, const char* argv[]) {
    WindowPtr window = create_window(argc, argv);
    if (!window)
        return 1;

    // The array of points
    vector<Point> points;

    // Read tolerance from cin
    double tolerance{};
    cin >> tolerance;

    // Read points from cin
    int N{};
    cin >> N;

    for (int i{0}; i < N; ++i) {
        double x{}, y{};
        cin >> x >> y;
        points.push_back(Point{x, y});
    }

    // draw points to screen all at once
    window->draw_points(points);

    auto begin = chrono::high_resolution_clock::now();
    
    vector<Point> to_draw{};
    for (auto point : points) {
        
        vector<Point> temp_points{} ; 
        
        std::copy_if(points.begin(), points.end(), std::back_inserter(temp_points),[&point](Point& otherP){return point.x <= otherP.x;});  
        std::sort(temp_points.begin(), temp_points.end(), PolarSorter(point));
        
        size_t start{0};    
        while (start < temp_points.size())    
        {
            to_draw.clear();
            to_draw.push_back(point);
            
            size_t j{start + 1};
            
            to_draw.push_back(temp_points[start]);
            
            while( j < temp_points.size() && point.sameSlope(temp_points[start], temp_points[j], tolerance)){
                to_draw.push_back(temp_points[j]);
                ++j;
            }
            
            if(to_draw.size() > 3){
                window->draw_line(to_draw); 
            }
            start = j;
        }
    }
    
    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;

    // wait for user to terminate program
    window->run();

    return 0;
}
