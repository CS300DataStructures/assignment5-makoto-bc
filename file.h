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
 * @return The database
 */
BST<UPC> readLines(std::istream& file);

/**
 * Reads a single record and adds it to tree.
 * @param line Database file
 */
void readTree(std::istream& line, BST<UPC>& tree);

#endif //ASSIGNMENT_5__FILE_H_
