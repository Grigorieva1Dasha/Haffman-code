#pragma once
#include<iostream>
#include"Node.h"

using namespace std;

struct mySort {
	bool operator()(Node* l, Node* r) {
		return r->w > l->w;
	}
};
