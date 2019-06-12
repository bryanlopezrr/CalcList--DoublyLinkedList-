#ifndef CALCLIST_H
#define CALCLIST_H
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include "CalcListInterface.hpp"

using std::stringstream;
using std::string;
using std::cout; 
using std::fixed;
using std::endl;

struct Node{
    /*     A node consists of: 
            |-----------------------------------------------------|
            |<-prev* | totalAtStep | operand | math_oper | *next->|
            |-----------------------------------------------------|
    */
    double totalAtStep = 0.0; 
    double num_operand = 0.0; 
    string math_operation = " "; 

    Node* previous = nullptr;
    Node* next = nullptr;
};

/*  Definition for the functions in this file are in the implementation file .cpp */
class CalcList: public CalcListInterface{

public:
    //Constructor and Destructor for the class objects
    CalcList();
    ~CalcList();
    
    //Functios overriden from the CalcInterface class
    double total() const; 
    void newOperation(const FUNCTIONS func, const double operand); 
    void removeLastOperation();
    string toString(unsigned short precision) const; 

    //Operations to add, remove and check if list is empty for the linked list
    void add(Node*); 
    void remove(Node*);
    bool empty() const; 
private:
    int num_of_operations; 
    //Sentinel nodes
    Node* header; 
    Node* trailer; 
    
};

#endif