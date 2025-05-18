// Spencer Banasik
// Basic bit manipulation operations
// for bit packing
#ifndef SB_BIT_MANIP_HPP
#define SB_BIT_MANIP_HPP

#include <stdint.h>

namespace sb {
namespace bmanip {

    // This module will contain functions to perform bit manipulation options on bytes
    // We should support: uint8, uint16, uint32, uint64
    // Instead of function overloading we'll use prefixes such as c_set_bit or ll_set_bit

    // TODO:
    // Bounds checking
    // Access an arbitrary bit
    // Set an arbitrary bit (function for setting 0, setting 1, toggling, or either)
    // AND, OR, and XORing arbitrary bits
    // Applying above getters and setters to a range of bits
    // Applying the above setters to everything besides a bit
    
    // See how many 1's or 0's are in a bit

    // Reversing bits
    // Reversing bit order at a byte level (hotns)
    // Wrapping bit shifts
    
    // Converting a binary string to a bitpacked number
    // Converting a number to a binary string
    // Printing binary rendition of a number

    // Format:
    // datatype_operation_range
    // u8_set_bit
    // u16_xor_range
    // u64_and_allbut



}
}
#endif
