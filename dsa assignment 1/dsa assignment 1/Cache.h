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
    
    Node *Foundingroot = new Node;
    Cache(int s) {
        arr = new Elem*[s];
        p = 0;
    }
    ~Cache() {
        delete[] arr;
    }
        Node *FindParent(int ad, Node *root, Node *newnode){
        if(root == nullptr){
                this->arr[this->p] = newnode->pro;
                return newnode;      
        }
        else {
            if(root->pro->addr > ad) {     
            root->left = FindParent(ad, root->left, newnode);
            }
            else if(root->pro->addr < ad) {
            root->right = FindParent(ad, root->right, newnode);
            }
        }
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