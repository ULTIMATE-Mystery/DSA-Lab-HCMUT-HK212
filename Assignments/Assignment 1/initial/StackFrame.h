#ifndef __STACK_FRAME_H__
#define __STACK_FRAME_H__
#include <string>
/*
StackFrame declaration
*/
class StackFrame {
    int opStackMaxSize;  // max size of operand stack
    int localVarArrSize; // size of local variable array
public:
    /*
    Constructor of StackFrame
    */
    StackFrame();
    class Stack {
        int index = -1;
        float operandStack [32];
    public:
        bool isEmpty() {
            return index == -1;
        }
        bool isFull() {
            return index == 31;
        }
        void push (float dataValue, int dataType) {
            operandStack [++index] = dataValue;
            operandStack [++index] = dataType;
        }
        void pop() {
            index -= 2;
        }
        float getDataValueAt (int index) {
            return operandStack [index];
        }
        int maxIndex() {
            return index;
        }
        float topDataValue() {
            return operandStack [index - 1];
        }
        int topDataType() {
            return operandStack [index];
        }
        int belowTopDataType() {
            return operandStack [index - 2];
        }
    };
    class Array {
        int IndexExistence [256];
        float localVariableArray [256];
        public:
        Array() {
            for (int i = 0; i < 256; i++) {
                IndexExistence [i] = -1;
            }
        }
        bool checkExistenceAtIndex (int index) {
            if (IndexExistence [index] == -1) return false;
            else return true;
        }
        bool outOfRange (int index) {
            if (index >= 256 || index < 0) return true;
            else return false;
        }
        int dataType (int index) {
            return (int) localVariableArray [index + 1];
        }
        float takeOutDataValue (int index) {
            IndexExistence [index] = -1;
            return localVariableArray [index];
        }
        float valueTracking (int index) {
            return localVariableArray [index];
        }
        void putNewValueAtIndex (float dataValue, int dataType, int index) {
            IndexExistence [index] = 1;
            localVariableArray [index] = dataValue;
            localVariableArray [index + 1] = dataType;
        }
    };
    /*
    Run the method written in the testcase
    @param filename name of the file
    */
    void run (std::string filename);
};
#endif // !__STACK_FRAME_H__