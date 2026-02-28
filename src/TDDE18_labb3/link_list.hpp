#include <iostream>
#include <concepts>

// denna var ganska cool faktiskt:)
template <typename T>
concept comparable = requires (T a, T b) {
    {a < b} -> std::same_as<bool>;
    {a > b} -> std::same_as<bool>;

};

template <comparable T>
struct node {
    node* next;
    T data;
};

template<comparable T>
class LinkList {
public: 
    // inserts data in sorted order
    template<comparable T>
    void insert(T data) {
        auto new_node = new node<T>;
        auto current = first;



        while (current != nullptr) {
            if (current->next == nullptr) {
                // då ska new node läggas in direkt som nästa

                return;
            }
            if (current->data < data && current->next->data > data) {
                // då ska new node in mellan current och current->next
                
                
                return;
            }    
        }
        // här är listan tom och new node blir first
         
    }
    
    // removes entry based on index
    T remove(int index);
    
    // prints the whole list, e.g.  [1, 2, 3] 
    void print(); 

    // returns the values at index
    T at(int index); 

private:
    node<T>* first;

    LinkList() {
        first = nullptr;
    }

    ~LinkList() {
        node<T>* current = first;
        while (current != nullptr) {
            node<T>* next = current->next;
            delete current;
            current = next;
        }
    }

    // destructor, copy constructor, move constructor,
    // copy assignment operator and move assignment operator

};