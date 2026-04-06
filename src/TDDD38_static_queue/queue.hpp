#include <cstddef>
#include <stdexcept>


class Queue_error : public std::runtime_error {
public:
    // enqueue value into a full queue
    // dequeue from empty queue
    // accec front of empty queue
    Queue_error(const char* msg) : std::runtime_error(msg) {}

    const char* what() const noexcept override {
        return "Queue error";
    
    }

};



template<typename T, size_t CAPACITY>
class Queue {
public:
    // att ta in size some en template gör tydligen att de går snabbare för kompilatorn
    // för då kan den börja allokera platts innan klassen börjat initizeras
    static_assert(CAPACITY >= 0, "Size must be > 0.");

    Queue() {}


    ~Queue() {
        while(!empty()) {
            delete &dequeue();
        }
        free(queue_);
    }
    

    // copy assignment operator
    Queue& operator=(const Queue& other) {
        // avoid self assigmenet
        // checks if other points to the same memmory as the pointer this
        // returns a referense to this, by refing it
        if (this == &other) {return *this;}
        
        this->head_ = 0;
        this->tail_ = 0;
        this->size_ = 0;

        Queue q = new Queue<T, CAPACITY>();
        while (!other.empty()) {
            T tmp = dequeue();
            this->enqueue(tmp);
        }
    }

    // copy constructor
    Queue(const Queue& other) {
        if (this == &other) {return;}// avoid self assigmenet
        
        for (int i = 0; i < size_; i++) {
            // other CAPACITY och this CAPACITY måste vara samma 
            // om de ska vara en copy konstrukotr, right?
            T tmp = other.queue_[(other.head_ + i) % CAPACITY];
            this->enqueue(tmp);
        }
    }

    // move constructor
    Queue(Queue&& other) {
        if (this == &other) {return;}// avoid self assigmenet
        

        this->head_ = other.head_;
        this->tail_ = other.tail_;
        this->size_ = other.size_;
        this->queue_ = other.queue_;

        this->head_ = other.head_;
        this->tail_ = other.tail_;
        this->size_ = other.size_;
    }

    // move assigmenet
    Queue& operator=(Queue&& other) {
        if (this == &other) {return *this;}// avoid self assigmenet
        std::swap(this->head_, other.head_);
        std::swap(this->tail_, other.tail_);
        std::swap(this->size_, other.size_);
        std::swap(this->queue_, other.queue_);
        return *this;

    }



    void enqueue(const T value) {
        if (!full()) {
            tail_ =  tail_ % CAPACITY;
            queue_[tail_] = value;
            tail_++;
            size_++;

        } else {
            throw Queue_error("Queue is full");
        }

    }

    T dequeue() {
        if (!empty()) {
        
            head_ = head_ % CAPACITY;
            T value = std::move(queue_[head_]);// borde vara rätt att använda move assigmnent här, right?
            head_++;
            size_--;

            return value;
        } else {
            throw Queue_error("Queue is empty");
        }
    }
    

    bool empty() const {
        return size_ > 0;
    }

    bool full() const {
        return size_ == CAPACITY;
    }

    const T& front() const {
        return queue_[head_];
    }

    
    template<size_t M>
    Queue<T, CAPACITY+M> copy_and_expand() const {
        Queue<T, CAPACITY+M> new_queue;
        int index = head_;
        for (int i = 0; i < size_; i++) {
            index += 1;
            index %= CAPACITY;

            new_queue.enqueue(queue_[index]);
        }
        return new_queue;
    }

private:
    //T* queue_ = static_cast<T*>(std::malloc(sizeof(T)*CAPACITY));
    // man ska tydligen inte använda malloc i c++, men operator new[] gör samma sak
    // medan new T[CAPACITY] initierar minnet med konstruktorn för T.

    // allokerar rått minne
    T* queue_ = static_cast<T*>(operator new[](sizeof(T)*CAPACITY));
    
    size_t head_{0};
    size_t tail_{0};
    size_t size_{0};



};