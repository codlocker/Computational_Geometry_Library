#include "monotone.h"
using namespace std;

void triangulate() {
	DCELFace* walker = Faces.head;
	vector<pair<DCELVertex *, DCELVertex *> > pendingDiagonals;
	while(walker) {
		if(walker->boundaryLength() > 3 && walker->bordered) {
			vector<pair<DCELVertex *, int> >::iterator it;
			vector<pair<DCELVertex *, int> > list = walker->sortedVertices();
			stack<pair<DCELVertex *, int> > stck;
			it = list.begin();
			stck.push((*it));
			it++;
			stck.push((*it));
			it++;
			for(it = list.begin();it != list.end(); it++) 
			{
				if(it+1 != list.end() && list.second != stck.top().second) {
					while(stck.size > 1) {
						pendingDiagonals.push_back(stck.top().first, (*it).first);
						stck.pop();
					}
					stck.push((*it-1));
					stck.push((*it));
				}
				else {
					while(!stck.empty) {
						if(stck.top().second == 1) {
							if(orientation((*it).first,(*it).first->edge->next->origin),stck.top().first == ANTICLOCKWISE)
								pendingDiagonals.push_back(stck.top().first, (*it).first);
							else break;
						}
						stck.pop();
					}
					stck.pop();
				}
			}
		}
		walker = walker->next;
	}
}