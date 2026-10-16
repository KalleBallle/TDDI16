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
     
    vector<Point> temp_points; 
     std::copy(points.begin(), points.end(),std::back_inserter(temp_points));
    /////////////////////////////////////////////////////////////////////////////
    // Draw any lines that you find in 'points' using the function 'window->draw_line'.
    ///////////////////////////////////////////////////////////////////////////// 
    vector<Point> sniper_lineup{};
    for (auto point : points) {  
        sniper_lineup.push_back(point);
    std::sort(temp_points.begin(),temp_points.end(),PolarSorter(point));
        for (int i{0}; i <temp_points.size() ; ++i) {   

            if(point.sameSlope(temp_points[i],temp_points[i+1],tolerance)) 
            { 
                sniper_lineup.push_back(temp_points[i]); 
               // cout << temp_points[i] << endl;
                //cout << "ORIGIN: "  << points[o] << " 1p:" << temp_points[i] << " 2p:" << temp_points[i+1] << endl  ;       
                //window->draw_line({points[o],temp_points[i],temp_points[i+1]});
            }
           
              else if(sniper_lineup.size() >= 3)
            {  
               // cout << points[o] << endl; 
                window->draw_line(sniper_lineup); 
                sniper_lineup.clear();  
                sniper_lineup.push_back(point);


            }  
            else 
            { 
                sniper_lineup.clear();
                sniper_lineup.push_back(point);
            }  
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
