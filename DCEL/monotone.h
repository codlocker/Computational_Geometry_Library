#include <iostream>
#include "origin.h"
using namespace std;
#define REGULAR_VERTEX 0
#define START_VERTEX 1
#define END_VERTEX 2
#define MERGE_VERTEX 3
#define SPLIT_VERTEX 4
#define COLLINEAR 1 /*!< Macro defined for identifying 3 collinear points */
#define CLOCKWISE 2 /*!< Macro defined for identifying 3 points that rotate clockwise */
#define ANTICLOCKWISE 3 /*!< Macro defined for identifying 3 points that rotate anticlockwise */
class func {
public:
  bool operator() (DCELHalfEdge* e1, DCELHalfEdge* e2) {
    return e1->origin->y < e2->origin->y;
  }
};
set<DCELHalfEdge *, func>tree;
void printTree() {
  set<DCELHalfEdge *, func>::iterator it;
  for (it = tree.begin(); it != tree.end(); it++) {
    cout << (*it)->meta << "->helper = ";
    (*it)->helper->print();
  }
  cout<<"___________"<<endl;
}
int vlen;
int orientation(DCELVertex* a, DCELVertex* b, DCELVertex* c) {
  double dif;
  dif = (b->y - a->y) * (c->x - b->x) - (b->x - a->x) * (c->y - b->y);
  if (dif == 0) {
    return COLLINEAR;
  } else if (dif > 0 ) {
    return CLOCKWISE;
  } else {
    return ANTICLOCKWISE;
  }
}
bool below(DCELVertex* v1, DCELVertex* v2) {
  if (v1->y != v2->y)
    return v1->y > v2->y;
  else
    return v1->x < v2->x;
}
void form_vertex_type() {
  DCELVertex *v = Vertices.head;
  vlen = Vertices.length;
  // cout<<vlen<<endl;
  for (int i = 0; i < vlen; i++) {
    // cout<<"Comparing: ";
    // cout<<"\n prev neighbor = ";
    // v->edge->twin->origin->print();
    // cout<<"v = ";v->print();
    // cout<<"\n next neighbor = ";
    // v->edge->getPrev()->origin->print();
    // cout<<"----"<<endl;
    if (below(v, v->edge->twin->origin) && below(v, v->edge->getPrev()->origin)) {
      if (orientation(v->edge->twin->origin, v, v->edge->getPrev()->origin) == CLOCKWISE) {
        v->type = START_VERTEX;
        // v->print();cout<<" - START VERTEX"<<endl;
      }
      else {
        v->type = SPLIT_VERTEX;
        // v->print();cout<<" - SPLIT VERTEX"<<endl;
      }
    }
    else if (below(v->edge->twin->origin, v) && below(v->edge->getPrev()->origin, v)) {
      if (orientation(v->edge->twin->origin, v, v->edge->getPrev()->origin) == CLOCKWISE) {
        v->type = END_VERTEX;
        // v->print();cout<<" - END VERTEX"<<endl;
      }
      else {
        v->type = MERGE_VERTEX;
        // v->print();cout<<" - MERGE VERTEX"<<endl;
      }
    }
    else {
      v->type = REGULAR_VERTEX;
      // v->print();cout<<" - REGULAR VERTEX"<<endl;
    }
    v = v->next;
    // cout<<endl;
  }
}
void HANDLE_START_VERTEX(DCELVertex *v) {
  tree.insert(v->edge);
  // cout << "added " << v->edge->meta << " to Tree" << endl;
  v->edge->helper = v;
  // cout << v->edge->meta << "->helper = ";
  // v->print();
}
void HANDLE_END_VERTEX(DCELVertex *v) {
  // cout<<"Handling end vertex ";
  if (v->edge->getPrev()->helper)
    if (v->edge->getPrev()->helper->type == MERGE_VERTEX) {
      insertDiagonal(v, v->edge->getPrev()->helper);
    }
  tree.erase(v->edge->getPrev());
  // cout << "removed " << v->edge->meta << " from Tree" << endl;
}
bool left_edgeto_vertex(const DCELHalfEdge* e1, const DCELHalfEdge* e2) {
  return (e1->origin->y > e2->origin->y) && (e1->origin->x < e2->origin->x);
}
void HANDLE_SPLIT_VERTEX(DCELVertex *v) {
  printTree();
  set<DCELHalfEdge *, func>::iterator it;
  it = std::lower_bound(tree.begin(), tree.end(), v->edge, left_edgeto_vertex);
  if (it != tree.begin()) {
    it--;
  }
  DCELHalfEdge *s = *it;
  // cout << "\nInserting diagonal between " << v->x << " " << v->y << " and ";
  // s->helper->print(); cout << endl;
  insertDiagonal(v, s->helper);
  s->helper = v;
  // cout << s->meta << "->helper = ";
  // v->print();
  tree.insert(v->edge);
  // cout << "added " << v->edge->meta << " to Tree" << endl;
  v->edge->helper = v;
}
void HANDLE_MERGE_VERTEX(DCELVertex *v) {
  // cout<<"Handling Merge Vertex ";
  // v->print();
  if (v->edge->getPrev()->helper)
    if (v->edge->getPrev()->helper->type == MERGE_VERTEX) {
      insertDiagonal(v, v->edge->getPrev()->helper);
    }
  tree.erase(v->edge->getPrev());
  // cout << "removed " << v->edge->meta << " from Tree" << endl;
  printTree();
  set<DCELHalfEdge *, func>::iterator it;
  it = std::lower_bound(tree.begin(), tree.end(), v->edge, left_edgeto_vertex);
  if (it != tree.begin()) {
    it--;
  }
  DCELHalfEdge *s = *it;
  if (s->helper)
    if (s->helper->type == MERGE_VERTEX) {
      // cout<<"debug"<<endl;
      insertDiagonal(v, s->helper);
    }
  s->helper = v;
  // cout << s->meta << "->helper = ";
  // v->print();
}
void HANDLE_REGULAR_VERTEX(DCELVertex *v) {
  // cout<<"Handling ";
  // v->print();
  // cout<<v->edge->twin->meta<<" originating from ";
  // v->edge->twin->origin->print();
  if (below(v, v->edge->twin->origin)) {
    // cout << "below" << endl;
    if (v->edge->getPrev()->helper->type == MERGE_VERTEX) {
      insertDiagonal(v, v->edge->getPrev()->helper);
    }
    tree.erase(v->edge->getPrev());
    tree.insert(v->edge);
    // cout << "added " << v->edge->meta << " to Tree" << endl;
    v->edge->helper = v;
    // cout << v->edge->meta << "->helper = ";
    // v->print();
  }
  else {
    set<DCELHalfEdge *, func>::iterator it;
    printTree();
    it = std::lower_bound(tree.begin(), tree.end(), v->edge, left_edgeto_vertex);
    if (it != tree.begin()) {
      it--;
    }
    DCELHalfEdge *s = *it;
    // cout<<"s = "<<s->meta<<endl;
    if (s->helper->type == MERGE_VERTEX) {
      // cout<<"bugger"<<endl;
      insertDiagonal(v, s->helper);
    }
    s->helper = v;
    // cout << s->meta << "->helper = ";
    // v->print();
  }
}
int split_into_monotone() {
  // cout<<"Splitting"<<endl;
  form_vertex_type();
  DCELVertex *v = Vertices.head;
  int i = 0;
  while (v) {
    // cout<<i++<<" ";
    // v->print();
    if (v->type == START_VERTEX) {
      // cout<<"start vertex here\n";
      HANDLE_START_VERTEX(v);
    }
    else if (v->type == SPLIT_VERTEX) {
      // cout << "split vertex here\n";
      HANDLE_SPLIT_VERTEX(v);
    }
    else if (v->type == END_VERTEX) {
      // cout<<"end vertex here\n";
      HANDLE_END_VERTEX(v);
    }
    else if (v->type == MERGE_VERTEX) {
      // cout<<"merge vertex here\n";
      HANDLE_MERGE_VERTEX(v);
    }
    else if (v->type == REGULAR_VERTEX) {
      // cout<<"regular vertex here\n";
      HANDLE_REGULAR_VERTEX(v);
    }
    // cout << "Handling over" << endl;
    v = v->next;
  }
  // cout << "OutOfTheLoop" << endl;
}