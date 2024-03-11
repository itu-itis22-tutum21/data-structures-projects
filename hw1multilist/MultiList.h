/* @Author
Student Name: Alper Tutum
Student ID : 150210088 Date: 23/04/2023 */

#pragma once

#include "MultiNode.h"
#include <string>

class MultiList{
private:
    Department* head;
    Department* tail;
    int totalDepartmentNumber;
public:
    MultiList();
    ~MultiList();
    void add_uni_node(Department*,string, string, string, string, string, string, string, string, string, string, string);
    void add_dep_uni_node(Department*,string,string, string, string, string, string, string, string, string, string, string, string);
    void add_node(string, string, string, string, string, string, string, string, string, string, string, string);
    void increase_depNum();
    int get_depNum() const;
    void select_department(int);
    void select_uni(int);
    void listDepartments();
};