#include "DCELHalfEdge.h"
#include "DCELVertex.h"

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
		twinEdge->origin = LaggingTwin->twin->origin;
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

