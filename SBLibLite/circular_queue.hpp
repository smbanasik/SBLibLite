// Spencer Banasik
#ifndef SB_CIRCULAR_QUEUE_HPP
#define SB_CIRCULAR_QUEUE_HPP
namespace sb {
namespace cont {


/**
* @brief Circular Queue
* @author Spencer Banasik
* @details A stack allocated, iteratorless circular queue.
* This circular queue chooses to keep track of the start and the end,
* with both pointing to real elements. This means that the queue must always
* have one element to start.
* 
* An alternative is to have the end point to one-after the real end, like with
* ever other standard container, allowing for iterators. However, the circular 
* queue will then need to have some way of determining whether it is full or 
* empty, and to be compatible with STL iterators, that method requires an 
* empty buffer of space.
* 
* @invariant There will always be at least one element in the queue
*/
template<typename T, size_t S>
class CircularQueue {
public:

    /**
    * @brief Parameterized Constructor
    * @author Spencer Banasik
    * @details To satisfy the invariant there must always be one 
    * element in the queue. This ensures that.
    * @param [in] initial The initial value for the queue.
    */
    CircularQueue(T& initial) {
        my_data[start] = initial;
    }


    /**
    * @brief Back
    * @author Spencer Banasik
    * @returns A reference to the first element in the circular queue.
    */
    T& front() {
        return my_data[start];
    }

    /**
    * @brief Back
    * @author Spencer Banasik
    * @returns A reference to the last element in the circular queue.
    */
    T& back() {
        return my_data[end];
    }

    /**
    * @brief At
    * @author Spencer Banasik
    * @details Let I be index, S be start, C be capacity,
    * and R be return value.
    * (C + S + I) % C = R
    * (8 + 2 + 4) % 8 = 6
    * @param [in] idx The index.
    * @returns A reference to the element at that index.
    */
    T& at(size_t idx) {
        return my_data[(S + start + idx) % S]
    }

    /**
    * @brief Set
    * @author Spencer Banasik
    * @details Arbitrarily set an element of the queue
    * @param [in] elem The element set
    * @param [in] idx  The index of the element to be set
    * @returns Void
    */
    void set(T& elem, size_t idx) {
        my_data[(S + start + idx) % s] = elem;
    }

    /**
    * @brief At operator overload
    * @author Spencer Banasik
    * @details Let I be index, S be start, C be capacity,
    * and R be return value.
    * (C + S + I) % C = R
    * (8 + 2 + 4) % 8 = 6
    * @param [in] idx The index.
    * @returns A reference to the element at that index.
    */
    T& operator[](size_t idx){
        return my_data[(S + start + idx) % S]
    }

    /**
    * @brief Length
    * @author Spencer Banasik
    * @details Let C be capacity, E be end, S be start,
    * and L be length.
    * If E > S, E-S = L - 1
    * 7 - 0 = 8 - 1
    * If E < S, C+E-S = L - 1
    * 8 + 1 - 2 = 8 - 1
    * Universally, (C + E - S) % C = L - 1
    * @returns The number of elements in our circular queue.
    */
    size_t length() {
        return 1 + ((S + end - start) % S);
    }

    /**
    * @brief Push to front
    * @author Spencer Banasik
    * @details Pushes an element to the front of the queue,
    * moving the queue start back by one. Overwrites an element
    * if one was where the pushed element will be.
    * @param [in] elem The element to be pushed.
    * @returns A reference to the pushed element.
    */
    T& push_front(T& elem) {
        start = circular_decrement(start);
        my_data[start] = elem;

        if (end == start)
            end = circular_decrement(end);

        return my_data[start];
    }

    /**
    * @brief Push to back
    * @author Spencer Banasik
    * @details Pushes an element to the back of the queue,
    * moving the queue end forward by one. Overwrites an element
    * if one was where the pushed element will be.
    * @param [in] elem The element to be pushed.
    * @returns A reference to the pushed element.
    */
    T& push_back(T& elem) {
        end = circular_increment(end);
        my_data[end] = elem;

        if (end == start)
            start = circular_increment(start);

        return my_data[end];
    }

    /**
    * @brief Pop from front
    * @author Spencer Banasik
    * @details Pops an element from the front of the queue,
    * moving the queue start forward by one. Will not remove
    * the element if length is one.
    * @returns A copy of the popped element.
    */
    T pop_front() {
        if (length() == 1)
            return my_data[start];

        T& returned_var = my_data[start];
        start = circular_increment(start);

        return returned_var;
    }

    /**
    * @brief Pop from back
    * @author Spencer Banasik
    * @details Pops an element from the back of the queue,
    * moving the queue end backward by one. Will not remove
    * the element if length is one.
    * @returns A copy of the popped element.
    */
    T pop_back() {
        if (length() == 1)
            return my_data[start];

        T& returned_var = my_data[end];
        end = circular_decrement(end);

        return returned_var;
    }

    /**
    * @brief Data
    * @author Spencer Banasik
    * @returns A pointer to our data.
    */
    T* data() {
        return &my_data;
    }

private:

    /**
    * @brief Circular Inrecment
    * @author Spencer Banasik
    * @param [in] Start or end variable.
    * @returns The start or end variable, incremented by one according to the circular queue.
    * @private
    */
    size_t circular_increment(const size_t edge) {
        return (edge + 1) % 8
    }

    /**
    * @brief Circular Inrecment
    * @author Spencer Banasik
    * @param [in] Start or end variable
    * @returns The start or end variable, decremented by one according to the circular queue
    * @private
    */
    size_t circular_decrement(const size_t edge) {
        return (edge == 0) ? (S - 1) : (edge - 1);
    }

    T my_data[S];
    size_t start = 0;
    size_t end = 0;
};

}
}
#endif