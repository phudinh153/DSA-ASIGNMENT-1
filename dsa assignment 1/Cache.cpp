#include "main.h"

Node* SearchTree(int addr, Node *root){
    if(root->pro->addr == addr || root == nullptr){
        return root;
    }
    else if(root->pro->addr > addr){
        return SearchTree(addr, root->left);
    }
    else{
        return SearchTree(addr, root->right);
    }   
}

Data* Cache::read(int addr) { //trả về dữ liệu được lưu tại địa chỉ addr nếu addr được lưu tại cache, ngược lại trả về NULL
    cout << "1" << endl;
    Node *root = this->Foundingroot;
    if(p == 0){
        return NULL;
    }
    else if(SearchTree(addr, root)) return root->pro->data;
    return NULL;
}

void DeleteFIFO(Node *root, int key){
    if(root == nullptr) return;
    else if(root->pro->addr > key) DeleteFIFO(root->left, key);
    else if(root->pro->addr < key) DeleteFIFO(root->right, key);
    else{
        if(root->left == nullptr && root->right == nullptr){
            delete root;
            root = nullptr;
        }
        else if(root->left == nullptr){
            Node *p = root;
            root = root->right;
            delete p;
            p = nullptr;
    
        }
        else if(root->right == nullptr){
            Node *p = root;
            root = root->left;
            delete p;
            p = nullptr;
    
        }
        else{
            Node *p = root->right;
            while(p->left != nullptr){
                p = p->left;
            }
            root->pro->addr = p->pro->addr;
            root->pro->data = p->pro->data;
            DeleteFIFO(root->right, p->pro->addr);
        }
    }
}

Elem* Cache::put(int addr, Data* cont) {  //đưa addr và data vào trong cache và trả về phần tử bị đưa ra khỏi cache nếu có, ngược lại trả về NULL.
    cout << "2" << endl;            
    if(p == 15){
        if(addr % 2 == 0){  //FIFO
            Node *root = this->Foundingroot;
            DeleteFIFO(root, root->pro->addr);
        }
        else{               //LIFO
            
        }
    }
    return NULL;
}

Elem* Cache::write(int addr, Data* cont) {
    cout << "3" << endl;
    return NULL;
}

void Cache::print() {
	for (int i = 0; i < p; i++)
        arr[i]->print();
}

void Cache::preOrder() {
	for (int i = 0; i < p; i++)
        arr[i]->print();
}

void Cache::inOrder() {
    for (int i = 0; i < p; i++)
        arr[i]->print();
}

