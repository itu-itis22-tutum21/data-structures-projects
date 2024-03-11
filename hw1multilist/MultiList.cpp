/* @Author
Student Name: Alper Tutum
Student ID : 150210088 Date: 23/04/2023 */

#include <iostream>
#include <string>
#include <chrono>
#include "MultiNode.h"
#include "MultiList.h"

using namespace std;
using namespace std::chrono;

MultiList::MultiList(){
    this->head = NULL;
    this->tail = NULL;
    this->totalDepartmentNumber = 0;
}

//create a new university node and insert it alphabetically
void MultiList::add_uni_node(Department *depPTR, string faculty, string uni, string discount, string city, string language, string score_last, string range_last, string score_first, string range_first, string range_average, string score_average){
    University* temp = depPTR->getUp();
    University* newUni = new University(faculty, uni, discount, city, language, score_last, range_last, score_first, range_first, range_average, score_average);

    if (uni.compare(temp->get_uni()) > 0){
        while (temp->getUp() != NULL){
            if (uni.compare(temp->getUp()->get_uni()) > 0){
                temp = temp->getUp();
            } else{
                break;
            }
        }
        newUni->set_up(temp->getUp());
        temp->set_up(newUni);
    } else{
        //new node will be the first
        depPTR->set_up(newUni);
        newUni->set_up(temp);
    }
    
    depPTR->increase();
}

//create a department node and the first university node attached to it
void MultiList::add_dep_uni_node(Department *ptr, string department, string faculty, string uni, string discount, string city, 
                                string language, string score_last, string range_last, string score_first, string range_first, 
                                string range_average, string score_average){
    
    //adding a new department
    Department* newDep = new Department(department);

    if (ptr != NULL){
        if (department.compare(ptr->get_Department()) > 0){
            newDep->set_next(ptr->getNext());
            newDep->set_prev(ptr);
            ptr->set_next(newDep);
        } else if (ptr != head){
            ptr->getPrev()->set_next(newDep);
            newDep->set_prev(ptr->getPrev());
            ptr->set_prev(newDep);
            newDep->set_next(ptr);
        } else{
            newDep->set_prev(ptr->getPrev());
            ptr->set_prev(newDep);
            newDep->set_next(ptr);
        }
        if (newDep->getNext() == NULL){
            this->tail = newDep;
        } else if (newDep->getPrev() == NULL){
            this->head = newDep;
        }
    } else{
        this->head = newDep;
        this->tail = newDep;
    }

    this->increase_depNum();

    //adding the first university
    University* newUni = new University(faculty, uni, discount, city, language, score_last, range_last, score_first, range_first, range_average, score_average);
    newDep->set_up(newUni);
    newDep->increase();
    //add_uni_node(newDep, faculty, uni, discount, city, language, score_last, range_last, score_first, range_first, range_average, score_average);
}

//this function is called in main
//compare departments
//if it already exists call add_uni_node
//if not call add_dep_uni_node
void MultiList::add_node(string department, string faculty, string uni, string discount, string city, string language, string score_last, string range_last, string score_first, string range_first, string range_average, string score_average){
    Department* ptr = this->head;
    bool exists = false;

    while (ptr != this->tail){
        if (department.compare(ptr->get_Department()) == 0){
            exists = true;
            break;
        } else if (department.compare(ptr->get_Department()) > 0){
            ptr = ptr->getNext();
        } else{
            break;
        }
    }

    if (ptr != NULL){
        if ((ptr == this->tail) && (department.compare(ptr->get_Department()) == 0)){
            exists = true;
        }
    }

    if (!exists){
        //call add_dep_uni_node
        this->add_dep_uni_node(ptr, department, faculty, uni, discount, city, language, score_last, range_last,
                                score_first, range_first, range_average, score_average);
    } else{
        //call add_uni_node
        this->add_uni_node(ptr, faculty, uni, discount, city, language, score_last, range_last,
                                score_first, range_first, range_average, score_average);
    }
}

