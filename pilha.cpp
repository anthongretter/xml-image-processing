#include <string>
#include <stdexcept>
#include <stdio.h>
#include <iostream>


class Stack {

    public:
        Stack(){
            max_size = DEFAULT_SIZE;
            data = new std::string[max_size];
            __top = -1;
        };

        explicit Stack(int size){
            max_size = size;
            data = new std::string[max_size];
            __top = -1;
        };

        ~Stack(){
            delete [] data;
        };

        std::string top(){
            return data[__top];
        };
        std::string pop(){
            if(isEmpty()){
                throw std::out_of_range("pilha vazia");
            }
            __top -=1;
            return data[__top+1];
        };

        int push(std::string value){
            if(isFull()){
                return -1;
            }
            __top += 1;
            data[__top] = value;
            return __top;
        };

        bool isEmpty(){
            return __top == -1;
        };

        bool isFull(){
            return __top == max_size-1;
        }

    private:
        std::string* data;
        int const DEFAULT_SIZE = 10;
        int max_size;
        int __top;

    
};