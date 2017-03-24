#include "origin.h"
#include "GrahamScans.h"
#include "Andrews.h"
#include "JarvisMarch.h"

int main(int argc, char *argv[]) {
    vector<pair<double , double> > points;
    if ( argc < 2 ) // argc should be 2 for correct execution
        // We print argv[0] assuming it is the program name
        cout << "usage: " << argv[0] << " <algorithm> <filename>\n";
    else {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            cout << "\nusage: " << argv[0] << " <algorithm> <filename>\n";
            printf("\t-g\t--grahamscan\tEvaluate by Graham Scan\n");
            printf("\t-a\t--andrew\tEvaluate by Andrew's algorithm\n");
            printf("\t-j\t--jarvismarch\tEvaluate by Jarvis March\n\n");
        }
        else {
            if (argv[2])
                points = getData(argv[2]);
            else
                points = getData("./tests/sampleInput.txt");
            if (argv[1][1] == 'g' || strcmp(argv[1], "--grahamscan") == 0) {
                double ret = execGrahamScans(points);
                //cout << "Time taken : " << ret << endl;
            }
            else if (argv[1][1] == 'a' || strcmp(argv[1], "--andrew") == 0) {
                //clock_t t_taken;
                //t_taken = clock();
                set<pair<double, double> > andrews_res = execAndrews(points);
                ull andrews_len = andrews_res.size();
                cout << andrews_len << endl;
                set<pair<double, double> >::iterator iter;
                for (iter = andrews_res.begin(); iter != andrews_res.end(); ++iter) {
                    cout << (*iter).first << " " << (*iter).second << endl;
                }
                //t_taken = clock() - t_taken;
                //cout << "Time taken : " << ((double) (t_taken))/CLOCKS_PER_SEC << endl;
            }
            else if (argv[1][1] == 'j' || strcmp(argv[1], "--jarvismarch") == 0) {
                double time_jarvis = execJarvisMarch(points);
                //cout << "Time taken : " << time_jarvis << endl;
            }
            else {
                printf("Illegal flag");
            }
        }
    }
    return 0;
}
