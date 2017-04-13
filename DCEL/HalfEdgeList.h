#include "DCELHalfEdge.h"
#include "DCELVertex.h"
#include "FaceList.h"


using namespace std;
class HalfEdgeList
{
public:
	HalfEdgeList(void);
	~HalfEdgeList(void);

	DCELHalfEdge* head;
	DCELHalfEdge* tail;
	int globalEdgeCount;

	void addToList(DCELHalfEdge* newEdge);
	void removeFromList(DCELHalfEdge* edge);
	DCELHalfEdge* addTwinTo(DCELHalfEdge* edge, DCELHalfEdge* LaggingTwin);
	DCELFace* addEdgeBetween(DCELVertex* v1, DCELVertex* v2, DCELFace* face);
protected:
	bool status;
};

HalfEdgeList::HalfEdgeList(void) : globalEdgeCount(0), head(NULL), tail(NULL), status(false)
{
}

HalfEdgeList::~HalfEdgeList(void)
{
}

void HalfEdgeList::addToList(DCELHalfEdge* newEdge)
{
	newEdge->meta = ++globalEdgeCount;
	// cout<<newEdge->meta<<"->origin = ";
	// newEdge->origin->print();

	if (head)
	{
		tail->next = newEdge;
		// cout<<tail->meta<<"->next = "<<newEdge->meta<<endl;
		tail = newEdge;
	}
	else {
		head = newEdge;
		tail = newEdge;
	}
}

DCELHalfEdge* HalfEdgeList::addTwinTo(DCELHalfEdge* edge, DCELHalfEdge* LaggingTwin) {
	// cout << endl;
	DCELHalfEdge *twinEdge = new DCELHalfEdge();
	twinEdge->meta = ++globalEdgeCount;
	twinEdge->twin = edge;
	// cout << edge->meta << "->twin = " << twinEdge->meta << endl;
	if (LaggingTwin) {
		LaggingTwin->origin = twinEdge->twin->origin;
		// cout<<LaggingTwin->meta<<"->origin = ";
		// LaggingTwin->origin->print();

		twinEdge->next = LaggingTwin;
		// cout << twinEdge->meta << "->next = " << LaggingTwin->meta << endl;
	}
	edge->twin = twinEdge;
	return twinEdge;
}

void HalfEdgeList::removeFromList(DCELHalfEdge* edge)
{
	edge->getPrev()->next = edge->twin->next;
	edge->twin->getPrev()->next = edge->next;
	delete edge->twin;
	delete edge;
}

DCELFace* HalfEdgeList::addEdgeBetween(DCELVertex* v1, DCELVertex* v2, DCELFace* face)
{
	DCELHalfEdge* walker = face->edge;
	
	// cout<<"spotting vertex:";
	// v1->print();
	while (1) {
		// cout<<"Origin of "<<walker->next->meta<<" is ";
		// walker->next->origin->print();
		if (walker->next->origin == v1) {
			// cout<<"v1 found at" << walker->meta << endl;
			break;
		}
		walker = walker->next;
	}
	DCELHalfEdge* halfEdge = new DCELHalfEdge();
	halfEdge->origin = v2;
	halfEdge->meta = ++globalEdgeCount;
	// cout << halfEdge->meta << "->origin = ";
	// halfEdge->origin->print();
	halfEdge->next = walker->next;
	// cout << halfEdge->meta << "->next = " << walker->next->meta << endl;

	DCELHalfEdge* twinWalker = face->edge;
	// cout<<"spotting vertex:";
	// v2->print();
	while (1) {
		if (twinWalker->next->origin == v2) {
			// cout<<"v2 found at" << twinWalker->meta << endl;
			break;
		}
		twinWalker = twinWalker->next;

	}

	DCELHalfEdge* twinEdge = new DCELHalfEdge();
	twinEdge->origin = v1;
	twinEdge->meta = ++globalEdgeCount;
	// cout << twinEdge->meta << "->origin = ";
	// twinEdge->origin->print();
	twinEdge->next = twinWalker->next;
	// cout << twinEdge->meta << "->next = " << twinWalker->next->meta << endl;
	walker->next = twinEdge;
	// cout << walker->meta << "->next = " << twinEdge->meta << endl;
	twinWalker->next = halfEdge;
	// cout << twinWalker->meta << "->next = " << halfEdge->meta << endl;
	
	halfEdge->twin = twinEdge;
	twinEdge->twin = halfEdge;


	DCELFace* firstHalf = new DCELFace();
	firstHalf->edge = halfEdge;
	walker = halfEdge;
	do {
		walker->face = firstHalf;
		// cout<<"setting face of "<<walker->meta<<endl;
		walker = walker->next;
	} while(walker != halfEdge);
	// cout<<endl;

	DCELFace* secHalf = new DCELFace();
	secHalf->edge = twinEdge;
	twinEdge->face = secHalf;
	walker = twinEdge;
	do {
		walker->face = secHalf;
		// cout<<"setting face of "<<walker->meta<<endl;
		walker = walker->next;
	} while(walker != twinEdge);

	secHalf->next = firstHalf;
	return secHalf;
}

