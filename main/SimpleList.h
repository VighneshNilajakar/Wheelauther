#pragma once

#include <stddef.h>

template<class T>
struct SimpleListNode {
    T data;
    SimpleListNode<T>* next = NULL;
};

template<typename T>
class SimpleList {
    public:
        SimpleList();
        SimpleList(int(*compare)(T & a, T & b));
        virtual ~SimpleList();

        virtual void setCompare(int (*compare)(T& a, T& b));
        
        virtual int size();
        virtual bool isSorted();
        virtual bool isEmpty();

        virtual void add(T obj);
        virtual void add(int index, T obj);
        virtual void insert(T obj);
        virtual void replace(int index, T obj);
        virtual void remove(int index);
        virtual void clear();

        virtual T get(int index);
        virtual T getFirst();
        virtual T getLast();
        
        virtual int search(T obj);
        virtual void sort();

    protected:
        int (*compare)(T& a, T& b) = NULL;

        int listSize = 0;
        SimpleListNode<T>* listBegin = NULL;
        SimpleListNode<T>* listEnd = NULL;

        // Helps get() method by saving last position
        SimpleListNode<T>* lastNodeGot = NULL;
        int lastIndexGot = -1;
        bool isCached = false;
        bool sorted = true;

        virtual SimpleListNode<T>* getNode(int index);
};

// Implementation
template<typename T>
SimpleList<T>::SimpleList() {}

template<typename T>
SimpleList<T>::SimpleList(int(*compare)(T & a, T & b)) {
    setCompare(compare);
}

template<typename T>
SimpleList<T>::~SimpleList() {
    clear();
}

template<typename T>
void SimpleList<T>::clear() {
    while(listSize > 0) {
        SimpleListNode<T>* h = listBegin;
        listBegin = listBegin->next;
        delete h;
        listSize--;
    }
    listEnd = NULL;
    lastNodeGot = NULL;
    lastIndexGot = -1;
    isCached = false;
}

template<typename T>
void SimpleList<T>::add(T obj) {
    SimpleListNode<T>* node = new SimpleListNode<T>();
    node->data = obj;
    
    if (!listBegin) listBegin = node;
    if (listEnd) {
        listEnd->next = node;
        listEnd = node;
    } else {
        listEnd = node;
    }
    
    listSize++;
    sorted = false;
}

template<typename T>
SimpleListNode<T>* SimpleList<T>::getNode(int index) {
    if (index < 0 || index >= listSize) return NULL;

    SimpleListNode<T>* h = listBegin;
    int c = 0;

    while(h && c < index) {
        h = h->next;
        c++;
    }

    return h;
}

template<typename T>
T SimpleList<T>::get(int index) {
    SimpleListNode<T>* h = getNode(index);
    if (h) return h->data;
    return T();
}

template<typename T>
int SimpleList<T>::size() {
    return listSize;
}

template<typename T>
bool SimpleList<T>::isSorted() {
    return sorted;
}

template<typename T>
void SimpleList<T>::setCompare(int (*compare)(T& a, T& b)) {
    this->compare = compare;
    sort();
}