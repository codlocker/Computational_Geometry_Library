//
// Created by shuttle3468 on 8/2/17.
//
#include "origin.h"

#define ull unsigned long long
/*
 * Left Monotonic Change for Upper
 */
vector<pair<double, double> > BEmonotonicChain(vector<pair<double, double> > L_upper, vector<pair<double, double> > points) {
    int i,j,len = int(points.size());
    for(i = 2;i<len;i++) {
        int LU_len = int(L_upper.size());

        while (orientation(L_upper[LU_len-2], L_upper[LU_len-1], points[i]) != CLOCKWISE) {
            /*cout << L_upper[LU_len-2].first <<" " << L_upper[LU_len-2].second << " "
                 << L_upper[LU_len-1].first <<" " << L_upper[LU_len-1].second << " "
                 << points[i].first <<" " << points[i].second;
            cout << endl;*/
            L_upper.pop_back();
            if(L_upper.size() < 3) { break;}
        }
        L_upper.push_back(points[i]);
    }
    return L_upper;
}
/*
 * End to Beginning/ Right Monotonic Change
 */
vector<pair<double, double> > EBmonotonicChain(vector<pair<double, double> > L_lower, vector<pair<double, double> > rpoints) {
    int i,j,len = int(rpoints.size());
    for(i = len-3;i>=0;i--) {
        int LU_len = int(L_lower.size());

        while (orientation(L_lower[LU_len-1], L_lower[LU_len-2], rpoints[i]) != CLOCKWISE) {

            /*cout << L_lower[LU_len-2].first <<" " << L_lower[LU_len-2].second << " "
                 << L_lower[LU_len-1].first <<" " << L_lower[LU_len-1].second << " "
                 << rpoints[i].first <<" " << rpoints[i].second;
            cout << endl;*/
            L_lower.pop_back();
            if(L_lower.size() < 3) { break;}
        }
        L_lower.push_back(rpoints[i]);
    }
    return L_lower;
}
set<pair<double, double> > execAndrews(vector<pair<double, double> > Points) {
    cout << "Executing Andrews Algorithm\n---\n";
    vector<pair<double, double> > L_upper,L_lower;
    int len;
    len = int(Points.size());
    /*
     * Sort the Points By x-coordinate
     */
    sort(Points.begin(),Points.end(),orderedSort);
    //printVectorData(len,Points, "After Sorting by x-coordinate");
    /*
     * L Upper
     */
    L_upper.pb(Points[0]);L_upper.pb(Points[1]);
    L_upper = BEmonotonicChain(L_upper,Points);
    //printVectorData(L_upper.size(), L_upper,"Getting LUpper\n");
    /*
     * L Lower
     */
    L_lower.pb(Points[len-1]);L_lower.pb(Points[len-2]);
    L_lower = EBmonotonicChain(L_lower,Points);
    //printVectorData(L_lower.size(), L_lower,"Getting Llower\n");
    /*
     * Final Set of Convex Points
     */
    set<pair<double ,double> > convex_hull;
    int LU_len = L_upper.size();
    int LL_len = L_lower.size();
    for(int i=0;i<L_upper.size();i++) {
        convex_hull.insert(L_upper[i]);
    }
    for(int i=0;i<L_lower.size();i++) {
        convex_hull.insert(L_lower[i]);
    }

    return convex_hull;
}

