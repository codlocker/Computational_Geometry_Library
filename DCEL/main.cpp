#include "triangulate.h"
using namespace std;

int main() {
	getPolygon();
	split_into_monotone();
	triangulate();
	printPolygon();
}