/* @Author
Student Name: Alper Tutum Student ID : 150210088>
Date: 06.06.2023 */

#pragma once

#include "AVLNode.h"

class AVLTree{
private:
    AVLDNA* root;
    void rotate_right(AVLDNA*);
    void rotate_left(AVLDNA*);
    void balance(AVLDNA*);
    void balanceTree(AVLDNA*);
    void removeSubtree(AVLDNA*);
public:
    AVLTree();
    AVLDNA* getRoot() const;
    AVLDNA* findMax(AVLDNA*);
    void search_node(int, int, std::string);
    bool add_node(int, int, std::string);
    void remove_node(int, int, std::string);
    void list_subtree(AVLDNA*, AVLDNA*);
    void fillVector(AVLDNA*, std::vector<AVLDNA>&);
    void calculate_true_positive(std::vector<AVLDNA>&, std::vector<AVLDNA>&, int&);
    ~AVLTree();
};