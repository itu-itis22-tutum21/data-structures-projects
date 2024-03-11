/* @Author
Student Name: Alper Tutum Student ID : 150210088>
Date: 06.06.2023 */

#pragma once
#include <string>

using namespace std;

class  BSDNA{
private:
    int chromosome;
    int position;
    string altBase;
    BSDNA* left;
    BSDNA* right;
    BSDNA* parent;
public:
    BSDNA(int, int, string);
    int getChrom() const;
    int getPos() const;
    string getBase() const;
    BSDNA* getLeft() const;
    BSDNA* getRight() const;
    BSDNA* getParent() const;
    int compare(BSDNA*) const;
    void setLeft(BSDNA*);
    void setRight(BSDNA*);
    void setParent(BSDNA*);
    void changeData(int, int, string);
    void printData();
    bool isLeaf();
};