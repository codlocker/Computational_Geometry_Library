
class DCELFace
{
public:
	DCELFace();
	~DCELFace();

	DCELHalfEdge* edge;
	bool bordered;
	DCELFace* next;
	int boundaryLength();
	vector<DCELVertex *> sortedVertices();
};

DCELFace::DCELFace() : edge(NULL), next(NULL), bordered(true)
{
}

DCELFace::~DCELFace() {

}

int DCELFace::boundaryLength() {
	int length = 0;
	DCELHalfEdge* walker = edge;
	do {
		walker = walker->next;
		length++;
	} while (walker != edge);
	return length;
}

vector<DCELVertex *> DCELFace::sortedVertices() {
	vector<DCELVertex*> list;
	DCELVertex* highest = edge->origin;
	DCELHalfEdge* walker = edge;
	DCELHalfEdge *left, *right;
	do {	
		if (walker->origin->y > highest->y || (walker->origin->y == highest->y && walker->origin->x < highest->x)) {
			highest = walker->origin;
		}
		walker = walker->next;	
	} while (walker != edge);
	
	list.push_back(highest);
	left = highest->edge->next;
	right = highest->edge->getPrev();
	do {
		if(left->origin->y > right->origin->y || (left->origin->y == right->origin->y && left->origin->x < right->origin->x)) {
			left = left->next;
			list.push_back(left->origin);
		}
		else {
			right = right->getPrev();
			list.push_back(right->origin);
		}
	}
	while(left != right );
	return list;
}