#include "origin.h"
#include "GrahamScans.h"
#include "Andrews.h"
int main() {
    vector<pair<double ,double> > points;
    points = getData();
    int ret = execGrahamScans(points);
    set<pair<double, double> > andrews_res = execAndrews(points);
    ull i, andrews_len = andrews_res.size();
    cout << "Output of Convex Hull in Andrews Algorithm is\n";
    set<pair<double, double > >::iterator iter;
    for(iter = andrews_res.begin();iter != andrews_res.end();++iter) {
        cout << (*iter).first << " " << (*iter).second << endl;
    }
}
