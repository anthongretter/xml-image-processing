#include <string>
#include <stdexcept>
#include <stdio.h>
#include <iostream>


class Stack {

    public:
        Stack(){
            max_size = DEFAULT_SIZE;
            data = new std::string[max_size];
            top = -1;
        };

        explicit Stack(int size){
            max_size = size;
            data = new std::string[max_size];
            top = -1;
        };

        ~Stack(){
            delete [] data;
        };

        std::string top(){
            return data[top];
        };
        std::string pop(){
            if(isEmpty()){
                throw std::out_of_range("pilha vazia");
            }
            top -=1;
            return data[top+1];
        };

        int push(std::string value){
            if(isFull()){
                return -1;
            }
            top += 1;
            data[top] = value;
            return top;
        };

        bool isEmpty(){
            return top == -1;
        };

        bool isFull(){
            return top == max_size-1;
        }

    private:
        std::string* data;
        int const DEFAULT_SIZE = 10;
        int max_size;
        int top;

    
};