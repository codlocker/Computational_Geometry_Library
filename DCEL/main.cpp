#include "triangulate.h"
using namespace std;

int main() {
	getPolygon("tests/input2.txt");
	split_into_monotone();
	triangulate();
	printPolygon();
}