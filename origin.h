//
// Created by shuttle3468 on 8/2/17.
//

#ifndef COMPUTGEOALGOS_ORIGIN_H
#define COMPUTGEOALGOS_ORIGIN_H

#include <iostream>
#include <bits/stdc++.h>

#define ull unsigned long long /*!< Macro for making my typing life easier*/
#define pb push_back /*!< Macro for making my typing life easier*/
#define mp make_pair /*!< Macro for making my typing life easier*/

#define COLLINEAR 1 /*!< Macro defined for identifying 3 collinear points */
#define CLOCKWISE 2 /*!< Macro defined for identifying 3 points that rotate clockwise */
#define ANTICLOCKWISE 3 /*!< Macro defined for identifying 3 points that rotate anticlockwise */
using namespace std;
vector<int> indices;
//! Euclidean Distance
/*! This function is used to calculate the distance between two points which is \f$\sqrt{(x_2-x_1)^2+(y_2-y_1)^2}\f$.
 */
double calcEuclidDistance(pair<double, double> fpoint, pair<double, double> spoint) {
    double dist;
    dist = sqrt(pow((fpoint.first-spoint.first),2.0) + pow((fpoint.second-spoint.second),2.0));
    return dist;
}
//! Orientation
/*! This function is used to calculate orientation of 3 points namely clockwise, anticlockwise and collinear.
 * The idea here is to to get the difference between slopes of 2 lines by assuming a particular direction as a result
 * the result obtained determines the direction of turn of the three points.
 */
int orientation(pair<double, double> a, pair<double, double> b, pair<double, double> c) {
    double m1, m2, dif;
    dif = (b.second - a.second)*(c.first-b.first) - (b.first-a.first)* (c.second - b.second);
    //cout << "Difference in Slopes " << dif<<endl;
    if(dif == 0) {
        return COLLINEAR;
    } else if (dif > 0 ) {
        return CLOCKWISE;
    } else {
        return ANTICLOCKWISE;
    }
}
//! Comparator Function
/*! This function basically compares a pair of elements by the values of their x-coordinate and if x-xoordinate is equal then it
 * checks for equality of y-coordinate
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
//! Comparator Function Sort by y coordinate
/*! This function basically compares a pair of elements by the values of their y-coordinate and if x-xoordinate is equal then it
 * checks for equality of x-coordinate
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

//@{
/**
 * @brief a double value which stores the centre about which polar ordering is to be done
 */
pair<double ,double > P0;
//@}

//! Function to order with respect to polar Coordinates
/*! function used by this algorithm to sort an array of
 * points with respect to the first point in the vector.
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

//! Print Function
/*! Prints content of the vector. Used for **output formatting**
 */
void printVectorData(int len, vector<pair<double, double> > v, string s) {
    int i;
    cout << s << v.size() << endl;
    for(i=0;i<len;i++)
        cout << v[i].first <<" " << v[i].second <<endl;
}
//! Extract Data from Input File
/*! It extracts Data From a file and stores it in a vector for further calculation.
 * Forms the base for getting Data.
 */
vector<pair<double, double> > getData(char *filename) {
    vector<pair<double, double> > input;
    double a,b;
    ifstream in_file;
    in_file.open(filename);
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