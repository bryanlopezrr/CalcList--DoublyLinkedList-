/***************************************************************

Project1: This program is calculator that stores the different
          operations and numbers into a Doubly Linked List
        
Author: Bryan Lopez 
Class: Data Structures; Dr. Oropallo
    
***************************************************************/

#include "CalcList.hpp"

CalcList::CalcList(){
    /* This constructor will be initializing and setting up the sentinel values
       that will help me know where the beginning and end of the list are.
    */

    //    |---| ---> |---|
    //    | H |      | T |
    //    |---| <--- |---|
    header = new Node; 
    trailer = new Node;

    header->next = trailer; 
    trailer->previous = header;
    //initiliaze the total number of operations executed in the program
    num_of_operations = 0; 
}

CalcList::~CalcList(){
    /* This destructor checks if the list is empty or not. In the latter it will remove the
       header->next node and will continue to do so unitl the list is empty
    */
    while(!empty()){
        remove(header->next);
    }
    delete header;
    delete trailer;
}

double CalcList::total() const{
    /* This function returns the trailer previous pointer's value resulting in the
      total at the exact moment during the list
      */
    return trailer->previous->totalAtStep;
}

void CalcList::newOperation(const FUNCTIONS func, const double operand){
    /* This function creates a new operation and stores the appropriate members in the 
       data type struct Node.

       IE:     A node consists of: 
            |-----------------------------------------------------|
            |<-prev* | totalAtStep | operand | math_oper | *next->|
            |-----------------------------------------------------|
        Each case DIVISION,MULTIPLICATION, SUBTRACTION, ADDITION stores the appropriate types
        to be used later
    */
  add(trailer); //pushing the node to the back of the list     
    switch(func){
        case DIVISION:
            if(operand == 0) {
                removeLastOperation(); 
                throw("ERROR: You can't divide by zero.");
            }
            else{ 
                trailer->previous->totalAtStep /= operand;
                trailer->previous->num_operand = operand;
                trailer->previous->math_operation = "/";
                break;
            }
        case MULTIPLICATION:
            trailer->previous->totalAtStep *= operand;
            trailer->previous->num_operand = operand;
            trailer->previous->math_operation = "*";
            break;
        case SUBTRACTION:
            trailer->previous->totalAtStep -= operand;
            trailer->previous->num_operand = operand;
            trailer->previous->math_operation = "-";
            break;
        case ADDITION:
            trailer->previous->totalAtStep += operand;
            trailer->previous->num_operand = operand;
            trailer->previous->math_operation = "+";
            break;
        default:
            cout << "ERROR: Not a valid operation; Valid operations include '+','-','*','/'.\n";
            break;
    }
}

void CalcList::removeLastOperation(){
    /* This function will call our remove() function and pass it the trailer node's previuous
       pointer which is the last operation added to the list. 
     */
    remove(trailer->previous);
}


string CalcList::toString(unsigned short precision) const{
    /*  This function will take a precision parameter to set the significant digits 
        of the operands and totals in the string version of the operations

        The function uses a temporary pointer to point to the back of the list and move from
        there to print out the list in the appropriate order (reverse)
     */
    stringstream ss;
    string string_text = "";
    int step = num_of_operations;
    Node* temp = trailer;

    ss.precision(precision);
    while(temp->previous != header){
        //(step): 
        ss << step << ": ";
        //(totalAtStep)(math_operation)
        ss << fixed << temp->previous->previous->totalAtStep;
        ss << temp->previous->math_operation;
        //(num_operand)=
        ss << temp->previous->num_operand << "=";
        //(newTotal)
        ss << temp->previous->totalAtStep;
        ss << endl;

        temp = temp->previous; //move pointer to traverse the list from the back 
        step--;
    }
    //ss format -> (step): (totalAtStep)(math_operation)(num_operand)=(newTotal)
    string_text = ss.str();
    return string_text; //return the final string ^^^
}

void CalcList::add(Node* N) {
    /* This function will add a node into the list and set the pointers appropriately to 
       traverse through the list afterwards
    */
    Node* x = new Node; 
    x->next = N;
    x->totalAtStep = N->previous->totalAtStep;
    x->previous = N->previous; 
    N->previous->next = x;
    N->previous = x;

    num_of_operations++;  //increase number of operations
}

void CalcList::remove(Node* N) { 
    /* This function will remove the node passed to it and will move the pointers to make sure
       the links are set up properly
    */
    if(!empty()) { 
        Node* x = N->previous; 
        Node* y = N->next; 
        x->next = y; 
        y->previous = x;
        delete N;
        
        num_of_operations--; //decrease number of operations 
        }
    else{
       throw ("ERROR: The list is empty at the moment\n");
    }
}

bool CalcList::empty() const{
    //             |---| ---> |---|
    //             | H |      | T |
    //             |---| <--- |---|

    // This function checks if ^ indeed is empty or not
    return header->next == trailer;
}