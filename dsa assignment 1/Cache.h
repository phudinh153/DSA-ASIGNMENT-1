#ifndef CACHE_H
#define CACHE_H

#include "main.h"
class Node{
    public:
        Node *left, *right;
        Elem *pro; //property
    Node(){
        left = nullptr;
        right = nullptr;
    }
        

};
class Cache {
        Elem** arr;
        int p;
	public:
    
    Node *Foundingroot;
    Cache(int s) {
        arr = new Elem*[s];
        p = 0;
    }
    ~Cache() {
        delete[] arr;
    }
		Data* read(int addr);
		Elem* put(int addr, Data* cont);
		Elem* write(int addr, Data* cont);
		void print();
		void preOrder();
		void inOrder();
};
;
#endif