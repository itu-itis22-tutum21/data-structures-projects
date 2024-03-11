/* @Author
Student Name: Alper Tutum Student ID : 150210088>
Date: 06.06.2023 */

#pragma once

#include "BSTNode.h"
#include <string>
#include <vector>

class BSTree{
private:
    BSDNA* root;
    void removeSubtree(BSDNA*);
public:
    BSTree();
    BSDNA* getRoot() const;
    BSDNA* findMax(BSDNA*);
    void searchDNANode(int, int, string);
    bool addDNANode(int, int, string);
    void removeDNANode(int, int, string);
    void listSubtree(BSDNA*, BSDNA*);
    void fillVector(BSDNA*, vector<BSDNA>&);
    void calculateTruePositive(vector<BSDNA>&, vector<BSDNA>&, int&);
    ~BSTree();
};