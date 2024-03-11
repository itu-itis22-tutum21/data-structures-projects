/* @Author
Student Name: Alper Tutum Student ID : 150210088>
Date: 06.06.2023 */

#pragma once
#include <string>

#include "ListNode.h"

class LinkedList{
private:
    ListDNA* head;
public:
    LinkedList();
    ListDNA* getHead();
    void searchDNANode(int, int, std::string);
    bool addDNANode(int, int, std::string);
    bool removeDNANode(int, int, std::string);
    void print_list();
    void calculateTruePositive(LinkedList*);
    ~LinkedList();
};