
class DCELFace  
{
public:
	DCELFace();
	~DCELFace();

	DCELHalfEdge* edge;
	DCELFace* next;
};

DCELFace::DCELFace() : edge(NULL), next(NULL) 
{
}

DCELFace::~DCELFace() {

}