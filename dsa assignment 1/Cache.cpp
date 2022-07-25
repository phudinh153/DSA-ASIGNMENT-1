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
    /*else if(SearchTree(addr, root)) {
        if(root->pro){
        return root->pro->data;
        }
    }*/
    else{
        for(int i = 0; i < p; i++){
            if(this->arr[i]->addr == addr){
                return this->arr[i]->data;
            }
        }
    }
    return NULL;
}

void Deletenode(Node *root, int key){
    if(root == nullptr) return;
    else if(root->pro->addr > key) Deletenode(root->left, key);
    else if(root->pro->addr < key) Deletenode(root->right, key);
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
            root->pro->data = p->pro->data;
            Deletenode(root->right, p->pro->addr);
        }
    }
}

Node *FindParent(int ad, Node *root){
    if(root->left == nullptr || root->right == nullptr){
        return root;
    }
    else if(root->pro->addr > ad) {
        root->left = FindParent(ad, root->left);
    }
    else{
        root->right = FindParent(ad, root->right);
    }
}

Elem* Cache::put(int addr, Data* cont) {  //đưa addr và data vào trong cache và trả về phần tử bị đưa ra khỏi cache nếu có, ngược lại trả về NULL.
    cout << "2" << endl;    
    Node *root = this->Foundingroot;    
    if(this->p == 0){
        root->pro = new Elem(addr, cont, 1);
        this->arr[this->p] = root->pro;
    }
    else{
        root = FindParent(addr, root);
        Node *newnode = new Node;
        newnode->pro = new Elem(addr, cont, 1);
        if(root->pro->addr > addr){
            root->left = newnode;
            root = root->left;
        }
        else if(root->pro->addr < addr){
            root->right = newnode;
            root = root->right;
        }
        this->arr[this->p] = root->pro;
    }
    this->p++;

    if(p == 15){
        if(addr % 2 == 0){  //FIFO
            Node *root = this->Foundingroot;
            Deletenode(root, root->pro->addr);
        }
        else{               //LIFO
            Node *root = this->Foundingroot;
            Deletenode(root, arr[14]->addr);
        }
        this->p--;
        return this->arr[14];
    }
    return NULL;
}

Elem* Cache::write(int addr, Data* cont) {
    cout << "3" << endl;
    Node *root = this->Foundingroot;
    //root = SearchTree(addr, root);
    if(root->pro){         //if found addr
        root->pro->data = cont;
        root->pro->sync = 0;
    }
    else{                   //not found addr
        root = this->Foundingroot;
        if(this->p == 0){
            root->pro = new Elem(addr, cont, 0);
            this->arr[this->p] = root->pro;
        }
        else{
            root = FindParent(addr, root);
            Node *newnode = new Node;
            newnode->pro = new Elem(addr, cont, 0);
            this->arr[this->p] = newnode->pro;
            if(root->pro->addr > addr){
                root->left = newnode;
                root = root->left;
            }
            else if(root->pro->addr < addr){
                root->right = newnode;
                root = root->right;
            }
        }
        this->p++;
        if(p == 15){
            if(addr % 2 == 0){  //FIFO
                Node *root = this->Foundingroot;
                Deletenode(root, root->pro->addr);
            }
            else{               //LIFO
                Node *root = this->Foundingroot;
                Deletenode(root, arr[14]->addr);
            }
            this->p--;
            return this->arr[14];
        }
    }

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

