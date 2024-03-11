/* @Author
Student Name: Alper Tutum Student ID : 150210088>
Date: 06.06.2023 */

#include <iostream>
#include <vector>
#include <chrono>
#include "../include/BSTree.h"
#include "../include/BSTNode.h"

using namespace std;
using namespace std::chrono;

BSTree::BSTree(){
    this->root = NULL;
}

void BSTree::removeSubtree(BSDNA* root){
    if (root == NULL) return;

    if (root->getLeft()!=NULL){
        removeSubtree(root->getLeft());
    }
    if (root->getRight()!=NULL){
        removeSubtree(root->getRight());
    }

    delete root;
}

BSDNA* BSTree::getRoot() const{
    return this->root;
}

BSDNA* BSTree::findMax(BSDNA* ptr){
    if (ptr!=NULL){
        while (ptr->getRight()!=NULL){
            ptr = ptr->getRight();
        }

        return ptr;
    }else{
        return NULL;
    }
}

void BSTree::searchDNANode(int chromosome, int position, string altBase){
    auto start = high_resolution_clock::now();
    BSDNA* ptr = this->root;

    if (ptr != NULL){ //check if the tree is empty
        while (!(ptr->getChrom()==chromosome && ptr->getPos()==position && ptr->getBase()==altBase)){
            if(ptr->isLeaf()){
                //if the temporary pointer reached a leaf and still couldn't find the DNA then there is no such DNA
                cout << chromosome << " " << position << " " << altBase << " could not be found" << endl;
                return;
            }
            if ((chromosome > ptr->getChrom()) || ((chromosome == ptr->getChrom()) && (position > ptr->getPos()))){
                ptr = ptr->getRight();
            }else if ((chromosome < ptr->getChrom()) || ((chromosome == ptr->getChrom()) && (position < ptr->getPos()))){
                ptr = ptr->getLeft();
            }else{
                cout << chromosome << " " << position << " " << altBase << " could not be found" << endl;
                return;
            }
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        cout << ptr->getChrom() << " " << ptr->getPos() << " " << ptr->getBase() << " was found in " << duration.count() << "ms" << endl;
    }else{
        cout << chromosome << " " << position << " " << altBase << " could not be found" << endl;
        return;
    }
}

bool BSTree::addDNANode(int chromosome, int position, string altBase){
    BSDNA* ptr = this->root;
    BSDNA* newNode = new BSDNA(chromosome, position, altBase);

    if(ptr == NULL){
        //if this is the first node to be added
        this->root = newNode;
        return true;
    }else{
        while (!ptr->isLeaf()){
            if ((newNode->compare(ptr))>0){
                if (ptr->getRight()==NULL){
                    break;
                }
                ptr = ptr->getRight();
            }else if ((newNode->compare(ptr))<0){
                if (ptr->getLeft()==NULL){
                    break;
                }
                ptr = ptr->getLeft();
            }else{
                //cout << "DNA node already exists" << endl;
                delete newNode;
                return false;
            }
        }
        if ((newNode->compare(ptr))>0){
            ptr->setRight(newNode);
            newNode->setParent(ptr);
            return true;
        }else if ((newNode->compare(ptr))<0){
            ptr->setLeft(newNode);
            newNode->setParent(ptr);
            return true;
        }else{
            //cout << "DNA node already exists" << endl;
            delete newNode;
            return false;
        }
    }
}

void BSTree::removeDNANode(int chromosome, int position, string altBase){
    auto start = high_resolution_clock::now();
    BSDNA* ptr = this->root;

    if(ptr!=NULL){
        while (!(ptr->getChrom()==chromosome && ptr->getPos()==position && ptr->getBase()==altBase)){
            /*if (ptr->isLeaf()){
                cout << chromosome << " " << position << " " << altBase << " could not be deleted because it could not be found" << endl;
                return;
            }*/
            if ((chromosome > ptr->getChrom()) || ((chromosome == ptr->getChrom()) && (position > ptr->getPos()))){
                if (ptr->getRight()==NULL){
                    cout << chromosome << " " << position << " " << altBase << " could not be deleted because it could not be found" << endl;
                    return;
                }
                ptr = ptr->getRight();
            }else{
                if (ptr->getLeft()==NULL){
                    cout << chromosome << " " << position << " " << altBase << " could not be deleted because it could not be found" << endl;
                    return;
                }
                ptr = ptr->getLeft();
            }
        }

        if (ptr->isLeaf()){
            if (ptr==this->root){
                //if there is only one node
                delete ptr;
            }else if ((ptr->getParent()->getChrom() > ptr->getChrom()) || ((ptr->getParent()->getChrom() == ptr->getChrom()) && (ptr->getParent()->getPos() > ptr->getPos()))){
                //if ptr is the left child
                ptr->getParent()->setLeft(NULL);
                delete ptr;
            }else{
                //if ptr is the right child
                ptr->getParent()->setRight(NULL);
                delete ptr;
            }
        }else if (ptr->getLeft()!=NULL && ptr->getRight()==NULL){//if ptr has only left subtree
            if (ptr==this->root){
                BSDNA* temp = ptr->getLeft();
                
                temp->setParent(NULL);
                delete ptr;
                this->root = temp;
            }else if ((ptr->getParent()->getChrom() > ptr->getChrom()) || ((ptr->getParent()->getChrom() == ptr->getChrom()) && (ptr->getParent()->getPos() > ptr->getPos()))){
                //if ptr is the left child
                ptr->getParent()->setLeft(ptr->getLeft());
                ptr->getLeft()->setParent(ptr->getParent());
                delete ptr;
            }else{
                //if ptr is the right child
                ptr->getParent()->setRight(ptr->getLeft());
                ptr->getLeft()->setParent(ptr->getParent());
                delete ptr;
            }
        }else if (ptr->getLeft()==NULL && ptr->getRight()!=NULL){//if ptr has only right subtree
            if (ptr==this->root){
                BSDNA* temp = ptr->getRight();

                temp->setParent(NULL);
                delete ptr;
                this->root = temp;
            }else if ((ptr->getParent()->getChrom() > ptr->getChrom()) || ((ptr->getParent()->getChrom() == ptr->getChrom()) && (ptr->getParent()->getPos() > ptr->getPos()))){
                //if ptr is the left child
                ptr->getParent()->setLeft(ptr->getRight());
                ptr->getRight()->setParent(ptr->getParent());
                delete ptr;
            }else{
                //if ptr is the right child
                ptr->getParent()->setRight(ptr->getRight());
                ptr->getRight()->setParent(ptr->getParent());
                delete ptr;
            }
        }else{//if the node is internal and has two subtrees

            BSDNA* temp = this->findMax(ptr->getLeft());
            //temp is the greatest node in the left subtree of the node we want to delete
            ptr->changeData(temp->getChrom(), temp->getPos(), temp->getBase());
            if (temp->isLeaf()){
                if (temp == ptr->getLeft()){
                    //if there is only one node in ptr's left subtree
                    temp->getParent()->setLeft(NULL);
                    delete temp;
                }else{
                    //if there is more than one node to the left of ptr and temp is a leaf temp has to be the right child
                    temp->getParent()->setRight(NULL);
                    delete temp;
                }
            }else{
                //if temp is not a leaf it can only have a left subtree
                temp->getParent()->setRight(temp->getLeft());
                temp->getLeft()->setParent(temp->getParent());
                delete temp;
            }
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        cout << chromosome << " " << position << " " << altBase << " was deleted in " << duration.count() << "ms" << endl;
    }else{
        cout << chromosome << " " << position << " " << altBase << " could not be deleted because it could not be found" << endl;
    }
}

void BSTree::listSubtree(BSDNA* root, BSDNA* max){
    //print data of all nodes using inorder traversal
    if(root==NULL) return;

    listSubtree(root->getLeft(), max);
    root->printData();
    if(root!=max) cout << ",";
    listSubtree(root->getRight(), max);
}

void BSTree::fillVector(BSDNA* root, vector<BSDNA> &v){
    //vector is filled in inorder so that the vector is sorted
    if (root == NULL) return;

    fillVector(root->getLeft(), v);
    v.push_back(*root);
    fillVector(root->getRight(), v);
}

void BSTree::calculateTruePositive(vector<BSDNA> &v1, vector<BSDNA> &v2, int &i){
    //the vectors are already sorted
    int n1 = v1.size();
    int n2 = v2.size();
    int i1 = 0;
    int i2 = 0;

    while (i1<n1 && i2< n2){
        if (v1[i1].compare(&v2[i2])<0){
            i1++;
        }else if (v1[i1].compare(&v2[i2])>0){
            i2++;
        }else{
            //extra check for alternate bases because compare() function only compares chromosome and position
            if(v1[i1].getBase()==v2[i2].getBase()) i++;
            i1++;
            i2++;
        }
    }
}

BSTree::~BSTree(){
    removeSubtree(this->root);
}