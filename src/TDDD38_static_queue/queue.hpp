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
    static_assert(CAPACITY <= 0, "Size must be > 0.");

    Queue() {}


    ~Queue() {
        while(!empty()) {
            delete dequeue();
        }
        free(queue_);
    }
    

    // copy assignment operator
    Queue operator=(const Queue& other) {
        if (this == &other) {return;}// avoid self assigmenet
        
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
        
        delete this;
        this = new Queue<T, CAPACITY>();
        while (!other.empty()) {
            T tmp = other.dequeue();
            this->enqueue(tmp);// här är de ju lite onödigt att göra en kopia, men jaja igen
        }
    }

    // move constructor
    Queue(Queue&& other) {
        if (this == &other) {return;}// avoid self assigmenet
        
        // glömm inte att logga timmar!;)
        
    }

    // move assigmenet
    Queue operator=(Queue&& other) {
        if (this == &other) {return;}// avoid self assigmenet
        

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

    T& front() const {
        return queue_[head_];
    }

    
    template<size_t M>
    void copy_and_expand() {
        Queue* new_queue = new Queue<T, CAPACITY+M>();
        while (!this->empty()) {
            T tmp = this->dequeue();
            new_queue->enqueue(tmp);
            delete tmp;
        }
        delete this;
        this = std::move(new_queue);
    }

private:
    T* queue_ = malloc(sizeof(T)*CAPACITY);
    size_t head_{0};
    size_t tail_{0};
    size_t size_{0};
    

    




};