#ifndef ASSIGNMENT_5__FILE_H_
#define ASSIGNMENT_5__FILE_H_

#include "UPC.h"
#include "BST.h"

/**
 * @param filepath Path of UPC database file
 * @return Tree representing the database
 */
BST<UPC> buildTree(const std::string& filepath);

/**
 * @param file Database file
 * @return Entries in file
 */
std::vector<std::tuple<UPC, std::string>> readLines(std::istream& file);

/**
 * Reads a single record and adds it to tree.
 * @param file Database file
 */
std::tuple<UPC, std::string> readEntry(std::istream& file);

#endif //ASSIGNMENT_5__FILE_H_
