
class DCELFace  
{
public:
	DCELFace();
	~DCELFace();

	DCELHalfEdge* edge;
	bool bordered;
	DCELFace* next;
};

DCELFace::DCELFace() : edge(NULL), next(NULL), bordered(true)
{
}

DCELFace::~DCELFace() {

}