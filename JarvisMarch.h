
//
// Created by calvrix on 13/02/17.
//
#ifndef COMPUTGEOALGOS_JARVISMARCH_H
#define COMPUTGEOALGOS_JARVISMARCH_H

#include <iostream>
#include <bits/stdc++.h>
#include "origin.h"
using namespace std;

//! Generic Swap Function
void swap(double &p, double &q) {
	p = p + q;
	q = p - q;
	p = p - q;
}

//! Point Swap Function
/*! Swaps the coordinates of the points passed. Used for **efficiency** by reducing number of checks
 */
void swapElements(pair<double,double> &p, pair<double, double> &q) {
	swap(p.first,q.first);
	swap(p.second,q.second);
}


//! **Graham Scans Algorithm Implementation**
/*! 1. First Step is to sort points with respect to their x coordinates.\n
 *
 *  2. Start from the left-most point.\n
 *
 *  3. Choose and add the point that makes the largest obtuse interior angle with the latest edge on the hull.\n
 * 
 *	4. Swap the point with the corresponding nth point in the point set to avoid repeating already chosen points
 */
int execJarvisMarch(vector<pair<double, double> > Points) {
	int len, i, current, min = 0, hullLength=0;
	len = int(Points.size());
	/*
	 * Get the point with lowest x-coordinate
	 */
	double x_min = Points[0].first; // a **double** value which gets the point with lowest y-coordinate
	for (int i = 1; i < len; i++)
	{
		if (orderedSort(Points[i], Points[min]))
			x_min = Points[i].first, min = i;
	}

	P0 = Points[min];	//P0 denotes the latest point permanently added to the hull

	swapElements(Points[hullLength++],Points[min]); //Swap the left-most point with the point in the set with index 0
	/*
	 * Form the Hull by processing the remaining points
	 */
	vector<pair<double , double> > convex_hull; // a **vector data structure** for storing the convex hull points
	cout<<"Executing Jarvis March\n---\n"<<endl;
	do {
		cout<<P0.first<<","<<P0.second<<endl;
		convex_hull.pb(P0);
		for (i = hullLength, current = i; i < len; i++) {
			//Find the next point by comparing angles made with the last edge on the hull
			if (orderByPolar(P0,Points[i],Points[current])) {
				current = i;
			}
		}
		//Since the above check starts from an index = hullLength, check if the start of the hull is the next point
		if (orderByPolar(P0,Points[0],Points[current])) {
			current = 0;
		}
		P0 = Points[current];
		swapElements(Points[hullLength++],Points[current]); //Swap the latest added point with the point in the set having index equal to the hull length
	} while (P0 != Points[min]);
	return 0;
}
#endif