/* @Author
Student Name: Alper Tutum Student ID : 150210088>
Date: 06.06.2023 */

#include <iostream>
#include "../include/ListNode.h"

using namespace std;

ListDNA::ListDNA(int chrom, int pos, string base){
    this->chromosome = chrom;
    this->position = pos;
    this->altBase = base;
    this->next = NULL;
}

int ListDNA::getChrom() const{
    return this->chromosome;
}

int ListDNA::getPos() const{
    return this->position;
}

string ListDNA::getBase() const{
    return this->altBase;
}

ListDNA* ListDNA::getNext() const{
    return this->next;
}

void ListDNA::setNext(ListDNA* ptr){
    this->next = ptr;
}