//increment number of total departments
void MultiList::increase_depNum(){
    totalDepartmentNumber++;
}

int MultiList::get_depNum() const{
    return this->totalDepartmentNumber;
}

void MultiList::listDepartments(){
    //auto start = high_resolution_clock::now();
    Department* department = this->head;

    while(department != NULL){
        cout << "Department: " << department->get_Department() << endl;
        cout << "Number of Universities of Department:" << department->get_numOfUni() << endl;
        cout << "----------------" << endl; //seperator
        department = department->getNext();
    }
    //auto stop = high_resolution_clock::now();
    //auto duration = duration_cast<microseconds>(stop - start);
    //cout << "List departments: " << duration.count() << endl; (4473)
}

void MultiList::select_department(int totalDepNum){
    if (totalDepNum > 0){
        int depNum = 0;
        
        cout << "To review a department, enter a number between 1 and " << totalDepNum << ": ";
        cin >> depNum;

        while (depNum>totalDepNum || depNum < 1){
            cout << "Invalid number, please enter a number between 1 and " << totalDepNum << ": ";
            cin >> depNum;
        }

        //auto start = high_resolution_clock::now();

        Department* department = this->head;
        
        for (size_t i = 0; i < depNum - 1; i++){
            department = department->getNext();
        }
        
        cout << "Department: " << department->get_Department() << endl; //print the department

        if (department->get_numOfUni() > 0){
            University* university = department->getUp();

            //print all the universities of the department with all the details
            for (size_t i = 1; i < department->get_numOfUni()+1; i++){
                cout << i << ": " << university->get_uni() << endl;
                university->printDetails();
                university = university->getUp();
            }
        }

        //auto stop = high_resolution_clock::now();
        //auto duration = duration_cast<microseconds>(stop - start);
        //cout << "Time for listing universities: " << duration.count() << endl; (depends on how many universities there are)
    }
}

void MultiList::select_uni(int totalDepNum){
    if (totalDepNum > 0){
        int depNum;

        cout << endl << "To review a department, enter a number between 1 and " << totalDepNum << ": ";
        cin >> depNum;

        while (depNum>totalDepNum || depNum < 1){
            cout << endl << "Invalid department number, please enter a number between 1 and "  << totalDepNum << ": ";
            cin >> depNum;
        }
        
        Department* department = this->head;
        
        for (size_t i = 0; i < depNum-1; i++){
            department = department->getNext();
        }
        
        cout << "Department: " << department->get_Department() << endl; //print the department

        if (department->get_numOfUni() > 0){
            int uniNum;

            cout << endl << "To review a university of selected department, enter a number between 1 and " << department->get_numOfUni() << ": ";
            cin >> uniNum;

            while (uniNum>department->get_numOfUni()){
                cout << endl << "Invalid number, please enter a number between 1 and " << department->get_numOfUni() << ": ";
                cin >> uniNum;
            }

            //auto start = high_resolution_clock::now();
            //print university details
            University* university = department->getUp();

            for (size_t i = 0; i < uniNum-1; i++){
                university = university->getUp();
            }
            cout << university->get_uni() << endl;
            university->printDetails();

            //uto stop = high_resolution_clock::now();
            //auto duration = duration_cast<microseconds>(stop - start);
            //cout << "Time for selecting department and university: " << duration.count() << endl;
        }
    }
}

MultiList::~MultiList(){
    Department* depTemp = this->head;
    Department* depTemp2 = NULL;
    University* uniTemp = NULL;
    University* uniTemp2 = NULL;
    
    while (depTemp != NULL){
        depTemp2 = depTemp->getNext();
        uniTemp = depTemp->getUp();
        while (uniTemp != NULL){
            uniTemp2 = uniTemp->getUp();
            delete uniTemp;
            uniTemp = uniTemp2;
        }
        delete depTemp;
        depTemp = depTemp2;
    }
}