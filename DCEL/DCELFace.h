
class DCELFace
{
public:
	DCELFace();
	~DCELFace();

	DCELHalfEdge* edge;
	bool bordered;
	DCELFace* next;
	int boundaryLength();
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