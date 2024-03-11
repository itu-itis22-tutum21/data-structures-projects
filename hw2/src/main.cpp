/* @Author
Student Name: Alper Tutum Student ID : 150210088>
Date: 06.06.2023 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include "../include/BSTree.h"
#include "../include/AVLTree.h"
#include "../include/LinkedList.h"

using namespace std;
using namespace std::chrono;

void print_ds_menu();
void print_operation_menu();
bool perform_operation(char, BSTree*, BSTree*);
bool perform_operation(char, AVLTree*, AVLTree*);
bool perform_operation(char, LinkedList*, LinkedList*);

int main(){

    //string file_gt = "../gt.txt";
    //string file_predict = "../predict.txt";
    bool end = false;
    char choice_ds, choice_op;
    
    print_ds_menu();
    cin >> choice_ds;

    if (choice_ds == '1') //Binary Search Tree Selection
    {
        BSTree* predictionBST = new BSTree();
        BSTree* groundTruthBST = new BSTree();

        while (!end){
            print_operation_menu();
            cin >> choice_op;
            end = perform_operation(choice_op, predictionBST, groundTruthBST);
        }

        predictionBST->~BSTree();
        groundTruthBST->~BSTree();
    }

    else if (choice_ds == '2') //AVL Tree Selection
    {
        AVLTree* predictionAVL = new AVLTree();
        AVLTree* groundTruthAVL = new AVLTree();

        while (!end){
            print_operation_menu();
            cin >> choice_op;
            end = perform_operation(choice_op, predictionAVL, groundTruthAVL);
        }

        predictionAVL->~AVLTree();
        groundTruthAVL->~AVLTree();
    }

    else if (choice_ds == '3') //Linked List Selection
    {
        LinkedList* predictionList = new LinkedList();
        LinkedList* groundTruthList = new LinkedList();

        while (!end){
            print_operation_menu();
            cin >> choice_op;
            end = perform_operation(choice_op, predictionList, groundTruthList);
        }

        predictionList->~LinkedList();
        groundTruthList->~LinkedList();
    }
    
    else{
        cout << "Error: You have entered an invalid choice" << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void print_ds_menu(){
    cout << "Choose a data structure" << endl;
    cout << "1: Binary Search Tree" << endl;
    cout << "2: AVL Tree"<< endl;
    cout << "3: Unsorted Singly Linked List"<< endl;
    cout << "Enter a choice {1,2,3}:";
}

void print_operation_menu(){
    cout << "Choose an operation" << endl;
    cout << "1: Create ground truth data structure from file" << endl;
    cout << "2: Create prediction data structure from file"<< endl;
    cout << "3: Add a variant prediction"<< endl;
    cout << "4: Delete a variant prediction"<< endl;
    cout << "5: List predictions"<< endl;
    cout << "6: Search a prediction variant from predictions"<< endl;
    cout << "7: Calculate true positive variant count"<< endl;
    cout << "0: Exit" << endl;
    cout << "Enter a choice {1,2,3,4,5,6,7,0}:";
}

//Function overloading is utilized because pointers to different classes are needed as parameters to the same function 

//perform operation for BSTree
bool perform_operation(char choice, BSTree* predictTree, BSTree* gtTree){
    bool terminate = false;

    if (choice == '1'){
        //Create ground truth structure
        auto start = high_resolution_clock::now();

        ifstream inFile;
        inFile.open("../gt.txt");
        if(!inFile.is_open()){
            cout << "ERROR: The File Cannot be Opened" << endl;
            return EXIT_FAILURE;
        }

        int chromosome;
        int position;
        string altBase;

        string row;
        string delimiter = "	";
        string afterDelimiter;
        bool header = true;

        while (!inFile.eof()){
            int i = 0;
            getline(inFile, row, '\n');

            size_t pos = 0;
            string token;

            while ((pos = row.find(delimiter)) != string::npos){
                token = row.substr(0, pos);
                afterDelimiter = row.substr(row.find("	")+1);
                if (token != " "){
                    if (i == 0 && header==false) chromosome = stoi(token);
                    else if (i == 1 && header==false){position = stoi(token);
                    altBase = afterDelimiter;
                    }
                }
                row.erase(0, pos + delimiter.length());
                i++;
            }
            if (header == false){
                //add nodes for ground truth BSTree
                gtTree->addDNANode(chromosome, position, altBase);
            }
            header = false;
        }

        inFile.close();

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        cout << "Ground truth data structure was created from file in " << duration.count() << " ms" << endl;       
    } else if (choice == '2'){
        //Create prediction structure
        auto start = high_resolution_clock::now();

        ifstream inFile;
        inFile.open("../predict.txt");
        if(!inFile.is_open()){
            cout << "ERROR: The File Cannot be Opened" << endl;
            return EXIT_FAILURE;
        }

        int chromosome;
        int position;
        string altBase;

        string row;
        string delimiter = "	";
        string afterDelimiter;
        bool header = true;

        while (!inFile.eof()){
            int i = 0;
            getline(inFile, row, '\n');

            size_t pos = 0;
            string token;

            while ((pos = row.find(delimiter)) != string::npos){
                token = row.substr(0, pos);
                afterDelimiter = row.substr(row.find("	")+1);
                if (token != " "){
                    if (i == 0 && header==false) chromosome = stoi(token);
                    else if (i == 1 && header==false) {position = stoi(token);
                        altBase = afterDelimiter;
                    }
                }
                row.erase(0, pos + delimiter.length());
                i++;
            }
            if (header == false){
                //add nodes for prediction BSTree
                predictTree->addDNANode(chromosome, position, altBase);
            }
            header = false;
        }

        inFile.close();

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        cout << "Prediction data structure was created from file in " << duration.count() << " ms" << endl;
    } else if (choice == '3'){
        //Add variant prediction
        int chrom, pos;
        string altBase;
        cout << "Enter the CHROM POS and ALT_BASE information with a space in between: ";
        cin >> chrom >> pos >> altBase;
        auto start = high_resolution_clock::now();

        bool added = predictTree->addDNANode(chrom, pos, altBase);

        if (added){
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start);
            cout << chrom << " " << pos << " " << altBase << " was added in " << duration.count() << "ms" << endl;
        }
    } else if (choice == '4'){
        //Delete variant prediction
        int chrom, pos;
        string altBase;
        cout << "Enter the CHROM POS and ALT_BASE information with a space in between: ";
        cin >> chrom >> pos >> altBase;

        predictTree->removeDNANode(chrom, pos, altBase);
    } else if (choice == '5'){
        //List predictions
        BSDNA* max = predictTree->findMax(predictTree->getRoot());
        predictTree->listSubtree(predictTree->getRoot(), max);
        cout << endl;
    } else if (choice == '6'){
        //Search variant from predictions
        int chrom, pos;
        string altBase;
        cout << "Enter the CHROM POS and ALT_BASE information with a space in between: ";
        cin >> chrom >> pos >> altBase;

        predictTree->searchDNANode(chrom, pos, altBase);
    } else if (choice == '7'){
        //Count true positive variants
        auto start = high_resolution_clock::now();
        vector<BSDNA> vec1;
        vector<BSDNA> vec2;
        int count = 0;

        //first fill the vector with the data of both trees
        predictTree->fillVector(predictTree->getRoot(), vec1);
        gtTree->fillVector(gtTree->getRoot(), vec2);

        //then count how many common nodes there are
        predictTree->calculateTruePositive(vec1, vec2, count);

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        cout << "True positive variant count is " << count << ". It took " << duration.count() << " ms to calculate." << endl;
    } else if(choice == '0'){
        //Exit
        terminate = true;
    } else{
        cout << "Invalid entry, please enter a number between 0 and 7" << endl;
    }
    return terminate;
}

//perform operation for AVLTree
bool perform_operation(char choice, AVLTree* predictAVL, AVLTree* gtAVL){
    bool terminate = false;
    
    if (choice == '1'){
        //Create ground truth structure
        auto start = high_resolution_clock::now();

        ifstream inFile;
        inFile.open("../gt.txt");
        if(!inFile.is_open()){
            cout << "ERROR: The File Cannot be Opened" << endl;
            return EXIT_FAILURE;
        }

        int chromosome;
        int position;
        string altBase;

        string row;
        string delimiter = "	";
        string afterDelimiter;
        bool header = true;

        while (!inFile.eof()){
            int i = 0;
            getline(inFile, row, '\n');

            size_t pos = 0;
            string token;

            while ((pos = row.find(delimiter)) != string::npos){
                token = row.substr(0, pos);
                afterDelimiter = row.substr(row.find("	")+1);
                if (token != " "){
                    if (i == 0 && header==false) chromosome = stoi(token);
                    else if (i == 1 && header==false){position = stoi(token);
                    altBase = afterDelimiter;
                    }
                }
                row.erase(0, pos + delimiter.length());
                i++;
            }
            if (header == false){
                //add nodes for ground truth AVLTree
                gtAVL->add_node(chromosome, position, altBase);
            }
            header = false;
        }

        inFile.close();

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        cout << "Ground truth data structure was created from file in " << duration.count() << " ms" << endl;
    } else if (choice == '2'){
        //Create prediction structure
        auto start = high_resolution_clock::now();

        ifstream inFile;
        inFile.open("../predict.txt");
        if(!inFile.is_open()){
            cout << "ERROR: The File Cannot be Opened" << endl;
            return EXIT_FAILURE;
        }

        int chromosome;
        int position;
        string altBase;

        string row;
        string delimiter = "	";
        string afterDelimiter;
        bool header = true;

        while (!inFile.eof()){
            int i = 0;
            getline(inFile, row, '\n');

            size_t pos = 0;
            string token;

            while ((pos = row.find(delimiter)) != string::npos){
                token = row.substr(0, pos);
                afterDelimiter = row.substr(row.find("	")+1);
                if (token != " "){
                    if (i == 0 && header==false) chromosome = stoi(token);
                    else if (i == 1 && header==false){position = stoi(token);
                        altBase = afterDelimiter;
                    }
                }
                row.erase(0, pos + delimiter.length());
                i++;
            }
            if (header == false){
                //add nodes for prediction AVLTree
                predictAVL->add_node(chromosome, position, altBase);
            }
            header = false;
        }

        inFile.close();

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        cout << "Prediction data structure was created from file in " << duration.count() << " ms" << endl;
    } else if (choice == '3'){
        //Add variant prediction
        int chrom, pos;
        string altBase;
        cout << "Enter the CHROM POS and ALT_BASE information with a space in between: ";
        cin >> chrom >> pos >> altBase;
        auto start = high_resolution_clock::now();

        bool added = predictAVL->add_node(chrom, pos, altBase);

        if (added){
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start);
            cout << chrom << " " << pos << " " << altBase << " was added in " << duration.count() << "ms" << endl;
        }
    } else if (choice == '4'){
        //Delete variant prediction
        int chrom, pos;
        string altBase;
        cout << "Enter the CHROM POS and ALT_BASE information with a space in between: ";
        cin >> chrom >> pos >> altBase;

        predictAVL->remove_node(chrom, pos, altBase);
    } else if (choice == '5'){
        //List predictions
        AVLDNA* max = predictAVL->findMax(predictAVL->getRoot());
        predictAVL->list_subtree(predictAVL->getRoot(), max);
        cout << endl;
    } else if (choice == '6'){
        //Search variant from predictions
        int chrom, pos;
        string altBase;
        cout << "Enter the CHROM POS and ALT_BASE information with a space in between: ";
        cin >> chrom >> pos >> altBase;

        predictAVL->search_node(chrom, pos, altBase);
    } else if (choice == '7'){
        //Count true positive variants
        auto start = high_resolution_clock::now();
        vector<AVLDNA> vec1;
        vector<AVLDNA> vec2;
        int count = 0;

        predictAVL->fillVector(predictAVL->getRoot(), vec1);
        gtAVL->fillVector(gtAVL->getRoot(), vec2);

        predictAVL->calculate_true_positive(vec1, vec2, count);

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        cout << "True positive variant count is " << count << ". It took " << duration.count() << " ms to calculate." << endl;
    } else if(choice == '0'){
        //Exit
        terminate = true;
    } else{
        cout << "Invalid entry, please enter a number between 0 and 7" << endl;
    }
    return terminate;
}

//perform operation for Singly Linked List
bool perform_operation(char choice, LinkedList* predictList, LinkedList* gtList){
    bool terminate = false;

    if (choice == '1'){
        //Create ground truth structure
        auto start = high_resolution_clock::now();

        ifstream inFile;
        inFile.open("../gt.txt");
        if(!inFile.is_open()){
            cout << "ERROR: The File Cannot be Opened" << endl;
            return EXIT_FAILURE;
        }

        int chromosome;
        int position;
        string altBase;

        string row;
        string delimiter = "	";
        string afterDelimiter;
        bool header = true;

        while (!inFile.eof()){
            int i = 0;
            getline(inFile, row, '\n');

            size_t pos = 0;
            string token;

            while ((pos = row.find(delimiter)) != string::npos){
                token = row.substr(0, pos);
                afterDelimiter = row.substr(row.find("	")+1);
                if (token != " "){
                    if (i == 0 && header==false) chromosome = stoi(token);
                    else if (i == 1 && header==false){position = stoi(token);
                    altBase = afterDelimiter;
                    }
                }
                row.erase(0, pos + delimiter.length());
                i++;
            }
            if (header == false){
                //add nodes for ground truth Linked List
                gtList->addDNANode(chromosome, position, altBase);
            }
            header = false;
        }

        inFile.close();

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        cout << "Ground truth data structure was created from file in " << duration.count() << " ms" << endl;
    } else if (choice == '2'){
        //Create prediction structure
        auto start = high_resolution_clock::now();

        ifstream inFile;
        inFile.open("../predict.txt");
        if(!inFile.is_open()){
            cout << "ERROR: The File Cannot be Opened" << endl;
            return EXIT_FAILURE;
        }

        int chromosome;
        int position;
        string altBase;

        string row;
        string delimiter = "	";
        string afterDelimiter;
        bool header = true;

        while (!inFile.eof()){
            int i = 0;
            getline(inFile, row, '\n');

            size_t pos = 0;
            string token;

            while ((pos = row.find(delimiter)) != string::npos){
                token = row.substr(0, pos);
                afterDelimiter = row.substr(row.find("	")+1);
                if (token != " "){
                    if (i == 0 && header==false) chromosome = stoi(token);
                    else if (i == 1 && header==false){position = stoi(token);
                        altBase = afterDelimiter;
                    }
                }
                row.erase(0, pos + delimiter.length());
                i++;
            }
            if (header == false){
                //add nodes for prediction Linked List
                predictList->addDNANode(chromosome, position, altBase);
            }
            header = false;
        }

        inFile.close();

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        cout << "Prediction data structure was created from file in " << duration.count() << " ms" << endl;
    } else if (choice == '3'){
        //Add variant prediction
        int chrom, pos;
        string altBase;
        cout << "Enter the CHROM POS and ALT_BASE information with a space in between: ";
        cin >> chrom >> pos >> altBase;
        auto start = high_resolution_clock::now();

        bool added = predictList->addDNANode(chrom, pos, altBase);

        if (added){
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start);
            cout << chrom << " " << pos << " " << altBase << " was added in " << duration.count() << "ms" << endl;
        }
    } else if (choice == '4'){
        //Delete variant prediction
        int chrom, pos;
        string altBase;
        cout << "Enter the CHROM POS and ALT_BASE information with a space in between: ";
        cin >> chrom >> pos >> altBase;
        auto start = high_resolution_clock::now();

        bool deleted = predictList->removeDNANode(chrom, pos, altBase);

        if (deleted){
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start);
            cout << chrom << " " << pos << " " << altBase << " was deleted in " << duration.count() << "ms" << endl;
        }
    } else if (choice == '5'){
        //List predictions
        predictList->print_list();
    } else if (choice == '6'){
        //Search variant from predictions
        int chrom, pos;
        string altBase;
        cout << "Enter the CHROM POS and ALT_BASE information with a space in between: ";
        cin >> chrom >> pos >> altBase;

        predictList->searchDNANode(chrom, pos, altBase);
    } else if (choice == '7'){
        //Count true positive variants
        predictList->calculateTruePositive(gtList);
    } else if(choice == '0'){
        //Exit
        terminate = true;
    } else{
        cout << "Invalid entry, please enter a number between 0 and 7" << endl;
    }
    return terminate;
}