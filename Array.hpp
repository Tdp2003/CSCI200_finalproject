#ifndef ARRAY_H
#define ARRAY_H

#include "List.hpp"
#include <string>
#include <exception>
#include <iostream>

using namespace std;

template<typename T>
class Array : public List<T>{
public:
    Array();
    T get(const int) const override;
    void set(const int, const T) override;
    void insert(const int, const T) override;
    void remove(const int) override;
private:
    T* mpArr;
};

template<typename T>
Array<T>::Array(){
    mpArr = new T[0];
}

template<typename T>
T Array<T>::get(const int POS) const{
    return mpArr[POS];
}

template<typename T>
void Array<T>::set(const int POS, const T VALUE){
    mpArr[POS] = VALUE;
}

template<typename T>
 void Array<T>::insert(const int POS, const T VALUE){
    T* newArr = new T[this->mSize + 1];
    if(this->mSize == 0){
        newArr[0] = VALUE;
    }else if(POS <= 0){
        newArr[0] = VALUE;
        for(int i = 0; i < this->mSize; i++){
            newArr[i+1] = mpArr[i];
        }
    }else if(POS >= this->mSize){
        for(int i = 0; i < this->mSize; i++){
            newArr[i] = mpArr[i];
        }
        newArr[this->mSize] = VALUE;
    }else{
        for(int i = 0; i < POS; i++){
            newArr[i] = mpArr[i];
        }
        newArr[POS] = VALUE;
        for(int i = POS + 1; i < this->mSize + 1; i++){
            newArr[i] = mpArr[i-1];
        }
    }
    delete mpArr;
    mpArr = newArr;
    this->mSize++;
 }

 template<typename T>
 void Array<T>::remove(const int POS){
    if(this->mSize == 0){
        return;
    }
    T* newArr = new T[this->mSize - 1];
    if(POS <= 0){
        for(int i = 0; i < this->mSize - 1; i++){
            newArr[i] = mpArr[i+1];
        }
    }else if(POS >= this->mSize){
        for(int i = 0; i < this->mSize - 1; i++){
            newArr[i] = mpArr[i];
        }
    }else{
        for(int i = 0; i < POS; i++){
            newArr[i] = mpArr[i];
        }
        for(int i = POS + 1; i < this->mSize; i++){
            newArr[i-1] = mpArr[i];
        }
    }
    delete mpArr;
    mpArr = newArr;
    this->mSize--;
 }

#endif