#include <iostream>
#include <concepts>
#include <sstream>

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

    node(T data) : data(data), next(nullptr) {}
};

template<comparable T>
class LinkList {
public: 

    LinkList() {
        first_ = nullptr;
        length_ = 0;
    }

    ~LinkList() {
        node<T>* current = first_;
        while (current != nullptr) {
            node<T>* next = current->next;
            delete current;
            current = next;
        }
    }
    // inserts data in sorted order
    void insert(T data) {
        auto new_node = new node(data);
        // current är alltså en pekare till nuvarande noden
        auto current = this->first_;

        while (current != nullptr) {
            if (current->next == nullptr) {
                // då ska new node läggas in direkt som nästa
                current->next = new_node;
                new_node->data = data;
                new_node->next = nullptr;
                length_++;
                return;
            }
            else if (current->data < data && current->next->data > data) {
                // då ska new node in mellan current och current->next
                new_node->next = current->next;
                current->next = new_node;
                length_++;
                return;
            }
            // flytta fram current
            current = current->next;
        }
        this->first_ = new_node; 
        length_++;
    }
    
    // removes entry based on index
    T remove(int index) {
        return T();
    }
    
    // prints the whole list, e.g.  [1, 2, 3] 
    std::string to_string() {
        std::ostringstream result;
        result << "[";
        auto current = first_;

        while (current != nullptr) {
            result << current->data;
            
            if (current->next != nullptr) {
                result << ", ";
            }
            current = current->next;

        }
        
        result << "]";
        return result.str();
    } 

    // returns the values at index
    T at(int index) {
        auto current = first_;
        int count = 0;

        while (count < index) {
            count++;
            if (current == nullptr) {
                throw std::out_of_range("Index out of range");
            }
            current = current->next;
        }
        return current->data;
    }

private:
    node<T>* first_;
    int length_;

    

    

    // destructor, copy constructor, move constructor,
    // copy assignment operator and move assignment operator

};