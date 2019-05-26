#ifndef ITERATOR_H
#define ITERATOR_H

#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <assert.h>
#include <QDebug>

template<typename T>
class Iterator {
private:
    std::vector<T> * pointer;
    int current;
public:
    Iterator(std::vector<T> * item, int current) : pointer(item), current(current){}

    bool operator!=(const Iterator<T> & iter) const;
    bool operator==(const Iterator<T> & iter) const;

    Iterator& operator++();
    Iterator& operator--();
    Iterator*  next();
    Iterator*  prev();
    T get_value();

};

template<typename T>
bool Iterator<T>::operator==(const Iterator<T> & iter) const {
    return pointer[current] == iter.pointer[current];
}

template<typename T>
bool Iterator<T>::operator!=(const Iterator<T> & iter) const {
    return pointer[current] != iter.pointer[current];
}

template<typename T>
Iterator<T>* Iterator<T>::next(){
    if (current == pointer->size()){
        //some exception
    }
    current = current+1;
    return this;
}

template<typename T>
Iterator<T>* Iterator<T>::prev(){
    if (current == 0){
        //some exception
    }
    current--;
    return this;
}
template<typename T>
T Iterator<T>:: get_value(){
    return this->pointer->at(current);
}
#endif // ITERATOR_H
