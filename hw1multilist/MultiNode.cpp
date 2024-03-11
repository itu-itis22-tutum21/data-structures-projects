/* @Author
Student Name: Alper Tutum
Student ID : 150210088 Date: 23/04/2023 */

#include <iostream>
#include <string>
#include "MultiNode.h"

using namespace std;
University::University(string faculty, string uni, string discount, string city, string language, string score_last,
                        string range_last, string score_first, string range_first, string range_average, string score_average){
    this->faculty = faculty;
    this->discount = discount;
    this->city=city;
    this->uniName = uni;
    this->lang = language;
    this->score_last = score_last;
    this->range_last = range_last;
    this->score_first = score_first;
    this->range_first = range_first;
    this->average_range = range_average;
    this->average_score = score_average;
    this->up = NULL;
}

string University::get_uni() const{
    return this->uniName;
}

void University::set_up(University* next){
    this->up = next;
}

University* University::getUp() const{
    return this->up;
}

void University::printDetails(){
    cout << "Faculty: " << this->faculty << endl;
    cout << "Discount: " << this->discount << endl;
    cout << "City: " << this->city << endl;
    cout << "Language: " << this->lang << endl;
    cout << "Score Last: " << this->score_last << endl;
    cout << "Range Last: " << this->range_last << endl;
    cout << "Score First: " << this->score_first << endl;
    cout << "Range First: " << this->range_first << endl;
    cout << "Score Average: " << this->average_score << endl;
    cout << "Range Average: " << this->average_range << endl;
    cout << "----------------" << endl;
}

Department::Department(string dep){
    this->department = dep;
    this->numOfUniversity = 0;
    this->next = NULL;
    this->prev = NULL;
    this->up = NULL;
}

void Department::set_up(University* under){
    this->up = under;
}

string Department::get_Department() const{
    return this->department;
}

int Department::get_numOfUni() const{
    return this->numOfUniversity;
}

University* Department::getUp() const{
    return this->up;
}

Department* Department::getNext() const{
    return this->next;
}

Department* Department::getPrev() const{
    return this->prev;
}

void Department::set_next(Department *nxt){
    this->next = nxt;
}

void Department::increase(){ //increase the number of university
    this->numOfUniversity++;
}

void Department::set_prev(Department *previous){
    this->prev = previous;
}
