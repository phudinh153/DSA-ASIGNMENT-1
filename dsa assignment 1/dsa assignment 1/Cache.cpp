#include "main.h"


Data* Cache::read(int addr) { //trả về dữ liệu được lưu tại địa chỉ addr nếu addr được lưu tại cache, ngược lại trả về NULL
    //cout << "1" << endl;
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

Node* Deletenode(Node *root, int key){
    //if(root == nullptr) return root;
    //root->pro->print();
    if(root->pro->addr > key) root->left = Deletenode(root->left, key);
    else if(root->pro->addr < key) root->right = Deletenode(root->right, key);
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
            root->right = Deletenode(root->right, p->pro->addr);
        }
    }

    return root;

}

Node* SearchTree(int addr, Node *root){
    if(root == nullptr || root->pro == nullptr){
        return root;
    }
    else if(root->pro != nullptr){ 
        if(root->pro->addr == addr){
                return root;
        }
    }
    else if(root->pro->addr > addr){
        return SearchTree(addr, root->left);
    }
    else if(root->pro->addr < addr){
        return SearchTree(addr, root->right);
    }   
}

Elem* Cache::put(int addr, Data* cont) {  //đưa addr và data vào trong cache và trả về phần tử bị đưa ra khỏi cache nếu có, ngược lại trả về NULL.
    //cout << "2" << endl;    
    Node *root = this->Foundingroot;    
    if(this->p == 0){
        root->pro = new Elem(addr, cont, 1);
        this->arr[this->p] = root->pro;
    }
    else{
        Node *newnode = new Node;
        newnode->pro = new Elem(addr, cont, 1);
        root = FindParent(addr, root, newnode);
        //root = SearchTree(addr, root);
        //this->arr[this->p] = root->pro;
    }
    this->p++;

    if(p == 15){
        if(addr % 2 == 0){  //FIFO
            Elem *del = new Elem(this->arr[0]->addr, this->arr[0]->data, this->arr[0]->sync);
            root = Deletenode(root, root->pro->addr);
            this->Foundingroot = root;
            for(int i = 1; i < p; i++){
                this->arr[i - 1] = this->arr[i];
            }
            root->pro->print();
            this->p--;
            return del;
        }
        else{               //LIFO
            Elem *del = new Elem(this->arr[14]->addr, this->arr[14]->data, this->arr[14]->sync);
            root = Deletenode(root, arr[14]->addr);
            this->p--;
            return del;
        } 
    }
    return NULL;
}

Elem* Cache::write(int addr, Data* cont) {
    //cout << "3" << endl;
    Node *root = this->Foundingroot;
    root = SearchTree(addr, root);
    if(root){         //if found addr
        if(root->pro){
            root->pro->data = cont;
            root->pro->sync = 0;
        }
    }
    else{                   //not found addr
        root = this->Foundingroot;
        if(this->p == 0){
            root->pro = new Elem(addr, cont, 0);
            this->arr[this->p] = root->pro;
        }
        else{
            Node *newnode = new Node;
            newnode->pro = new Elem(addr, cont, 0);
            root = FindParent(addr, root, newnode);
            //root = SearchTree(addr, root);
            //this->arr[this->p] = newnode->pro;
        }
        this->p++;
        if(p == 15){
            if(addr % 2 == 0){  //FIFO
                Elem *del = new Elem(this->arr[0]->addr, this->arr[0]->data, this->arr[0]->sync);
                root = Deletenode(root, root->pro->addr);
                this->Foundingroot = root;
                for(int i = 1; i < p; i++){
                    this->arr[i - 1] = this->arr[i];
                }
                root->pro->print();
                this->p--;
                return del;
            }
            else{               //LIFO
                Elem *del = new Elem(this->arr[14]->addr, this->arr[14]->data, this->arr[14]->sync);
                root = Deletenode(root, arr[14]->addr);
                this->p--;
                return del;
            } 
        }
    }

    return NULL;
}

void Cache::print() {
	for (int i = p - 1; i >= 0; i--){
        arr[i]->print();
    }
}

void printCayhaila(Node *t){
	if (t != NULL){
		t->pro->print();
		printCayhaila(t->left);
		printCayhaila(t->right);
	}
}

void Cache::preOrder() {
	Node *root = this->Foundingroot;
    printCayhaila(root);
}

void Cache::inOrder() {
    Elem **newarr = new Elem*[this->p];
    for (int i = 0; i < p; i++){
        newarr[i] = new Elem(arr[i]->addr, arr[i]->data, arr[i]->sync);
    }

    for (int i = 0; i < p - 1; i++){
        for(int j = 0; j < p - i - 1; j++){
            if(newarr[j]->addr > newarr[j + 1]->addr){
                swap(newarr[j], newarr[j + 1]);
            }
        }
    }
    for (int i = 0; i < p; i++){
        newarr[i]->print();
    }
}

