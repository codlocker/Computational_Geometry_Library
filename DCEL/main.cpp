#include "origin.h"
using namespace std;

int main() {
	getPolygon();
	Edges.addEdgeBetween(Vertices.head, Vertices.head->next->next,Faces.tail);
	Faces.removeFromList(Faces.tail);
	Vertices.echo();
	return 0;
}