#pragma once
#include <concepts>
//TODO: llvm, clang -> clangd

#include <vector>

std::vector<bool> b;

template <std::integral T = char>
struct BitProxy {
    T& ref;
    size_t idx;

    BitProxy& operator=(bool val) {
        if(val){
            ref |= (1 << idx);
            ////////
            // 00001 << 3
            // 01000

            // 00101
            //|
            // 01000
            //=
            // 01101
        }
        else{
            ref &= ~(1 << idx);
            ////////
            // 00001 << 3
            // 01000
            // ~
            // 10111

            // 01101
            //&
            // 10111
            //=
            // 00101
        }
        return *this;
    }

    operator bool() const {
        return (ref >> idx) & 1;
    }
};

template <std::integral T>
struct Bit {
private:
    static constexpr size_t _sz {sizeof(T)};
    T value;
    size_t idx;
    using Proxy = BitProxy<T>;
public:
    Bit(const Bit& b) = default;
    constexpr Bit(T o) : value(o) {}
    
    T operator[](size_t idx) const {
        return (value >> idx) & 1;
    }

    Proxy operator[](size_t idx) {
        return Proxy{value, idx};
    }
};



