#include <iostream>
using namespace std;
#include <unordered_map>

template <typename T>
class Node {
    public:
    //val
        T value;
        Node<T>* nxt;
        Node<T>* prv;


    Node(T val){
        value = val;
    }
    

    
};

template <typename T>
class LRU {
    public:
        int capacity;
        unordered_map <T, Node<T>*> hashmap;

        //MRU
        Node<T> *head;
        //LRU
        Node<T> *tail;
        int count;



    LRU(int cap) {
        capacity = cap;
        count = 0;
    }


    //inserts to the LRU

    void put(T input) {
        
        //add first
        if (hashmap.count(input) == 1) {

            cout << "Already in LRU Cache" << endl;
            return;
        }
        //add to map()
        Node<T>* temp = new Node<T>(input);
        
        
        hashmap.insert({input, temp});
        if (count ==  0) {
            
            head = temp;
            tail = temp;
            //printf("%p\n", head);
            count = count + 1;
            
        }
        else if(count < capacity) {
            
            temp->nxt = head;
            head->prv = temp;
            //printf( "%p\n", head);
            //printf("%p\n", &temp);
            head = temp;
            //printf( "%p\n", head);
            count = count + 1;
            
            
       

        }

        else {

            Node<T>* garbage = tail;

            temp->nxt = head;
            head->prv = temp;
            head = temp;

            tail = tail->prv;
            tail->nxt = NULL; 
            

            //add garbage collection


            hashmap.erase(garbage->value);
            delete garbage;
        }

        
    


    }

    T get(T input) {
        //check if input is in the dictionary
        if (hashmap.count(input) == 1) {

            Node<T>* node_ptr = hashmap.at(input);
            Node<T>* prev = node_ptr->prv;
            Node<T>* next = node_ptr->nxt;
            

            if (prev == NULL) {

                return hashmap.at(input)->value;

            }

            else if (next == NULL) {
                prev->nxt = next; 
                tail = prev;
                node_ptr->prv = NULL;
                node_ptr->nxt = head;
                head = node_ptr; 
                return hashmap.at(input)->value;

            }

        
            else {

                prev->nxt = next; 
                next->prv = prev;
                node_ptr->prv = NULL;
                node_ptr->nxt = head;
                head = node_ptr; 
                return hashmap.at(input)->value;

            }
            
        }

        else {

            cout << "You are trying to access something that is not in the Cache" << endl;
            return -1;
        }




    }
   



    

    

};

void print_LRU_values(Node<int>* head ) {
    Node<int>* iter = head;
    while(iter != NULL) {
        printf("%d__", iter->value); 
        iter = iter->nxt;  

    }
    printf("\n");


}    


int main(int argc, char** argv) {

    //add command line arguments capacity of the LRU
    



    LRU<int> myLRU(atoi(argv[1]));
    while(1) {

        int p_g, val;   
        cout << "Type 1 for put, or 2 for get: ";
        cin >> p_g;
        cout << "Type your number: ";
        cin >> val;

        if (p_g == 1) {

            myLRU.put(val);
            print_LRU_values(myLRU.head);
        }

        else {

            int test = myLRU.get(val);
            printf("Got: %d\n",test);
            print_LRU_values(myLRU.head);
            
        }

    }
    



    
    
    
    

    
    
    
    


    

return 0;
}