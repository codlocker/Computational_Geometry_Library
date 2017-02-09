//
// Created by shuttle3468 on 8/2/17.
//

#ifndef COMPUTGEOALGOS_ORIGIN_H
#define COMPUTGEOALGOS_ORIGIN_H

#include <iostream>
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define COLLINEAR 1
#define CLOCKWISE 2
#define ANTICLOCKWISE 3
using namespace std;
/*
 * Function to Calculate Euclidean Distance
 */
double calcEuclidDistance(pair<double, double> fpoint, pair<double, double> spoint) {
    double dist;
    dist = sqrt(pow((fpoint.first-spoint.first),2.0) + pow((fpoint.second-spoint.second),2.0));
    return dist;
}
/*
 * Get Orientation of the 3 points
 */
int orientation(pair<double, double> a, pair<double, double> b, pair<double, double> c) {
    double m1, m2, dif;
    dif = (b.second - a.second)*(c.first-b.first) - (b.first-a.first)* (c.second - b.second);
    //cout << "Difference in Slopes " << dif<<endl;
    if(dif == 0) {
        return COLLINEAR;
    } else if(dif > 0 ) {
        return CLOCKWISE;
    } else{
        return ANTICLOCKWISE;
    }
}
/*
 * Sort by x co-ordinate
 */
bool orderedSort(pair<double,double> &f, pair<double,double> &s) {
    //cout << "Comparing (" << f.first << ", " << f.second <<")" << " (" << s.first << ", " << s.second <<")" << endl;
    if(f.first < s.first) {
        return true;
    }
    if (f.first > s.first) {
        return false;
    }
    return f.second<s.second;
}
/*
 * Sort by y co-ordinate
 */
bool orderedYSort(pair<double,double> &f, pair<double,double> &s) {
    if(f.second < s.second) {
        return true;
    }
    if (f.second > s.second) {
        return false;
    }
    return f.first<s.first;
}
void printVectorData(int len, vector<pair<double, double> > v, string s) {
    int i;
    cout << s <<endl;
    for(i=0;i<len;i++)
        cout << v[i].first <<" " << v[i].second <<endl;
}
vector<pair<double, double> > getData() {
    vector<pair<double, double> > input;
    double a,b;
    ifstream in_file;
    in_file.open("tests/input1.txt");
    cout << "Reading from the file" << endl;
    while (in_file.is_open()) {
        int n;
        in_file >> n;
        while(in_file >> a >> b) {
            input.pb(mp(a,b));
        }
        in_file.close();
    }
    return input;
}
#endif //COMPUTGEOALGOS_ORIGIN_H