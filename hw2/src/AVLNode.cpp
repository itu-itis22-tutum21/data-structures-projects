/* @Author
Student Name: Alper Tutum Student ID : 150210088>
Date: 06.06.2023 */

#include <iostream>
#include "../include/AVLNode.h"

using namespace std;

AVLDNA::AVLDNA(int chrom, int pos, string base){
    this->chromosome = chrom;
    this->position = pos;
    this->altBase = base;
    this->left = NULL;
    this->right = NULL;
    this->parent = NULL;
    this->height = 0;
}

int AVLDNA::getChrom() const{
    return this->chromosome;
}

int AVLDNA::getPos() const{
    return this->position;
}

string AVLDNA::getBase() const{
    return this->altBase;
}

int AVLDNA::getHeight() const{
    return this->height;
}

AVLDNA* AVLDNA::getLeft() const{
    return this->left;
}

AVLDNA* AVLDNA::getRight() const{
    return this->right;
}

AVLDNA* AVLDNA::getParent() const{
    return this->parent;
}

int AVLDNA::compare(AVLDNA* ptr) const{
    if ((this->chromosome>ptr->chromosome) || ((this->chromosome==ptr->chromosome) && (this->position>ptr->position))){
        return 1;
    }else if ((this->chromosome<ptr->chromosome) || ((this->chromosome==ptr->chromosome) && (this->position<ptr->position))){
        return -1;
    }else{
        return 0;
    }
}

void AVLDNA::setHeight(int h){
    this->height = h;
}

int AVLDNA::find_height(AVLDNA* ptr){
    if(ptr==NULL){
        return -1;
    }else{
        ptr->setHeight(max(find_height(ptr->getLeft()), find_height(ptr->getRight()))+1);
        return ptr->height;
    }
}

int AVLDNA::getBalanceFactor(){
    return this->find_height(this->left) - this->find_height(this->right);
}

void AVLDNA::setLeft(AVLDNA* ptr){
    this->left = ptr;
}

void AVLDNA::setRight(AVLDNA* ptr){
    this->right = ptr;
}

void AVLDNA::setParent(AVLDNA* ptr){
    this->parent = ptr;
}

void AVLDNA::changeData(int chrom, int pos, string base){
    this->chromosome = chrom;
    this->position = pos;
    this->altBase = base;
}

void AVLDNA::print_data(){
    cout << this->chromosome << " " << this->position << " " << this->altBase;
}

bool AVLDNA::isLeaf(){
    if (this->left==NULL && this->right==NULL){
        return true;
    }else return false;
}