#include <string>
#include <stdexcept>
#include <stdio.h>
#include <iostream>


class Queue {
    public:

        Queue(){
            max_size = DEFAULT_SIZE;
            data = new int[max_size];
            __top = -1;
        };

        explicit Queue(int size){
            max_size = size;
            data = new int[max_size];
            __top = -1;
        };

        ~Queue(){
            delete [] data;
        };

        void clear(){
            __top = -1;
        };
        bool isFull(){
            return __top == max_size-1;
        };
        bool isEmpty(){
            return __top == -1;
        };
        int push(int value){
            if(!isFull()){
                __top +=1;
                data[__top] = value;
                return __top;
            }
            throw std::out_of_range("queue is full");
        };
        int pop(){
            if(!isEmpty()){
                int out = data[0];
                __top -=1;
                for(int i = 0; i <= __top; i++){
                    data[i] = data[i+1];
                }
                return out;
            }
            throw std::out_of_range("queue is empty");

        };
        int back(){
            if(!isEmpty()){
                return data[__top];
            }
            throw std::out_of_range("queue is empty");
        };


    private:
        int* data;
        int __top;
        int max_size;
        int const DEFAULT_SIZE = 10;

};