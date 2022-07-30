#include "main.h"


Data* Cache::read(int addr) {
    //cout << "1" << endl;
    //Node *root = this->Foundingroot;
    if(p == 0){
        return NULL;
    }
    /*else if(SearchTree(addr, root)) {
        if(root->pro){
        return root->pro->data;
        }
    }*/
    else{
        //cout <<"bug: ";
        //root->pro->print();
        for(int i = 0; i < p; i++){
            if(this->arr[i]->addr == addr){
                return this->arr[i]->data;
            }
        }
    }
    return NULL;
}

Node* Deletenode(Node *root, int key){
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
            root->pro = p->pro;
            root->right = Deletenode(root->right, p->pro->addr);
        }
    }

    return root;

}

Elem* Cache::put(int addr, Data* cont) {  
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
    if(p == 16){
        //arr[15]->print();
        if(addr % 2 == 0){  //FIFO
            //Elem *del = new Elem(this->arr[0]->addr, this->arr[0]->data, this->arr[0]->sync);
            root = Deletenode(root, root->pro->addr);
            this->Foundingroot = root;
            //this->arr[16] = this->arr[0];
            for(int i = 1; i < p; i++){
                swap(this->arr[i - 1], this->arr[i]);
            }
            //this->arr[16] = NULL;
            this->p--;
            return this->arr[15];
        }
        else{               //LIFO
            //Elem *del = new Elem(this->arr[15]->addr, this->arr[15]->data, this->arr[15]->sync);
            swap(this->arr[p - 2], this->arr[p - 1]);
            root = Deletenode(root, this->arr[p - 1]->addr);
            this->p--;
            return this->arr[p];
        } 
    }
    return NULL;
}

/*void SearchTree(int addr, Node *root){
    if(root->pro != nullptr){ 
        if(root->pro->addr == addr){
            root->pro->print();
            return;
        }
    }
    else if(root->pro->addr > addr){
        SearchTree(addr, root->left);
    }
    else if(root->pro->addr < addr){
        SearchTree(addr, root->right);
    }  
    return;
}*/

Elem* Cache::write(int addr, Data* cont) {
    //cout << "3" << endl;
    Node *root = this->Foundingroot; 
    if(this->p == 0){
        root->pro = new Elem(addr, cont, 0);
        this->arr[this->p] = root->pro;
        this->p++;
    }
    else{
        int k;  
        for(k = 0; k < p; k++){
            if(this->arr[k] != nullptr){
                if(this->arr[k]->addr == addr){
                    break;
                }
            }
        }     
        
        if(this->arr[k] != nullptr && this->arr[k]->addr == addr && k != 15){        //if found addr
                    this->arr[k]->data = cont;
                    this->arr[k]->sync = 0;
        }
        else{                   //not found addrs
            Node *newnode = new Node;
            newnode->pro = new Elem(addr, cont, 0);
            root = FindParent(addr, root, newnode);
                //root = SearchTree(addr, root);
                //this->arr[this->p] = newnode->pro;
            this->p++;
        }    
            if(p == 16){
                if(addr % 2 == 0){  //FIFO
                    //Elem *del = new Elem(this->arr[0]->addr, this->arr[0]->data, this->arr[0]->sync);
                    root = Deletenode(root, root->pro->addr);
                    this->Foundingroot = root;
                    //this->arr[16] = this->arr[0];
                    for(int i = 1; i < p; i++){
                        swap(this->arr[i - 1], this->arr[i]);
                    }
                    //this->arr[16] = NULL;
                    this->p--;  
                    return this->arr[15];
                }
                else{               //LIFO
                    //Elem *del = new Elem(this->arr[15]->addr, this->arr[15]->data, this->arr[15]->sync);
                    swap(this->arr[p - 2], this->arr[p - 1]);
                    root = Deletenode(root, this->arr[p - 1]->addr);
                    this->p--;
                    return this->arr[p];
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

void printCayhaila(Node *MOSSforgivemeplease){
	if (MOSSforgivemeplease != nullptr){
		MOSSforgivemeplease->pro->print();
		printCayhaila(MOSSforgivemeplease->left);
		printCayhaila(MOSSforgivemeplease->right);
        delete MOSSforgivemeplease;
        MOSSforgivemeplease = nullptr;
	}
}

void Cache::preOrder() {
	Node *root = this->Foundingroot;
    printCayhaila(root);
}

void Cache::inOrder() {
    Elem **newarr = new Elem*[this->p];
    for (int i = 0; i < p; i++){
        //newarr[i] = new Elem(this->arr[i]->addr, this->arr[i]->data, this->arr[i]->sync);
        newarr[i] = this->arr[i];
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
    delete[] newarr;
}

