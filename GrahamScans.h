//
// Created by shuttle3468 on 7/2/17.
//
#ifndef COMPUTGEOALGOS_GRAHAMSCANS_H
#define COMPUTGEOALGOS_GRAHAMSCANS_H

#include <iostream>
#include <bits/stdc++.h>
#include "origin.h"
#define ull unsigned long long
#define pb push_back
#define mp make_pair
using namespace std;
pair<double ,double > P0;
/*
     * Order By Polar
     */
bool orderByPolar(pair<double,double> &p1, pair<double,double> &p2){
    int oValue  = orientation(P0,p2,p1);
    /*cout << "comparing " << "(" << P0.first << ", " << P0.second <<")" <<  " "
         << "(" << p1.first << ", " << p1.second <<")" << " "
         << "(" << p2.first << ", " << p2.second <<")" <<endl;
    cout << " The orientation value is " << oValue << endl;*/
    if(oValue == 1) {
        //cout << "Result :" << (calcEuclidDistance(P0,p2) >= calcEuclidDistance(P0,p1)) <<endl;
        return (calcEuclidDistance(P0,p2) < calcEuclidDistance(P0,p1));
    }
    return (oValue != 3);
}
pair<double ,double > next_to_top(stack<pair<double ,double > > S){
    pair<double ,double > point = S.top();
    S.pop();
    pair<double ,double > res = S.top();
    S.push(point);
    return res;
}
int execGrahamScans(vector<pair<double, double> > Points) {
    int len,i, min = 0;
    len = int(Points.size());
    /*
     * Get the point with lowest y-coordinate
     */
    double y_min = Points[0].second;
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
    P0 = Points[0];  // P0 denotes Central Point for Comparision
    Points.erase(Points.begin());
    sort(Points.begin(), Points.end(), orderByPolar);

    len = int(Points.size());
    //printVectorData(len,Points, "Ordered by Polar Angles");
    /*
     * Form the Hull by processing the remaining points
     */
    stack<pair<double ,double > > convex_hull;
    convex_hull.push(P0);
    convex_hull.push(Points[0]);
    convex_hull.push(Points[1]);

    for(i=2;i<len;i++) {

        while (orientation(next_to_top(convex_hull), convex_hull.top(), Points[i])!=3) {
            if(convex_hull.size()<3) { break;}
            convex_hull.pop();
        }
        convex_hull.push(Points[i]);
    }
    cout << "Using Graham Scans Algorithm\n---\n" <<endl;
    while (!convex_hull.empty())
    {
        pair<double ,double > point = convex_hull.top();
        cout << "(" << point.first << ", " << point.second <<")" << endl;
        convex_hull.pop();
    }
    return 0;
}
#endif