#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<list>
#include"Node.h"
#include"mySort.h"

using namespace std;
map<char, vector<bool>>tab;
vector<bool>code;

Node* node(const char* filename) {
	ifstream in(filename, ios::binary);
	map<char, int>gur;
	list<Node*> heapNode;
	while (!in.eof()) {
		char c = in.get();
		gur[c]++;
	}
	for (map<char, int>::iterator it = gur.begin(); it != gur.end(); it++) {
		Node* p = new Node;
		p->w = it->second;
		p->c = it->first;
		heapNode.push_back(p);
	}
	while (heapNode.size() != 1) {
		heapNode.sort(mySort());
		Node* sonl = heapNode.front();
		heapNode.pop_front();
		Node* sonr = heapNode.front();
		heapNode.pop_front();
		Node* parent = new Node(sonl, sonr);
		heapNode.push_back(parent);
	}
	return heapNode.front();
}
void build_code_table(Node* root) {
	if (root->left != NULL) {
		code.push_back(0);
		build_code_table(root->left);
	}
	if (root->right != NULL) {
		code.push_back(1);
		build_code_table(root->right);
	}
	if (root->left == NULL && root->right == NULL) {
		tab[root->c] = code;
	}
	if (code.size() != 0) {
		code.pop_back();
	}
}
void coder(const char* file, const char* file2) {
	ifstream in(file, ios::binary);
	ofstream out(file2, ios::out | ios::binary);
	int count = 0;
	char buf = 0;
	char sym = in.get();
	while (!in.eof()) {
		vector<bool> v = tab[sym];
		for (int i = 0; i < v.size(); i++) {
			buf = buf | v[i] << (7 - count);
			count++;
			if (count == 8) {
				count = 0;
				out << buf;
				buf = 0;
			}
		}
		sym = in.get();
	}
	if (count != 0) {
		out << buf;
	}
	in.close();
	out.close();
}
void decoder(const char* filename, const char* filename2, Node*root) {

	ifstream in(filename, ios::binary);
	ofstream out(filename2, ios::out | ios::binary);
	int count = 0;
	bool buf = 0;
	char byte;
	Node* p = root;
	byte = in.get();
	while (!in.eof()) {
		buf = byte & (1 << (7 - count));
		if (buf == 1)
			p = p->right;
		else
			p = p->left;
		if (p->left == NULL && p->right == NULL) {
			out << p->c;
			p = root;
		}
		count++;
		if (count == 8) {
			count = 0;
			byte = in.get();
		}
	}
	in.close();
	out.close();
}
