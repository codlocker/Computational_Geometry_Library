#include "monotone.h"
using namespace std;

void triangulate() {
	DCELFace* walker = Faces.head;
	vector<pair<DCELVertex *, DCELVertex *> > pendingDiagonals;
	while(walker) {
		if(walker->boundaryLength() > 3 && walker->bordered) {
			vector<DCELVertex *>::iterator it;
			vector<DCELVertex *> list = walker->sortedVertices();
			stack<DCELVertex *> stck;
			it = list.begin();
			stck.push((*it));
			it++;
			stck.push((*it));
			it++;
			for(;it != list.end(); it++) 
			{
				
			}
		}
		walker = walker->next;
	}
}