#include "origin.h"
#include "GrahamScans.h"
#include "Andrews.h"
#include "JarvisMarch.h"

int main(int argc, char *argv[]) {
    vector<pair<double , double> > points;
    if ( argc > 2 ) // argc should be 2 for correct execution
        // We print argv[0] assuming it is the program name
        cout << "usage: " << argv[0] << " <filename>\n";
    else {
        int choice;
        printf("Select one of the three algorithms based on the index number associated with it\n");
        printf("1 for Graham Scans Algorithm\n2 for Andrews Algorithm\n3 for Jarvis Mach Algorithm\n0 for all 3\n");
        cin >> choice;
        if(argc == 2) {
            points = getData(argv[1]);}
        else{
            points = getData("./tests/sampleInput.txt");
        }
        switch(choice) {
            case 0:
            case 1: {
                double ret = execGrahamScans(points);
                //cout << "Time taken : " << ret << endl;
            }
                if(choice){break;}
            case 2: {
                    //clock_t t_taken;
                    //t_taken = clock();
                    set<pair<double, double> > andrews_res = execAndrews(points);
                    ull andrews_len = andrews_res.size();
                    cout << andrews_len << endl;
                    set<pair<double, double> >::iterator iter;
                    for (iter = andrews_res.begin(); iter != andrews_res.end(); ++iter) {
                        cout << (*iter).first << "," << (*iter).second << endl;
                    }
                    cout << endl;
                    //t_taken = clock() - t_taken;
                    //cout << "Time taken : " << ((double) (t_taken))/CLOCKS_PER_SEC << endl;
                }
                if(choice){break;}
            case 3: {
                double time_jarvis = execJarvisMarch(points);
                //cout << "Time taken : " << time_jarvis << endl;
                }
                if(choice){break;}
            default:
                if(choice){printf("No such option exists");}
        }
    }
    return 0;
}
