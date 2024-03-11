/* @Author
Student Name: Alper Tutum Student ID : 150210088>
Date: 06.06.2023 */

#include <iostream>
#include "../include/AVLTree.h"
#include "../include/AVLNode.h"

using namespace std;
using namespace std::chrono;

AVLTree::AVLTree(){
    this->root = NULL;
}

void AVLTree::rotate_right(AVLDNA* ptr){
    AVLDNA* newParent = ptr->getLeft();
    AVLDNA* temp = newParent->getRight();

    newParent->setRight(ptr);
    ptr->setLeft(temp);

    if (temp!=NULL){
        temp->setParent(ptr);
    }
    if (ptr!=this->root){
        if (ptr==ptr->getParent()->getLeft()){
            ptr->getParent()->setLeft(newParent);
        }else{
            ptr->getParent()->setRight(newParent);
        }
    }else{
        this->root = newParent;
    }

    newParent->setParent(ptr->getParent());
    ptr->setParent(newParent);

    ptr->setHeight(max(ptr->find_height(temp), ptr->find_height(ptr->getRight()))+1);
    newParent->setHeight(max(newParent->getLeft()->getHeight(), ptr->getHeight())+1);
}

void AVLTree::rotate_left(AVLDNA* ptr){
    AVLDNA* newParent = ptr->getRight();
    AVLDNA* temp = newParent->getLeft();

    newParent->setLeft(ptr);
    ptr->setRight(temp);

    if(temp!=NULL){
        temp->setParent(ptr);
    }
    if (ptr!=this->root){
        if (ptr==ptr->getParent()->getLeft()){
            ptr->getParent()->setLeft(newParent);
        }else{
            ptr->getParent()->setRight(newParent);
        }
    }else{
        this->root = newParent;
    }

    newParent->setParent(ptr->getParent());
    ptr->setParent(newParent);

    ptr->setHeight(max(ptr->find_height(ptr->getLeft()), ptr->find_height(temp))+1);
    newParent->setHeight(max(ptr->getHeight(), newParent->getRight()->getHeight())+1);
}

void AVLTree::balance(AVLDNA* ptr){
    if(ptr==NULL) return;
    
    if (ptr->getBalanceFactor() > 1){
        if (ptr->getLeft()->getBalanceFactor()>=0){//Left left imbalance
            this->rotate_right(ptr);
        }else{//Left right imbalance
            this->rotate_left(ptr->getLeft());
            this->rotate_right(ptr);
        }
    }else if (ptr->getBalanceFactor() < -1){
        if (ptr->getRight()->getBalanceFactor()<=0){//Right right imbalance
            this->rotate_left(ptr);
        }else{//Right left imbalance
            this->rotate_right(ptr->getRight());
            this->rotate_left(ptr);
        }
    }
}

void AVLTree::balanceTree(AVLDNA* ptr){
    //goes up from ptr to the root and balances the tree when needed
    while (ptr!=this->root){
        AVLDNA* temp = ptr;
        if (ptr->getBalanceFactor()>1 || ptr->getBalanceFactor()<-1){
            balance(ptr);
        }
        ptr = temp->getParent();
    }

    //one more iteration for reaching the root
    if (ptr->getBalanceFactor()>1 || ptr->getBalanceFactor()<-1){
        balance(ptr);
    }
}

void AVLTree::removeSubtree(AVLDNA* root){
    if (root == NULL) return;

    if (root->getLeft()!=NULL){
        removeSubtree(root->getLeft());
    }
    if (root->getRight()!=NULL){
        removeSubtree(root->getRight());
    }

    delete root;
}

AVLDNA* AVLTree::getRoot() const{
    return this->root;
}

AVLDNA* AVLTree::findMax(AVLDNA* ptr){
    if (ptr!=NULL){
        while (ptr->getRight()!=NULL){
            ptr = ptr->getRight();
        }

        return ptr;
    }else{
        return NULL;
    }
}

void AVLTree::search_node(int chromosome, int position, string altBase){
    auto start = high_resolution_clock::now();
    AVLDNA* ptr = this->root;

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

bool AVLTree::add_node(int chromosome, int position, string altBase){
    AVLDNA* ptr = this->root;
    AVLDNA* newNode = new AVLDNA(chromosome, position, altBase);

    if (ptr==NULL){
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

            //ptr is the parent of newNode
            AVLDNA* temp = ptr;
            while (temp!=this->root){
                temp->setHeight(max(ptr->find_height(temp->getLeft()), ptr->find_height(temp->getRight()))+1);
                if (temp->getParent()->getHeight()>temp->getHeight()){
                    break;
                }
                temp = temp->getParent();
            }
            if (temp==this->root){
                //if temp reaches root
                this->root->setHeight(root->getHeight()+1);
            }

            this->balanceTree(ptr);
            return true;
        }else if ((newNode->compare(ptr))<0){
            ptr->setLeft(newNode);
            newNode->setParent(ptr);

            //ptr is the parent of newNode
            AVLDNA* temp = ptr;
            while (temp!=this->root){
                temp->setHeight(max(ptr->find_height(temp->getLeft()), ptr->find_height(temp->getRight()))+1);
                if (temp->getParent()->getHeight()>temp->getHeight()){
                    break;
                }
                temp = temp->getParent();
            }
            if (temp==this->root){
                //if temp reaches root
                this->root->setHeight(root->getHeight()+1);
            }

            this->balanceTree(ptr);
            return true;
        }else{
            //cout << "DNA node already exists" << endl;
            delete newNode;
            return false;
        }
    }
}

