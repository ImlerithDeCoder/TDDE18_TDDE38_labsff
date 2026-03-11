#include <iostream>
#include <concepts>
#include <sstream>
#include <stdexcept>

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

    LinkList() {}

    ~LinkList() {
        delete_list(this->first_);
        length_ = 0;
    }

    // copy constructor
    LinkList(const LinkList& other) {
        auto current = other.first_;
        while (current != nullptr) {
            this->insert(current->data);
            current = current->next;
        }
    }
    
    // move constructor
    LinkList(LinkList&& other) {
        node<T>* tmp = other.first_;
        other.first_ = this->first_;

        this->length_ = other.length_;
        this->first_ = tmp;

        // eftersom other sickas med && alltså som ett rvalue, kommer användaren att ta bort other
        // kort efter detta
    }

    // copy assigment operator
    /*
    vad ska den göra?
        Den ska ta bort this eller lvalue, samt göra så att 
        lvalue blir ett nytt opjekt som är lika dant, 
        men med nytt minne, alltså en djup copia
    */
    LinkList& operator=(const LinkList& other) {
        if (this != &other) {// undviker self coppying
            delete_list(this->first_);// rensa nuvarande 
            this->first_ = nullptr;
            this->length_ = 0;
            
            auto curr = other.first_;
            while (curr != nullptr) {
                this->insert(curr->data);
                curr = curr->next;
            }
            this->length_ = other.length_;
        }
        
        return *this;
    }

    // move assigmenet
    LinkList& operator=(LinkList&& other) {
        if (this != &other) { // så vi undviker self assignmenet
            delete_list(this->first_);// rensa nuvarande 

            // sätter över other till this
            this->first_ = other.first_;
            this->length_ = other.length_;

            // så att others destruktor och tar bort this ochså eftersom de pekar på samma
            // samt others destruktor körs direkt när den går utanför scoap, därav && på den
            other.first_ = nullptr;
            other.length_ = 0;
        }

        return *this;
    }

    

    // inserts data in sorted order
    void insert(T data) {
        auto new_node = new node(data);

        if (this->first_ == nullptr || data < first_->data) {
            // new ska in på första platsen
            new_node->next = this->first_;
            this->first_ = new_node;
            this->length_++;
            return;
        }

        auto current = this->first_;
        while (current->next != nullptr && data > current->next->data) {
            current = current->next;
        }

        // new ska in efter current och innan current->next
        new_node->next = current->next;
        current->next = new_node;
        this->length_++;

    }
    
    // removes entry based on index
    T remove(int target) {
        if (target < 0 || target >= this->length_){
            throw std::out_of_range("Index out of range");
        }
        
        
        T data;        
        int itter = 0;
        auto current = first_;
        auto prev = first_;

        // vi vill lopa fram tills vi har att current är de nummret i ordningen som target
        while (target-1 > itter && current->next != nullptr) {
            itter++;
            current = current->next;
            // current är noden innan den som ska bort
        }
        

        // om vi ska ta bort entryn på första platsen i listan
        if (target == 0) {
            auto to_remove = this->first_;
            data = to_remove->data;
            this->first_ = this->first_->next;
            delete to_remove;
        } else {
            auto to_remove = current->next;
            data = to_remove->data;
            current->next = current->next->next;
            delete to_remove;
        }

        this->length_--;
        return data;

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

    int length() {
        return this->length_;
    }

    bool is_empty() {
        return length() == 0;
    }

private:
    node<T>* first_ = nullptr;
    int length_ = 0;

    void delete_list(node<T>* current) {
        if (current == nullptr) {
            return;
        } else {
            delete_list(current->next);
            delete current;
        }
    }

    

    

    // destructor, copy constructor, move constructor,
    // copy assignment operator and move assignment operator

};