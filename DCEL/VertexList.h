#include <iostream> 
using namespace std;
class VertexList
{
public:
	VertexList(void);
	~VertexList(void);

	DCELVertex* head;
	DCELVertex* tail;

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
	if ( head ) {
		if((head->y < newVertex->y) || (head->y == newVertex->y && head->x > newVertex->x)) {
			newVertex->next = head;
			head = newVertex;
			return;
		}
		DCELVertex* walker = head;
		while(walker->next) {
			if((walker->next->y < newVertex->y) || (walker->next->y == newVertex->y && walker->next->x > newVertex->x)) break;
			walker = walker->next;
		}
		newVertex->next = walker->next;
		walker->next = newVertex;
	}
	else {
		head = newVertex;
		tail = newVertex;
	}
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
