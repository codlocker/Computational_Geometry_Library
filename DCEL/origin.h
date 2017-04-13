#ifndef DCEL_ORIGIN_H
#define DCEL_ORIGIN_H

#include <iostream>
#include <bits/stdc++.h>
#include <typeinfo>
#include "HalfEdgeList.h"
#include "VertexList.h"

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

			DCELHalfEdge *edge = new DCELHalfEdge();
			edge->origin = next;
			edge->face = inner;
			inner->edge = edge;
			Edges.addToList(edge);
			LaggingTwin = Edges.addTwinTo(edge, LaggingTwin);
			LaggingTwin->face = outer;
			outer->edge = LaggingTwin;
			outer->bordered = false;
			next->edge = edge;
			Vertices.addToList(next);
		}
		Faces.addToList(outer);
		Faces.addToList(inner);

		in_file.close();
		// cout<<"----------"<<endl;
	}
	Edges.tail->next = Edges.head;
	// cout << Edges.tail->meta << "->next = " << Edges.head->meta << endl;
	Edges.head->twin->next = Edges.tail->twin;
	Edges.tail->twin->origin = Vertices.tail;
	// cout<<Edges.tail->twin->meta<<"->origin = ";
	// Edges.tail->twin->origin->print();
	// cout << Edges.head->twin->meta << "->next = " << Edges.tail->twin->meta << endl;
}
DCELFace* getFaceCommonTo(DCELVertex* v1, DCELVertex* v2) {
	DCELFace* face = NULL;
	DCELHalfEdge* walker = v1->edge;
	DCELHalfEdge* twinWalker = v2->edge;
	do {
		do {
			// cout<<"Comparing faces of "<<walker->meta<<" and "<<twinWalker->meta<<endl;
			if (walker->face == twinWalker->face && walker->face->bordered)
			{face = walker->face; break;}
			twinWalker = twinWalker->twin->next;
		} while (twinWalker != v2->edge);
		walker = walker->twin->next;
	} while (walker != v1->edge && !face);
	// cout<<"face found: "<<face->edge->meta<<endl;
	return face;
}
void insertDiagonal(DCELVertex* v1, DCELVertex* v2) {
	// cout<<"Attempting diagonal Between: ";
	// v1->print();
	// cout<<" and ";
	// v2->print();
	// cout<<endl;
	if(v1 == v2) return;
	DCELHalfEdge* walker = v1->edge;
	do {
		// cout<<walker->meta<<" points to ";
		// walker->next->origin->print();
		// cout<<endl;
		if(walker->next->origin == v2) {
			// cout<<"edge exists"<<endl;
			return;
		}
		// cout<<"Moving to "<< walker->twin->next->meta<<endl;
		walker = walker->twin->next;
	} while(walker != v1->edge);
	// cout<<"Adding edge Between: ";
	// v1->print();
	// cout<<" and ";
	// v2->print();
	// cout<<endl;
	DCELFace* face = getFaceCommonTo(v1, v2);
	DCELFace* newSubdivision = Edges.addEdgeBetween(v1, v2, face);
	delete face;
	Faces.addToList(newSubdivision);
}
#endif