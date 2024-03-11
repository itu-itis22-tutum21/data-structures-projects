/* @Author
Student Name: Alper Tutum
Student ID : 150210088 Date: 23/04/2023 */

#pragma once
#include <string>

using namespace std;
class University{
private:
    string faculty;
    string discount;
    string city;
    string uniName;
    string lang;
    string score_last;
    string range_last;
    string score_first;
    string range_first;
    string average_range;
    string average_score;
    University* up;
public:
    University(string, string, string, string, string, string, string, string, string, string, string);
    University* getUp() const;
    void set_up(University*);
    string get_uni() const;
    void printDetails();
};

class Department{
private:
    string department;
    int numOfUniversity;
    Department* next;
    Department* prev;
    University* up;
public:
    Department(string);
    Department* getNext() const;
    Department* getPrev() const;
    string get_Department() const;
    int get_numOfUni() const;
    University* getUp() const;
    void increase();
    void set_next(Department*);
    void set_up(University*);
    void set_prev(Department*);
};
