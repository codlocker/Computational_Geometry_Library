#include <iostream>
#include <bits/stdc++.h>
#include <typeinfo>
#include "HalfEdgeList.h"
#include "VertexList.h"
#include "FaceList.h"

using namespace std;

VertexList Vertices; //Head of linked-list containing Vertex Collation
HalfEdgeList Edges; //Head of linked-list containing Edge Collation
FaceList Faces; //Head of linked-list containing Face Collation


//! Extract Data from Input File
/*! getPolygon is the main extractor function that builds the collations.
 *	Vertices are expected to be received in an anticlockwise order.
 */
void getPolygon() {
	double a, b;
	DCELVertex *walker = new DCELVertex();
	DCELHalfEdge *LaggingTwin = NULL;
	DCELFace *inner = new DCELFace();
	DCELFace *outer = new DCELFace();
	ifstream in_file;
	in_file.open("tests/input.txt");
	while (in_file.is_open()) {
		int n, i = 0;
		in_file >> n;
		while (in_file >> a >> b) {
			DCELVertex *next = new DCELVertex();
			next->setCoords(a, b);
			// cout<<a<<" "<<b<<endl;
			Vertices.addToList(next);


			DCELHalfEdge *edge = new DCELHalfEdge();
			edge->origin = next;
			edge->face = inner;
			inner->edge = edge;
			Edges.addToList(edge);
			LaggingTwin = Edges.addTwinTo(edge, LaggingTwin);
			LaggingTwin->face = outer;
			outer->edge = LaggingTwin;
		}
		Faces.addToList(inner);
		Faces.addToList(outer);
		in_file.close();
		// cout<<"----------"<<endl;
	}
	Edges.tail->next = Edges.head->next;
	// cout << Edges.tail->meta << "->next = " << Edges.head->meta << endl;
	Edges.head->twin->next = Edges.tail->twin;
	// cout << Edges.head->twin->meta << "->next = " << Edges.tail->twin->meta << endl;
}

int main() {
	getPolygon();
	// Vertices.echo();
	return 0;
}