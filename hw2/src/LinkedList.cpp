/* @Author
Student Name: Alper Tutum Student ID : 150210088>
Date: 06.06.2023 */

#include <iostream>
#include <chrono>
#include "../include/LinkedList.h"
#include "../include/ListNode.h"

using namespace std;
using namespace std::chrono;

LinkedList::LinkedList(){
    this->head = NULL;
}

ListDNA* LinkedList::getHead(){
    return this->head;
}

void LinkedList::searchDNANode(int chrom, int pos, string base){
    auto start = high_resolution_clock::now();
    ListDNA* ptr = this->head;

    if (ptr!=NULL){
        while (!((ptr->getChrom()==chrom) && (ptr->getPos()==pos) && (ptr->getBase()==base))){
            if (ptr->getNext()==NULL){
                cout << chrom << " " << pos << " " << base << " could not be found" << endl;
                return;
            }
            ptr = ptr->getNext();
        } 
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        cout << ptr->getChrom() << " " << ptr->getPos() << " " << ptr->getBase() << " was found in " << duration.count() << "ms" << endl;
    }else{
        cout << chrom << " " << pos << " " << base << " could not be found" << endl;
        return;
    }
}

bool LinkedList::addDNANode(int chromosome, int position, string altBase){
    ListDNA* ptr = this->head;
    ListDNA* newNode = new ListDNA(chromosome, position, altBase);

    if(ptr==NULL){
        //adding to an empty list
        this->head = newNode;
        return true;
    }else{
        while (ptr->getNext() != NULL){
            if (ptr->getChrom()==chromosome && ptr->getPos()==position && ptr->getBase()==altBase){
                //cout << "DNA node already exists" << endl;
                delete newNode;
                return false;
            }
            ptr = ptr->getNext();
        }
        ptr->setNext(newNode);
        return true;
    }
}

bool LinkedList::removeDNANode(int chromosome, int position, string altBase){
    ListDNA* ptr = this->head;
    ListDNA* temp = NULL;

    if (ptr!=NULL){
        if (ptr->getNext()==NULL){
            //if there is only one node in the list
            if (ptr->getChrom()==chromosome && ptr->getPos()==position && ptr->getBase()==altBase){
                this->head = NULL;
                delete ptr;
                return true;
            }else{
                cout << chromosome << " " << position << " " << altBase << " could not be deleted because it could not be found" << endl;
                return false;
            }
        }else if (ptr->getChrom()==chromosome && ptr->getPos()==position && ptr->getBase()==altBase){
            this->head = ptr->getNext();
            delete ptr;
            return true;
        }else{
            while (!((ptr->getNext()->getChrom()==chromosome) && (ptr->getNext()->getPos()==position) && (ptr->getNext()->getBase()==altBase))){
                if (ptr->getNext()->getNext()==NULL){
                        cout << chromosome << " " << position << " " << altBase << " could not be deleted because it could not be found" << endl;
                        return false;
                    }
                    ptr = ptr->getNext();
            }

            temp = ptr->getNext();
            ptr->setNext(ptr->getNext()->getNext());
            ptr = temp;
            delete ptr;
            return true;
        }
    }else{
        cout << chromosome << " " << position << " " << altBase << " could not be deleted because it could not be found" << endl;
        return false;
    }
}

void LinkedList::print_list(){
    ListDNA* ptr = this->head;

    if (ptr!=NULL){
        cout << ptr->getChrom() << " " << ptr->getPos() << " " << ptr->getBase();

        ptr = ptr->getNext();
        while (ptr!=NULL){
            cout << "," << ptr->getChrom() << " " << ptr->getPos() << " " << ptr->getBase();
            ptr = ptr->getNext();
        }

        cout << endl;
    }
}

void LinkedList::calculateTruePositive(LinkedList* list){
    auto start = high_resolution_clock::now();
    ListDNA* ptr = this->head;
    int i = 0;
    ListDNA* header = NULL;

    //code here
    while (ptr!=NULL){
        header = list->getHead();
        while (header!=NULL){
            if ((ptr->getChrom()==header->getChrom()) && (ptr->getPos()==header->getPos()) && (ptr->getBase()==header->getBase())){
                i++;
                break;
            }
            header = header->getNext();
        }
        ptr = ptr->getNext();
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "True positive variant count is " << i << ". It took " << duration.count() << " ms to calculate." << endl;
}

LinkedList::~LinkedList(){
    ListDNA* temp1 = this->head;
    ListDNA* temp2 = NULL;

    while (temp1!=NULL){
        temp2 = temp1->getNext();
        delete temp1;
        temp1 = temp2;
    }

}