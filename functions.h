#pragma once
#include"mySort.h"

Node* node(const char* filename);
void build_code_table(Node* root);
void coder(const char* file, const char* file2);
void decoder(const char* file, const char* file2, Node*root);
