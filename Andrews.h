//
// Created by shuttle3468 on 8/2/17.
//
#include "origin.h"

//! **Upper Hull and Lower Hull Algorithm**
/*! 1. In case of upper hull formation we move from last element to the first and vice versa for lower hull.\n
 *
 *  2. Now we remove those points that are either **anti-clockwise or collinear** because being anticlockwise we are
 *  actually using an interior point in such cases.\n
 *
 *  3. After forming the hull remove the **last point** of each list (it's the same as the first point of the other list)
 */
vector<pair<double,double > > convex_hull(vector<pair<double, double> > points)
{
    int n = points.size();
    int counter = 0;
    vector<pair<double, double> > hull;

    for (int i = 0; i < n; ++i) {
        while (counter >= 2 && orientation(hull[counter-2], hull[counter-1], points[i]) != CLOCKWISE)
        {counter--;hull.pop_back();indices.pop_back();}
        hull.pb(points[i]);counter++;
        indices.pb(i);
    }

    // Build upper hull
    for (int i = n-2, t = counter+1; i >= 0; i--) {
        while (counter >= t && orientation(hull[counter-2], hull[counter-1], points[i]) != CLOCKWISE) {
            counter--; hull.pop_back(); indices.pop_back();
        }
        hull.pb(points[i]);counter++;
        indices.pb(i);
    }

    hull.resize(counter-1);
    return hull;
}

//! **Complete Execution of Andrews Monotone Chain**
/*! 1. Sort the array by their **x-coordinate**. If that's equal then compare y-coordinate this is compared in origin.h
 * header file.\n
 *
 *  2. The next part involves getting upper and lower convex hull\n
 *
 *  3. The final set that is formed is just to **remove** any existing duplicate points in the vector
 */

set<pair<double, double> > execAndrews(vector<pair<double, double> > Points) {
    cout << "Executing Andrews Algorithm\n---\n";
    vector<pair<double, double> > tentative_hull;
    vector<pair<double, double> > L_upper,L_lower;
    int len;
    len = int(Points.size());
    /*
     * Sort the Points By x-coordinate
    */
    sort(Points.begin(),Points.end(),orderedSort);

    tentative_hull = convex_hull(Points);
    /*
     * Final Set of Convex Points
     */
    set<pair<double ,double> > f_convex_hull;
    int LU_len = tentative_hull.size();
    //int LL_len = L_lower.size();
    ofstream out_file;
    out_file.open("output.ch");
    out_file << "CH\n";
    out_file << len << " " << LU_len << "\n";
    cout  << "Elements in convex hull:" << LU_len <<endl;
    for(int i=0;i < len;i++) {
        out_file << Points[i].first << " " << Points[i].second << " 0\n";
    }
    for(int i=0;i<LU_len;i++) {
        f_convex_hull.insert(tentative_hull[i]);
    }
    indices.erase(indices.begin());
    indices.pop_back();
    vector<int>::iterator it_set;
    for(it_set = indices.begin(); it_set!=indices.end(); it_set++) {
        out_file << *it_set << " ";
    }
    out_file << *(indices.end());
    out_file.close();
    return f_convex_hull;
}

