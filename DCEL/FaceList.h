#include "DCELFace.h"

using namespace std;
class FaceList
{
public:
	FaceList();
	~FaceList();
	DCELFace* head;
	DCELFace* tail;

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
	if (head)
	{
		tail->next = newFace;
		tail = newFace;
	}
	else {
		head = newFace;
		tail = newFace;
	}
}

int FaceList::length() {
	if (head) {
		DCELFace* walker;
		int length = 1;
		while (walker->next) {
			walker = walker->next;
			length++;
		}
		return length;
	}
	else return 0;
}

void FaceList::removeFromList(DCELFace* face) {
	DCELFace* walker = head;
	while (walker) {
		if (walker->next == face)
			break;
		walker = walker->next;
	}
	walker->next = walker->next->next;
	delete face;
}



