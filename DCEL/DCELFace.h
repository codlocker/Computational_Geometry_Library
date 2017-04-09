
class DCELFace  
{
public:
	DCELFace();
	~DCELFace();

	DCELHalfEdge* edge;
	DCELFace* globalnext;
};

DCELFace::DCELFace() : edge(NULL), globalnext(NULL) 
{
}

DCELFace::~DCELFace() {

}