/* @Author
Student Name: Alper Tutum Student ID : 150210088>
Date: 06.06.2023 */

#pragma once
#include <string>

class ListDNA{
private:
    int chromosome;
    int position;
    std::string altBase;
    ListDNA* next;
public:
    ListDNA(int, int, std::string);
    int getChrom() const;
    int getPos() const;
    std::string getBase() const;
    ListDNA* getNext() const;
    void setNext(ListDNA*);
};