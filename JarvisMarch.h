
//
// Created by shuttle3468 on 7/2/17.
//
#ifndef COMPUTGEOALGOS_JARVISMARCH_H
#define COMPUTGEOALGOS_JARVISMARCH_H

#include <iostream>
#include <bits/stdc++.h>
#include "origin.h"
#define ull unsigned long long
#define pb push_back
#define mp make_pair
using namespace std;

bool orderByAngle(pair<double, double> a, pair<double, double> b, pair<double, double> c ) {
	int oValue  = orientation(a,b,c);
    /*cout << "comparing " << "(" << P0.first << ", " << P0.second <<")" <<  " "
         << "(" << p1.first << ", " << p1.second <<")" << " "
         << "(" << p2.first << ", " << p2.second <<")" <<endl;
    cout << " The orientation value is " << oValue << endl;*/
    if(oValue == 1) {
        //cout << "Result :" << (calcEuclidDistance(P0,p2) >= calcEuclidDistance(P0,p1)) <<endl;
        return (calcEuclidDistance(a,c) < calcEuclidDistance(a,b));
    }
    return (oValue != 3);
}
void swap(double &p, double &q) {
	p = p + q;
	q = p - q;
	p = p - q;
}
void swapElements(pair<double,double> &p, pair<double, double> &q) {
	swap(p.first,q.first);
	swap(p.second,q.second);
}

int execJarvisMarch(vector<pair<double, double> > Points) {
	int len, i, current, min = 0, hullLength=0;
	len = int(Points.size());
	/*
	 * Get the point with lowest x-coordinate
	 */
	double x_min = Points[0].first;
	pair<double, double> lastPointOnHull;
	for (int i = 1; i < len; i++)
	{
		if (orderedSort(Points[i], Points[min]))
			x_min = Points[i].first, min = i;
	}

	lastPointOnHull = Points[min];

	swapElements(Points[hullLength++],Points[min]);
	/*
	 * Form the Hull by processing the remaining points
	 */
	vector<pair<double , double> > convex_hull;
	cout<<"Jarvis March:"<<endl;
	do {
		cout<<lastPointOnHull.first<<","<<lastPointOnHull.second<<endl;
		convex_hull.push_back(lastPointOnHull);
		for (i = hullLength, current = i; i < len; i++) {
			if (orderByAngle(lastPointOnHull,Points[i],Points[current])) {
				current = i;
			}
		}
		if (orderByAngle(lastPointOnHull,Points[0],Points[current])) {
			current = 0;
		}
		lastPointOnHull = Points[current];
		swapElements(Points[hullLength++],Points[current]);
	} while (lastPointOnHull != Points[min]);
	return 0;
}
#endif