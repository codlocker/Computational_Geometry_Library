#include "DCELFace.h"

using namespace std;
class FaceList
{
public:
	FaceList();
	~FaceList();	
	DCELFace* head;

	void addToList(DCELFace* newFace);
	int length();
	void removeFromList(DCELFace* face);
};

FaceList::FaceList() : head(NULL)
{
}

FaceList::~FaceList()
{
}

void FaceList::addToList(DCELFace* newFace) {
	newFace->globalnext = head;
	head = newFace;
}

int FaceList::length() {
	if(head) {
		DCELFace* walker;
		int length = 1;	
		while(walker->globalnext) {
			walker = walker->globalnext;
			length++;
		}
		return length;
	}
	else return 0;
}

void FaceList::removeFromList(DCELFace* face) {
	
}



