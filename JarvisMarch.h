//
// Created by niranjansooda on 24/3/17.
//

#ifndef COMPUTGEOALGOS_MYJARVIS_H
#define COMPUTGEOALGOS_MYJARVIS_H


#include <iostream>
#include <bits/stdc++.h>
#include "origin.h"
#define ull unsigned long long /*!< Macro for making my typing life easier*/
using namespace std;
//! **Jarvis March Algorithm Implementation**
/*! 1. First Step is to sort points with respect to their x coordinates.\n
 *
 *  2. Start from the left-most point.\n
 *
 *  3. Choose and add the point that makes the largest obtuse interior angle with the latest edge on the hull.\n
 */
double execJarvisMarch(vector<pair<double, double> > input){
    vector<pair<double, double> >output;
    vector<pair<double, double> >::iterator itr,itr2;
    vector<pair<double, double> >::iterator itr1=input.begin();
    vector<int>indices;
    for(itr=input.begin()+1;itr<input.end();itr++){
        if(itr->first<itr1->first){
            itr1=itr;
        }
    }
    itr=itr1;
    /*
	 * Form the Hull by processing the remaining points
	 */
    do{
        int index_position=itr-input.begin();
        indices.push_back(index_position);
        output.push_back(*itr);
        if(itr==input.end())
            itr2=input.begin();
        itr2=(itr+1);
        vector<pair<double, double> >::iterator itr3=input.begin();
        while(itr3<input.end()){
            //Find the next point by comparing angles made with the last edge on the hull
            if(orientation(*itr,*itr3,*itr2)==3){
                itr2=itr3;
            }
            itr3++;
        }
        itr=itr2;
    }while(itr!=itr1);
    ofstream out_file;
    out_file.open("output.ch");
    out_file << "CH\n";
    out_file <<input.size()<< " " << output.size() << "\n";
    for(int i=0;i < input.size() ;i++) {
        out_file << input[i].first << " " << input[i].second << " 0\n";
    }
    for(int i = 0; i <indices.size(); i++) {
        out_file << indices[i] << " ";
    }
    printVectorData(output.size(),output,"");
    return 0;
}

#endif //COMPUTGEOALGOS_MYJARVIS_H