void AVLTree::remove_node(int chromosome, int position, string altBase){
    auto start = high_resolution_clock::now();
    AVLDNA* ptr = this->root;

    if(ptr!=NULL){
        while (!(ptr->getChrom()==chromosome && ptr->getPos()==position && ptr->getBase()==altBase)){
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
                AVLDNA* parent = ptr->getParent();
                parent->setLeft(NULL);
                delete ptr;
                
                this->balanceTree(parent);
            }else{
                //if ptr is the right child
                AVLDNA* parent = ptr->getParent();
                parent->setRight(NULL);
                delete ptr;

                this->balanceTree(parent);
            }
        }else if (ptr->getLeft()!=NULL && ptr->getRight()==NULL){//if ptr has only left subtree
            if (ptr==this->root){
                AVLDNA* temp = ptr->getLeft();
                
                temp->setParent(NULL);
                delete ptr;
                this->root = temp;

                this->balance(temp);
            }else if ((ptr->getParent()->getChrom() > ptr->getChrom()) || ((ptr->getParent()->getChrom() == ptr->getChrom()) && (ptr->getParent()->getPos() > ptr->getPos()))){
                //if ptr is the left child
                AVLDNA* parent = ptr->getParent();
                parent->setLeft(ptr->getLeft());
                ptr->getLeft()->setParent(parent);
                delete ptr;

                this->balanceTree(parent);
            }else{
                //if ptr is the right child
                AVLDNA* parent = ptr->getParent();
                parent->setRight(ptr->getLeft());
                ptr->getLeft()->setParent(parent);
                delete ptr;

                this->balanceTree(parent);
            }
        }else if (ptr->getLeft()==NULL && ptr->getRight()!=NULL){//if ptr has only right subtree
            if (ptr==this->root){
                AVLDNA* temp = ptr->getRight();

                temp->setParent(NULL);
                delete ptr;
                this->root = temp;

                this->balance(temp);
            }else if ((ptr->getParent()->getChrom() > ptr->getChrom()) || ((ptr->getParent()->getChrom() == ptr->getChrom()) && (ptr->getParent()->getPos() > ptr->getPos()))){
                //if ptr is the left child
                AVLDNA* parent = ptr->getParent();
                parent->setLeft(ptr->getRight());
                ptr->getRight()->setParent(parent);
                delete ptr;

                this->balanceTree(parent);
            }else{
                //if ptr is the right child
                AVLDNA* parent = ptr->getParent();
                parent->setRight(ptr->getRight());
                ptr->getRight()->setParent(parent);
                delete ptr;

                this->balanceTree(parent);
            }
        }else{//if the node is internal and has two subtrees
            AVLDNA* temp = this->findMax(ptr->getLeft());
            //temp is the greatest node in the left subtree of the node we want to delete
            ptr->changeData(temp->getChrom(), temp->getPos(), temp->getBase());
            if (temp->isLeaf()){
                if (temp == ptr->getLeft()){
                    //if there is only one node in ptr's left subtree
                    temp->getParent()->setLeft(NULL);
                    delete temp;

                    this->balanceTree(ptr);
                }else{
                    //if there is more than one node to the left of ptr and temp is a leaf temp has to be the right child
                    AVLDNA* parent = temp->getParent();
                    parent->setRight(NULL);
                    delete temp;

                    this->balanceTree(parent);
                }
            }else{
                //if temp is not a leaf it can only have a left subtree
                AVLDNA* parent = temp->getParent();
                parent->setRight(temp->getLeft());
                temp->getLeft()->setParent(parent);
                delete temp;

                this->balanceTree(parent);
            }
        }

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        cout << chromosome << " " << position << " " << altBase << " was deleted in " << duration.count() << "ms" << endl;
    }else{
        cout << chromosome << " " << position << " " << altBase << " could not be deleted because it could not be found" << endl;
    }
}

void AVLTree::list_subtree(AVLDNA* root, AVLDNA* max){
    //print data of all nodes using inorder traversal
    if(root==NULL) return;

    list_subtree(root->getLeft(), max);
    root->print_data();
    if(root!=max) cout << ",";
    list_subtree(root->getRight(), max);
}

void AVLTree::fillVector(AVLDNA* root, vector<AVLDNA> &v){
    //fill the vector in inorder so that it will be sorted automatically
    if (root == NULL) return;

    fillVector(root->getLeft(), v);
    v.push_back(*root);
    fillVector(root->getRight(), v);
}

void AVLTree::calculate_true_positive(vector<AVLDNA> &v1, vector<AVLDNA> &v2, int &i){
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

AVLTree::~AVLTree(){
    removeSubtree(this->root);
}