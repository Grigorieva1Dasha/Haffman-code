#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<vector>
#include<list>
#include"Node.h"
#include"mySort.h"
#include"functions.h"

using namespace std;

int main(void) {
	setlocale(LC_ALL, "Russian");
	ifstream in("in.txt", ios::binary);
	if (!in.is_open()) {
		cout << "Не удается открыть файл" << endl;
		return -1;
	}
	Node* root = node("in.txt");
	build_code_table(root);
	coder("in.txt", "coder.txt");
	decoder("coder.txt", "decoder.txt", root);
	system("pause");
	return 0;
}
