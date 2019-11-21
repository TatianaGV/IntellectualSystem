#ifndef LAB02_ALGORITMS_H
#define LAB02_ALGORITMS_H

#include <functional>
#include <iostream>
#include <unordered_set>
#include <queue>
#include "Node.h"

using std::function;

Node* AStar(Node* node, function<int(Node*)> h);
Node* IDAStar(Node* node, function<int(Node*)> h);
Node* IDAStar2(Node* node, function<int(Node*)> h, int deep);


#endif //LAB02_ALGORITMS_H
