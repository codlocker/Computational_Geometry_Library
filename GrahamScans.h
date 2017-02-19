//
// Created by shuttle3468 on 7/2/17.
//
#ifndef COMPUTGEOALGOS_GRAHAMSCANS_H
#define COMPUTGEOALGOS_GRAHAMSCANS_H

#include <iostream>
#include <bits/stdc++.h>
#include "origin.h"

using namespace std;

pair<double , double > next_to_top(stack<pair<double , double > > S) {
    pair<double , double > point = S.top();
    S.pop();
    pair<double , double > res = S.top();
    S.push(point);
    return res;
}
//! **Graham Scans Algorithm Implementation**
/*! 1. First Step is to sort points with respect to the polar coordinates.\n
 *
 *  2. After getting the closed path, the next step is to get all points in  the path and remove concave points on this.\n
 *
 *  3. We accept and reject based on orientation of 3 points selected.
 */
double execGrahamScans(vector<pair<double, double> > Points) {
    //clock_t time_taken;
    //time_taken = clock();
    int len, i, min = 0;
    len = int(Points.size());
    double y_min = Points[0].second; // a **double** value which gets the point with lowest y-coordinate
    pair<double, double> temp;
    for (int i = 1; i < len; i++)
    {
        double y = Points[i].second;
        if ((y < y_min) || (y_min == y &&
                            Points[i].first < Points[min].first))
            y_min = Points[i].second, min = i;
    }

    temp = Points[min];
    Points[min] = Points[0];
    Points[0] = temp;

    //printVectorData(len,Points, "Get Values after minimum y-coordinate\n");
    P0 = Points[0];     // P0 denotes Central Point for Comparision
    Points.erase(Points.begin());
    sort(Points.begin(), Points.end(), orderByPolar);

    len = int(Points.size());
    //printVectorData(len,Points, "Ordered by Polar Angles");
    stack<pair<double , double > > convex_hull; // A **stack data structure** which stores the coordinates. Form the Hull by processing the remaining points
    convex_hull.push(P0);
    convex_hull.push(Points[0]);
    convex_hull.push(Points[1]);

    for (i = 2; i < len; i++) {

        while (orientation(next_to_top(convex_hull), convex_hull.top(), Points[i]) != 3) {
            if (convex_hull.size() < 3) { break;}
            convex_hull.pop();
        }
        convex_hull.push(Points[i]);
    }
    cout << "Using Graham Scans Algorithm\n---\n" << endl;
    while (!convex_hull.empty())
    {
        pair<double , double > point = convex_hull.top();
        cout << point.first << ", " << point.second << endl;
        convex_hull.pop();
    }
    //time_taken = clock() - time_taken;
    return 0;
}
#endif