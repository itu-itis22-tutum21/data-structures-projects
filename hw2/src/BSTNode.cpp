/* @Author
Student Name: Alper Tutum Student ID : 150210088>
Date: 06.06.2023 */

#include <iostream>
#include "../include/BSTNode.h"

using namespace std;

BSDNA::BSDNA(int chrom, int pos, string base){
    this->chromosome = chrom;
    this->position = pos;
    this->altBase = base;
    this->right = NULL;
    this->left = NULL;
    this->parent = NULL;
}

int BSDNA::getChrom() const{
    return this->chromosome;
}

int BSDNA::getPos() const{
    return this->position;
}

string BSDNA::getBase() const{
    return this->altBase;
}

BSDNA* BSDNA::getLeft() const{
    return this->left;
}

BSDNA* BSDNA::getRight() const{
    return this->right;
}

BSDNA* BSDNA::getParent() const{
    return this->parent;
}

int BSDNA::compare(BSDNA* ptr) const{
    if ((this->chromosome>ptr->chromosome) || ((this->chromosome==ptr->chromosome) && (this->position>ptr->position))){
        return 1;
    }else if ((this->chromosome<ptr->chromosome) || ((this->chromosome==ptr->chromosome) && (this->position<ptr->position))){
        return -1;
    }else{
        return 0;
    }
}

void BSDNA::setLeft(BSDNA* ptr){
    this->left = ptr;
}

void BSDNA::setRight(BSDNA* ptr){
    this->right = ptr;
}

void BSDNA::setParent(BSDNA* ptr){
    this->parent = ptr;
}

void BSDNA::changeData(int chrom, int pos, string base){
    this->chromosome = chrom;
    this->position = pos;
    this->altBase = base;
}

void BSDNA::printData(){
    cout << this->chromosome << " " << this->position << " " << this->altBase;
}

bool BSDNA::isLeaf(){
    if (this->left==NULL && this->right==NULL){
        return true;
    }else return false;
}