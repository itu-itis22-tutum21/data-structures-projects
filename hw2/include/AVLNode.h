/* @Author
Student Name: Alper Tutum Student ID : 150210088>
Date: 06.06.2023 */

#pragma once

class  AVLDNA{
private:
    int chromosome;
    int position;
    std::string altBase;
    AVLDNA* right;
    AVLDNA* left;
    AVLDNA* parent;
    int height;
public:
    AVLDNA(int, int, std::string);
    int getChrom() const;
    int getPos() const;
    std::string getBase() const;
    int getHeight() const;
    AVLDNA* getLeft() const;
    AVLDNA* getRight() const;
    AVLDNA* getParent() const;
    int compare(AVLDNA*) const;
    void setHeight(int);
    int find_height(AVLDNA*);
    int getBalanceFactor();
    void setLeft(AVLDNA*);
    void setRight(AVLDNA*);
    void setParent(AVLDNA*);
    void changeData(int, int, std::string);
    void print_data();
    bool isLeaf();
};