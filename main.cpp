#include "origin.h"
#include "GrahamScans.h"
#include "Andrews.h"
#include "JarvisMarch.h"

int main(int argc, char *argv[]) {
    vector<pair<double , double> > points;
    if ( argc != 2 ) // argc should be 2 for correct execution
        // We print argv[0] assuming it is the program name
        cout << "usage: " << argv[0] << " <filename>\n";
    else {
        points = getData(argv[1]);
        int ret = execGrahamScans(points);
        cout<<endl;
        set<pair<double, double> > andrews_res = execAndrews(points);
        ull i, andrews_len = andrews_res.size();
        cout << endl;
        set<pair<double, double > >::iterator iter;
        for(iter = andrews_res.begin();iter != andrews_res.end();++iter) {
            cout << (*iter).first << "," << (*iter).second << endl;
        }
        cout<<endl;
        int x_min = execJarvisMarch(points);
        cout<<endl;
    }
    return 0;
}
