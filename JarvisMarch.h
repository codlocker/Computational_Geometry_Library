
//
// Created by calvrix on 13/02/17.
//
#ifndef COMPUTGEOALGOS_JARVISMARCH_H
#define COMPUTGEOALGOS_JARVISMARCH_H

#include <iostream>
#include <bits/stdc++.h>
#include "origin.h"
using namespace std;

vector<int> indices_j;
//! Generic Swap Function
void swap(double &p, double &q) {
	double tray = p;
	p = q;
	q = tray;
}

//! Point Swap Function
/*! Swaps the coordinates of the points passed. Used for **efficiency** by reducing number of checks
 */
void swapElements(pair<double, double> &p, pair<double, double> &q) {
	swap(p.first, q.first);
	swap(p.second, q.second);
}


//! **Jarvis March Algorithm Implementation**
/*! 1. First Step is to sort points with respect to their x coordinates.\n
 *
 *  2. Start from the left-most point.\n
 *
 *  3. Choose and add the point that makes the largest obtuse interior angle with the latest edge on the hull.\n
 *
 *	4. Swap the point with the corresponding nth point in the point set to avoid repeating already chosen points
 */
double execJarvisMarch(vector<pair<double, double> > Points) {
	int len, i, current, min = 0, hullLength = 0;
	len = int(Points.size());
	double x_min = Points[0].first; // a **double** value which gets the point with lowest y-coordinate
	pair<double, double> leftMost;
	//clock_t j_taken;
	//j_taken = clock();
	for (int i = 1; i < len; i++)
	{
		if (orderedSort(Points[i], Points[min]))
			x_min = Points[i].first, min = i;
	}

	P0 = leftMost = Points[min]; //P0 denotes the latest point permanently added to the hull
	indices_j.pb(min);
	swapElements(Points[hullLength++], Points[min]); //Swap the left-most point with the point in the set with index 0
	/*
	 * Form the Hull by processing the remaining points
	 */
	vector<pair<double , double> > convex_hull; // a **vector data structure** for storing the convex hull points
	do {
		convex_hull.pb(P0);
		for (i = hullLength, current = i; i < len; i++) {
			//Find the next point by comparing angles made with the last edge on the hull
			if (orderByPolar(Points[i], Points[current])) {
				current = i;
			}
		}
		//Since the above check starts from an index = hullLength, check if the start of the hull is the next point
		if (orderByPolar(Points[0], Points[current])) {
			current = 0;
		}
		P0 = Points[current];
		swapElements(Points[hullLength++], Points[current]); //Swap the latest added point with the point in the set having index equal to the hull length
	} while (P0 != leftMost);
	ofstream out_file;
	out_file.open("output.ch");
	out_file << "CH\n";
	out_file << len << " " << convex_hull.size() << "\n";
	for (int i = 0; i < len; i++) {
		out_file << Points[i].first << " " << Points[i].second << " 0\n";
	}
	for (i = 0; i < convex_hull.size(); i++) {
		out_file << ((i + 1)%len) << " ";
	}
	printVectorData(hullLength-1,convex_hull,"");
	//j_taken = clock()-j_taken;
	return 0;
}
#endif
