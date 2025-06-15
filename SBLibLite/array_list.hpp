#ifndef SB_ARRAY_LIST_HPP
#define SB_ARRAY_LIST_HPP
namespace sb {
namespace cont {

/**
* @brief Node with array
* @author Spencer Banasik
* @details A node for the arraylist data type. The idea is that
* each node provides a contiguous array of elements, with a pointer 
* to the next area.
*/
template <typename T, size_t S>
class ArrayListNode {
public:

    T& at(size_t idx) {
        return my_data[idx];
    }

    T& operator[](size_t idx) {
        return my_data[idx];
    }

    size_t length() {
        return S;
    }

    T* data() {
        return my_data;
    }
    
    ArrayListNode* next() {
        return next_node;
    }

    void set_next(ArrayListNode* new_next) {
        next_node = new_next;
    }

private:

    T my_data[S];
    ArrayListNode* next_node = nullptr;

};

/**
* @brief Linked list with array nodes
* @author Spencer Banasik
* @details The array list container is one that I that thought of 
* when seeing Java's "ArrayList" container, though Java's ArrayList is 
* just a C++ vector. The idea is to mitigate the overhead of a linked list,
* while having contiguous storage that doesn't invalidate references when a
* reallocation occurs.
* 
* Random access through this is O(n/S), where S is the node array size. Optimal
* array sizes would vary depending on the data type implemented, but I estimate that
* it would be such that sizeof(T) * S >= cache line size, which is typically 64 bytes.
* Of course, benchmarking is the only way to really know which S is best.
* 
* Potential optimizations: Cache the last accessed node and if our desired element
* is in that node, we can use that immediately. We could also use it as a starting point 
* if we consider a common use case to be iterating though the elements.
* We could doubly link the nodes to allow for reverse iteration
*/
template <typename T, size_t S>
class ArrayList {
public:

    ArrayList() {
        initial = new ArrayListNode<T, S>();
        last = initial;
        num_nodes = 1;
    }
    ~ArrayList() {
        ArrayListNode<T, S>* prior = nullptr;
        for (size_t i = 0; i < num_nodes; i++) {
            prior = initial;
            initial = initial->next();
            delete prior;
        }
    }
    ArrayList(ArrayList& other) = delete;
    ArrayList& operator=(ArrayList& other) = delete;

    ArrayList(ArrayList&& other) {
        initial = other.initial;
        last = other.last;
        num_nodes = other.num_nodes;
        other.initial = nullptr;
        other.last = nullptr;
    }
    ArrayList& operator=(ArrayList&& other) {
        initial = other.initial;
        last = other.last;
        num_nodes = other.num_nodes;
        other.initial = nullptr;
        other.last = nullptr;
    }
    
    T& at(size_t idx) {
        size_t num_traverse = idx / S;
        ArrayListNode<T, S>* node = initial;
        for (size_t i = 0; i < num_traverse; i++) {
            node = node->next();
        }
        return node[idx % S];
    }

    T& operator[](size_t idx) {
        size_t num_traverse = idx / S;
        ArrayListNode<T, S>* node = initial;
        for (size_t i = 0; i < num_traverse; i++) {
            node = node->next();
        }
        return node[idx % S];
    }

    size_t length() {
        return num_nodes * S;
    }

    size_t nodes() {
        return num_nodes;
    }

    // TODO: we should follow the set 
    // of std::array functions,
    // since this more closely resembles 
    // that.
    // push/pop_front/back only work
    // at a node level, really.


    ArrayListNode<T, S>* front() {
        return initial;
    }

    ArrayListNode<T, S>* back() {
        return last;
    }

private:

    void reallocate() {
        ArrayListNode<T, S>* prior = last;
        last = new ArrayListNode<T, S>();
        prior->set_next(last);
    }

    ArrayListNode<T, S>* initial = nullptr;
    ArrayListNode<T, S>* last = nullptr;
    size_t num_nodes = 0;

};

}
}
#endif