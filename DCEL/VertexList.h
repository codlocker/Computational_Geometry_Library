#include <iostream> 
using namespace std;
class VertexList
{
public:
	VertexList(void);
	~VertexList(void);

	DCELVertex* head;
	DCELVertex* tail;

	void addToList(DCELVertex* newVertex, DCELVertex* afterThisVertex);
	void addToList(DCELVertex* newVertex);
	int length();
	void removeFromList(DCELVertex* vertex);
	void echo();
};

VertexList::VertexList(void) : head(NULL), tail(NULL)
{
}

VertexList::~VertexList(void)
{
}

void VertexList::echo() {
	DCELVertex* walker = head;
	while(1) {
		cout<<walker->x<<" "<<walker->y<<endl;
		if(walker->next)
			walker = walker->next;
		else break;
	}
}

void VertexList::addToList(DCELVertex* newVertex)
{
	if ( head==NULL ) {
		head = newVertex;
		tail = newVertex;
		// cout<<"Added Vertex: "<<newVertex->x<<" "<<newVertex->y<<endl;
	}
	else {
		addToList(newVertex, tail);
		tail = newVertex;
	}
}

void VertexList::addToList(DCELVertex* newVertex, DCELVertex* afterThisVertex)
{
	if(afterThisVertex->next) 
		newVertex->next = afterThisVertex->next;
	afterThisVertex->next = newVertex;
	// cout<<"Added Vertex: "<<newVertex->x<<" "<<newVertex->y<<endl;
}

int VertexList::length() {
	if(head) {
		DCELVertex* walker;
		int length = 1;	
		while(walker->next) {
			walker = walker->next;
			length++;
		}
		return length;
	}
	else return 0;
}
void VertexList::removeFromList(DCELVertex* vertex) 
{
	if(head) {
		DCELVertex* walker = head;
		if(walker == vertex) {
			head = walker->next;
			delete walker;
		}
		while(walker->next != vertex && walker->next != NULL) {
			walker = walker->next;
		} 	
		if(walker->next = vertex) {
			walker->next = vertex->next;
			delete vertex;
		}
	}
}
