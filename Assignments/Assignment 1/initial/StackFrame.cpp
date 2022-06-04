#include "StackFrame.h"
#include <iostream>
#include <fstream>
#include "errors.h"
#include "constants.h"
using namespace std;

// So tu trong chuoi lenh
int numberOfWordsInString (string string) {
    int count = 0;
    int n = string.length();
    for (int i = 0; i < n; i++)
    {
        if (string [i] == ' ') {
            count++;
        }
    }
    return count + 1;
}

// Tach chuoi lenh tu khoang trang 
string *splitString (string inputString) {
    int count = numberOfWordsInString (inputString);
    int i = 0;
    string *temp = new string [count];
    int start = 0;
    int end = inputString.find (" ");
    while (end != -1) {
        temp [i] = inputString.substr (start, end - start);
        start = end + 1;
        end = (int) inputString.find (" ", start);
        i++;
    }
    temp [i] = inputString.substr (start, end - start);
    return temp;
}

StackFrame::StackFrame() : opStackMaxSize (OPERAND_STACK_MAX_SIZE), localVarArrSize (LOCAL_VARIABLE_ARRAY_SIZE) {}

void StackFrame::run (string filename) {
    // Phan khai bao 
    Stack Stack;
    Array Array;
    float topDataOfStack = 0; // Du lieu tren cung cua ngan xep
    float belowTopDataOfStack = 0; // Du lieu ngay ben duoi du lieu tren cung cua ngan xep
    int lineNum = 0; // So thu tu dong lenh
    string lineTracking; // Duyet tung dong doc tu file bao gom cac chuoi lenh
    string *wordsTracking; // Xet cac chuoi lenh tach ra tu khoang trang 
    fstream Instructions; // Doc file bao gom cac chuoi lenh
    int numOfWordsInst = 0;// Chuoi lenh co bao nhieu cum
    Instructions.open (filename, ios::in);
    while (!Instructions.eof()) {
        getline (Instructions, lineTracking);
        numOfWordsInst = numberOfWordsInString (lineTracking);
        wordsTracking = splitString (lineTracking);
        lineNum++;
        if (numOfWordsInst == 1) { // Cac chuoi lenh chi co 1 cum lenh
            if (wordsTracking [0] == "iadd") { // Lenh 1
                if (Stack.maxIndex() > 2) {
                    if (max ((int) Stack.topDataType(), (int) Stack.belowTopDataType()) == 0) {
                        topDataOfStack = Stack.topDataValue(); Stack.pop();
                        belowTopDataOfStack = Stack.topDataValue(); Stack.pop();
                        Stack.push (int (topDataOfStack + belowTopDataOfStack) ,0);
                    }
                    else {
                        delete [] wordsTracking;
                        Instructions.close();
                        throw TypeMisMatch (lineNum);
                    }
                }
                else {
                    delete[] wordsTracking;
                    Instructions.close();
                    throw StackEmpty (lineNum);
                }
            }
            else if(wordsTracking [0] == "fadd") { // Lenh 2
                if (Stack.maxIndex() > 2) {
                    topDataOfStack = Stack.topDataValue();
                    Stack.pop();
                    belowTopDataOfStack = Stack.topDataValue();
                    Stack.pop();
                    Stack.push(float (topDataOfStack + belowTopDataOfStack), 1);
                }
                else {
                    delete [] wordsTracking;
                    Instructions.close();
                    throw StackEmpty (lineNum);
                }
            }
            else if(wordsTracking[0] == "isub") { // Lenh 3
                if(Stack.maxIndex() > 2) {
                    if(max((int)Stack.topDataType(),(int)Stack.belowTopDataType()) == 0) {
                        topDataOfStack = Stack.topDataValue();Stack.pop();
                        belowTopDataOfStack = Stack.topDataValue();Stack.pop();
                        Stack.push(int(belowTopDataOfStack - topDataOfStack),0);
                    }
                    else {
                        delete[] wordsTracking;
                        Instructions.close();
                        throw TypeMisMatch(lineNum);
                    }
                }
                else {
                    delete[] wordsTracking;
                    Instructions.close();
                    throw StackEmpty(lineNum);
                }
            }
            else if(wordsTracking[0] == "fsub") { // Lenh 4
                if(Stack.maxIndex() > 2) {
                    topDataOfStack = Stack.topDataValue();Stack.pop();
                    belowTopDataOfStack = Stack.topDataValue();Stack.pop();
                    Stack.push(float(belowTopDataOfStack - topDataOfStack),1);
                }
                else {
                    delete[] wordsTracking;
                    Instructions.close();
                    throw StackEmpty(lineNum);
                }
            }
            else if(wordsTracking[0] == "imul") { // Lenh 5
                if(Stack.maxIndex() > 2) {
                    if(max((int)Stack.topDataType(),(int)Stack.belowTopDataType()) == 0) {
                        topDataOfStack = Stack.topDataValue();Stack.pop();
                        belowTopDataOfStack = Stack.topDataValue();Stack.pop();
                        Stack.push(int(topDataOfStack * belowTopDataOfStack),0);
                    }
                    else {
                        delete[] wordsTracking;
                        Instructions.close();
                        throw TypeMisMatch(lineNum);
                    }
                }
                else {
                    delete[] wordsTracking;
                    Instructions.close();
                    throw StackEmpty(lineNum);
                }
            }
            else if(wordsTracking[0] == "fmul") { // Lenh 6
                if(Stack.maxIndex() > 2) {
                    topDataOfStack = Stack.topDataValue();Stack.pop();
                    belowTopDataOfStack = Stack.topDataValue();Stack.pop();
                    Stack.push(float(topDataOfStack * belowTopDataOfStack),1);
                }
                else {
                    delete[] wordsTracking;
                    Instructions.close();
                    throw StackEmpty(lineNum);
                }
            }
            else if(wordsTracking[0] == "idiv") { // Lenh 7
                if(Stack.maxIndex() > 2) {
                    if(max((int)Stack.topDataType(),(int)Stack.belowTopDataType()) == 0) {
                        topDataOfStack = Stack.topDataValue();Stack.pop();
                        belowTopDataOfStack = Stack.topDataValue();Stack.pop();
                            if(topDataOfStack == 0) {
                                delete[] wordsTracking;
                                Instructions.close();
                                throw DivideByZero(lineNum);
                            }
                        Stack.push(int(belowTopDataOfStack / topDataOfStack),0);
                    }
                    else {
                        delete[] wordsTracking;
                        Instructions.close();
                        throw TypeMisMatch(lineNum);
                    }
                }
                else {
                    delete[] wordsTracking;
                    Instructions.close();
                    throw StackEmpty(lineNum);
                }
            }
            else if(wordsTracking[0] == "fdiv") { // Lenh 8
                if(Stack.maxIndex() > 2) {
                    topDataOfStack = Stack.topDataValue();Stack.pop();
                    belowTopDataOfStack = Stack.topDataValue();Stack.pop();
                    if(topDataOfStack == 0) {
                        delete[] wordsTracking;
                        Instructions.close();
                        throw DivideByZero(lineNum);
                    }
                    Stack.push(float(belowTopDataOfStack / topDataOfStack),1);
                }
                else {
                    delete[] wordsTracking;
                    Instructions.close();
                    throw StackEmpty(lineNum);
                }
            }
            else if(wordsTracking[0] == "irem") { // Lenh 9
                if(Stack.maxIndex() > 2) {
                    if(max((int)Stack.topDataType(),(int)Stack.belowTopDataType()) == 0) {
                        topDataOfStack = Stack.topDataValue();Stack.pop();
                        belowTopDataOfStack = Stack.topDataValue();Stack.pop();
                            if(topDataOfStack == 0) {
                                delete[] wordsTracking;
                                Instructions.close();
                                throw DivideByZero(lineNum);
                            }
                        Stack.push(int(belowTopDataOfStack - (int)(belowTopDataOfStack/topDataOfStack)*topDataOfStack),0);
                    }
                    else {
                        delete[] wordsTracking;
                        Instructions.close();
                        throw TypeMisMatch(lineNum);
                    }
                }
                else {
                    delete[] wordsTracking;
                    Instructions.close();
                    throw StackEmpty(lineNum);
                }
            }
            else if(wordsTracking[0] == "ineg") { // Lenh 10
                if(Stack.maxIndex() > 0) {
                    if((int)Stack.topDataType()== 0) {
                        topDataOfStack = Stack.topDataValue();Stack.pop();
                        Stack.push(int(- topDataOfStack),0);
                    }
                    else {
                        delete[] wordsTracking;
                        Instructions.close();
                        throw TypeMisMatch(lineNum);
                    }
                }
                else {
                    delete[] wordsTracking;
                    Instructions.close();
                    throw StackEmpty(lineNum);
                }
            }
            else if(wordsTracking[0] == "fneg") { // Lenh 11
                if(Stack.maxIndex()>0) {
                    topDataOfStack = Stack.topDataValue();Stack.pop();
                    Stack.push(float(- topDataOfStack),1);
                }
                else {
                delete[] wordsTracking;
                Instructions.close();
                throw StackEmpty(lineNum);
                }
            }
            else if(wordsTracking[0] == "iand") { // Lenh 12
                if(Stack.maxIndex()>2) {
                    if(max((int)Stack.topDataType(),(int)Stack.belowTopDataType()) == 0) {
                        topDataOfStack = Stack.topDataValue();Stack.pop();
                        belowTopDataOfStack = Stack.topDataValue();Stack.pop();
                        int e = (int)topDataOfStack&(int)belowTopDataOfStack;
                        Stack.push(int(e),0);
                    }
                    else {
                        delete[] wordsTracking;
                        Instructions.close();
                        throw TypeMisMatch(lineNum);
                    }
                }
                else {
                    delete[] wordsTracking;
                    Instructions.close();
                    throw StackEmpty(lineNum);
                }
            }
            else if(wordsTracking[0] == "ior") { // Lenh 13
                if(Stack.maxIndex()>2) {
                    if(max((int)Stack.topDataType(),(int)Stack.belowTopDataType()) == 0) {
                        topDataOfStack = Stack.topDataValue();Stack.pop();
                        belowTopDataOfStack = Stack.topDataValue();Stack.pop();
                        int e = (int)topDataOfStack|(int)belowTopDataOfStack;
                        Stack.push(int(e),0);
                    }
                    else {
                        delete[] wordsTracking;
                        Instructions.close();
                        throw TypeMisMatch(lineNum);
                    }
                }
                else {
                    delete[] wordsTracking;
                    Instructions.close();
                    throw StackEmpty(lineNum);
                }
            }
            else if(wordsTracking[0] == "ieq") { // Lenh 14
                if(Stack.maxIndex()>2) {
                    if(max((int)Stack.topDataType(),(int)Stack.belowTopDataType()) == 0) {
                        topDataOfStack = Stack.topDataValue();Stack.pop();
                        belowTopDataOfStack = Stack.topDataValue();Stack.pop();
                            if(topDataOfStack == belowTopDataOfStack) {
                                Stack.push(1,0);
                            }
                            else {
                                Stack.push(0,0);
                            }
                    }
                    else {
                        delete[] wordsTracking;
                        Instructions.close();
                        throw TypeMisMatch(lineNum);
                    }
                }
                else {
                    delete[] wordsTracking;
                    Instructions.close();
                    throw StackEmpty(lineNum);
                }
            }
            else if(wordsTracking[0] == "feq") { // Lenh 15
                if(Stack.maxIndex()>2) {
                    topDataOfStack = Stack.topDataValue(); Stack.pop();
                    belowTopDataOfStack = Stack.topDataValue(); Stack.pop();
                        if(topDataOfStack == belowTopDataOfStack) {
                            Stack.push(1,0);
                        }
                        else {
                            Stack.push(0,0);
                        }
                }
                else {
                    delete[] wordsTracking;
                    Instructions.close();
                    throw StackEmpty(lineNum);
                }
            }
            else if(wordsTracking[0] == "ineq") { // Lenh 16
                if(Stack.maxIndex()>2) {
                    if(max((int)Stack.topDataType(),(int)Stack.belowTopDataType()) == 0) {
                        topDataOfStack = Stack.topDataValue();Stack.pop();
                        belowTopDataOfStack = Stack.topDataValue();Stack.pop();
                            if(topDataOfStack != belowTopDataOfStack) {
                                Stack.push(1,0);
                            }
                            else {
                                Stack.push(0,0);
                            }
                    }
                    else {
                        delete[] wordsTracking;
                        Instructions.close();
                        throw TypeMisMatch(lineNum);
                    }
                }
                else {
                    delete[] wordsTracking;
                    Instructions.close();
                    throw StackEmpty(lineNum);
                }
            }
            else if(wordsTracking[0] == "fneq") { // Lenh 17
                if(Stack.maxIndex()>2) {
                    topDataOfStack = Stack.topDataValue();Stack.pop();
                    belowTopDataOfStack = Stack.topDataValue();Stack.pop();
                    if(topDataOfStack != belowTopDataOfStack)
                        {Stack.push(1,0);}
                    else
                        {Stack.push(0,0);}
                }
                else {
                    delete[] wordsTracking;
                    Instructions.close();
                    throw StackEmpty(lineNum);
                }
            }
            else if(wordsTracking[0] == "ilt") { // Lenh 18
                if(Stack.maxIndex()>2) {
                    if(max((int)Stack.topDataType(),(int)Stack.belowTopDataType()) == 0) {
                        topDataOfStack = Stack.topDataValue();Stack.pop();
                        belowTopDataOfStack = Stack.topDataValue();Stack.pop();
                        if(belowTopDataOfStack < topDataOfStack) {
                            Stack.push(1,0);
                        }
                        else {
                            Stack.push(0,0);
                        }
                    }
                    else {
                        delete[] wordsTracking;
                        Instructions.close();
                        throw TypeMisMatch(lineNum);
                    }
                }
                else {
                    delete[] wordsTracking;
                    Instructions.close();
                    throw StackEmpty(lineNum);
                }
            }
            else if(wordsTracking[0] == "flt") { // Lenh 19
                if (Stack.maxIndex()>2) {
                    topDataOfStack = Stack.topDataValue();Stack.pop();
                    belowTopDataOfStack = Stack.topDataValue();Stack.pop();
                    if(belowTopDataOfStack < topDataOfStack) {
                        Stack.push(1,0);
                    }
                    else {
                        Stack.push(0,0);
                    }
                }
                else {
                    delete[] wordsTracking;
                    Instructions.close();
                    throw StackEmpty(lineNum);
                }
            }
            else if(wordsTracking[0] == "igt") { // Lenh 20
                if(Stack.maxIndex()>2) {
                    if(max((int)Stack.topDataType(),(int)Stack.belowTopDataType()) == 0) {
                        topDataOfStack = Stack.topDataValue();Stack.pop();
                        belowTopDataOfStack = Stack.topDataValue();Stack.pop();
                        if(belowTopDataOfStack > topDataOfStack) {
                            Stack.push(1,0);
                        }
                        else {
                            Stack.push(0,0);
                        }
                    }
                else {
                    delete[] wordsTracking;
                    Instructions.close();
                    throw TypeMisMatch(lineNum);
                }
                }
                else {
                    delete[] wordsTracking;
                    Instructions.close();
                    throw StackEmpty(lineNum);
                }
            }
            else if (wordsTracking[0] == "fgt") { // Lenh 21
                if(Stack.maxIndex()>2) {
                    topDataOfStack = Stack.topDataValue();Stack.pop();
                    belowTopDataOfStack = Stack.topDataValue();Stack.pop();
                    if(belowTopDataOfStack > topDataOfStack) {
                        Stack.push(1,0);
                    }
                    else {
                        Stack.push(0,0);
                    }
                }
                else {
                    delete[] wordsTracking;
                    Instructions.close();
                    throw StackEmpty(lineNum);
                }
            }
            else if(wordsTracking[0] == "ibnot") // Lenh 22
            {
         if (Stack.maxIndex()>0)
                {
                if((int)Stack.topDataType() == 0)
                {
                topDataOfStack = Stack.topDataValue();Stack.pop();
                if(topDataOfStack != 0)
                Stack.push(int(0),0);
                else
                Stack.push(int(1),0);
                }
                else
                {
                    delete[] wordsTracking;
            Instructions.close();
                    throw TypeMisMatch(lineNum);
                }
                }
                else
                {
                    delete[] wordsTracking;
            Instructions.close();
                    throw StackEmpty(lineNum);
                }
            }
            else if(wordsTracking[0] == "i2f") // Lenh 29
            {
         if(Stack.maxIndex()>0)
                {
                if((int)Stack.topDataType() == 0)
                {
                topDataOfStack = Stack.topDataValue();Stack.pop();
                Stack.push(float(topDataOfStack),1);
                }
                else
                {
                    delete[] wordsTracking;
            Instructions.close();
                    throw TypeMisMatch(lineNum);
                }
                }
                else
                {
                    delete[] wordsTracking;
            Instructions.close();
                    throw StackEmpty(lineNum);
                }
            }
            else if(wordsTracking[0] == "f2i") // Lenh 30
            {
         if(Stack.maxIndex()>0)
                {
                if((int)Stack.topDataType() == 1)
                {
                topDataOfStack = Stack.topDataValue();Stack.pop();
                Stack.push(int(topDataOfStack),0);
                }
                else
                {
                    delete[] wordsTracking;
            Instructions.close();
                    throw TypeMisMatch(lineNum);
                }
                }
                else
                {
                    delete[] wordsTracking;
            Instructions.close();
                    throw StackEmpty(lineNum);
                }
            }
            else //31 top
            {
         if(!Stack.isEmpty())
            {
                if((int)Stack.topDataType() == 1)
                    {
                        cout<<(float)Stack.topDataValue()<<"\n";
                    }
                else
                    {
                        cout<<(int)Stack.topDataValue()<<"\n";
                    }
            }
                else
                {
                    delete[] wordsTracking;
                    Instructions.close();
                    throw StackEmpty(lineNum);
                }
           }
        }
        else { // Cac chuoi lenh co 2 cum lenh
            if(wordsTracking[0] == "iconst") // Lenh 23
            {
        if(!Stack.isFull())
        {
            Stack.push(stoi(wordsTracking[1]),0);
        }
        else
        {
            delete[] wordsTracking;
            Instructions.close();
            throw StackFull(lineNum);
        }
            }
            else if(wordsTracking[0] == "fconst") // Lenh 24
            {
        if(!Stack.isFull())
        {
            Stack.push(stof(wordsTracking[1]),1);
        }
        else
        {
            delete[] wordsTracking;
            Instructions.close();
            throw StackFull(lineNum);
        }
            }
            else if(wordsTracking[0] == "iload") // Lenh 25
            {
        if(Array.outOfRange(stoi(wordsTracking[1])))
        {
            delete[] wordsTracking;
            Instructions.close();
            throw ArrayOutOfRange(lineNum);
        }
        else
        {
            if(Array.checkExistenceAtIndex(stoi(wordsTracking[1])))
            {
                if((int)Array.dataType(stoi(wordsTracking[1])) == 0)
                {
                    if(!Stack.isFull())
                        {
                            Stack.push((int)Array.valueTracking(stoi(wordsTracking[1])),0);
                        }
                        else
                        {
                            delete[] wordsTracking;
            Instructions.close();
                            throw StackFull(lineNum);
                        }
                }
                else
                {
                    delete[] wordsTracking;
            Instructions.close();
                    throw TypeMisMatch(lineNum);
                }
            }
            else
            {
                delete[] wordsTracking;
            Instructions.close();
                throw UndefinedVariable(lineNum);
            }
        }
            }
            else if(wordsTracking[0] == "fload") // Lenh 26
            {
        if(Array.outOfRange(stoi(wordsTracking[1])))
        {
            delete[] wordsTracking;
            Instructions.close();
            throw ArrayOutOfRange(lineNum);
        }
        else
        {
            if(Array.checkExistenceAtIndex(stoi(wordsTracking[1])))
            {
                if((int)Array.dataType(stoi(wordsTracking[1])) == 1)
                {
                    if(!Stack.isFull())
                        {
                            Stack.push((float)Array.valueTracking(stoi(wordsTracking[1])),1);
                        }
                        else
                        {
                            delete[] wordsTracking;
            Instructions.close();
                            throw StackFull(lineNum);
                        }
                }
                else
                {
                    delete[] wordsTracking;
            Instructions.close();
                    throw TypeMisMatch(lineNum);
                }
            }
            else
            {
                delete[] wordsTracking;
            Instructions.close();
                throw UndefinedVariable(lineNum);
            }
        }
            }
            else if(wordsTracking[0] == "istore") // Lenh 27
            {
        if(Array.outOfRange(stoi(wordsTracking[1])))
        {
            delete[] wordsTracking;
            Instructions.close();
            throw ArrayOutOfRange(lineNum);
        }
        else
        {
            if(!Stack.isEmpty())
            {
                if((int)Stack.topDataType() == 0)
                {
                    topDataOfStack = Stack.topDataValue();Stack.pop();
                    Array.putNewValueAtIndex((int)topDataOfStack,0,stoi(wordsTracking[1]));
                }
                else
                {
                    delete[] wordsTracking;
            Instructions.close();
                    throw TypeMisMatch(lineNum);
                }
            }
            else
            {
                delete[] wordsTracking;
            Instructions.close();
                throw StackEmpty(lineNum);
            }
        }
            }
            else if(wordsTracking[0] == "fstore") // Lenh 28
            {
        if(Array.outOfRange(stoi(wordsTracking[1])))
        {
            delete[] wordsTracking;
            Instructions.close();
            throw ArrayOutOfRange(lineNum);
        }
        else
        {
            if(!Stack.isEmpty())
            {
                if((int)Stack.topDataType() == 1)
                {
                    topDataOfStack = Stack.topDataValue();Stack.pop();
                    Array.putNewValueAtIndex((float)topDataOfStack,1,stoi(wordsTracking[1]));
                }
                else
                {
                    delete[] wordsTracking;
            Instructions.close();
                    throw TypeMisMatch(lineNum);
                }
            }
            else
            {
                delete[] wordsTracking;
            Instructions.close();
                throw StackEmpty(lineNum);
            }
        }
            }
            else { // Lenh 32
        if(Array.outOfRange(stoi(wordsTracking[1])))
        {
            delete[] wordsTracking;
            Instructions.close();
            throw ArrayOutOfRange(lineNum);
        }
        else
        {
           if(Array.checkExistenceAtIndex(stoi(wordsTracking[1])))
           {
               if((int)Array.dataType(stoi(wordsTracking[1]) == 0))
               {
                   cout<<(int)Array.valueTracking(stoi(wordsTracking[1]))<<"\n";
                   }
               else
               {
                   cout<<(float)Array.valueTracking(stoi(wordsTracking[1]))<<"\n";
               }
           }
           else
           {
               delete[] wordsTracking;
            Instructions.close();
               throw UndefinedVariable(lineNum);
           }
        }
            }
        }
        delete[] wordsTracking;
    }
}