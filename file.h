#ifndef ASSIGNMENT_5__FILE_H_
#define ASSIGNMENT_5__FILE_H_

#include "UPC.h"
#include "BST.h"

BST<UPC> buildTree(const std::string& filepath);

BST<UPC> readLines(std::istream& file);

void readTree(std::istream& line, BST<UPC>& tree);

#endif //ASSIGNMENT_5__FILE_H_
