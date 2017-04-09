using namespace std;
class DCELVertex  
{
public:
	DCELVertex();
	~DCELVertex();

	double x;
	double y;
	DCELHalfEdge* leaving;
	DCELHalfEdge* getEdgeTo(DCELVertex* v);
	void setCoords(double a, double b);
	void print();
	DCELVertex* next;
	DCELVertex* prev;
};

DCELVertex::DCELVertex(): x(0.0), y(0.0), leaving(NULL), prev(NULL), next(NULL)
{
}
DCELVertex::~DCELVertex()
{

}

void DCELVertex::setCoords(double a, double b) {
	x = a;
	y = b;
}

void DCELVertex::print() {
	cout<<x<<" "<<y<<endl;
}

DCELHalfEdge* DCELVertex::getEdgeTo(DCELVertex* v)
{
	DCELHalfEdge* rval = NULL;

	if (leaving) {
		if (leaving->twin->origin == v) {
			rval = leaving;
		} else {
			DCELHalfEdge* test = leaving->twin->next;
			while (rval == NULL && test != leaving) {
				if (test->twin->origin == v) {
					rval = test;
				} else {
					test = test->twin->next;
				}
			}
		}
	}

	return rval;
}