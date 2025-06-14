#include <stdint.h>
namespace sb {
namespace cont {


/**
* @brief Circular Queue
* @author Spencer Banasik
* @details A stack allocated, iteratorless circular queue.
*/
template<typename T, size_t S>
class CircularQueue {
public:

    /**
    * @brief Back
    * @author Spencer Banasik
    * @returns A reference to the first element in the circular queue
    */
    T& front() {
        return my_data[start];
    }

    /**
    * @brief Back
    * @author Spencer Banasik
    * @returns A reference to the last element in the circular queue
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
    * @param [in] idx - The index
    * @returns A reference to the element at that index
    */
    T& at(size_t idx) {
        return my_data[(S + start + idx) % S]
    }

    /**
    * @brief At operator overload
    * @author Spencer Banasik
    * @details Let I be index, S be start, C be capacity,
    * and R be return value.
    * (C + S + I) % C = R
    * (8 + 2 + 4) % 8 = 6
    * @param [in] idx - The index
    * @returns A reference to the element at that index
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
    * @brief Empty
    * @author Spencer Banasik
    * @returns Whether the circular queue is empty or not.
    */
    bool empty() {
        return start == end;
    }

    T& push_front() {

    }

    T& push_back() {

    }

    T& pop_front() {

    }

    T& pop_back() {

    }

    /**
    * @brief Data
    * @author Spencer Banasik
    * @returns A pointer to our data
    */
    T* data() {
        return &my_data;
    }

private:

    /**
    * @brief Circular Inrecment
    * @author Spencer Banasik
    * @param [in] Start or end variable
    * @returns The start or end variable, incremented by one according to the circular queue
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