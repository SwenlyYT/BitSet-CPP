#pragma once

#include <iostream>


template <size_t N = 8> // bits
class bitset {
private:
    uint8_t bytes[N / 8 + ((N % 8) > 0)] = {}; // bytes count = N/8 bytes + 1 byte if remainder more than 0; sets all bytes to 0
public:
    bitset() {
        
    }

    bitset(std::string str) {
        if (str.size() > N)
            throw "Array size cannot be more than 7";


        int index = 0;
        for (char ch : str) {
            if (ch < '0' or ch > '9')
                throw "Char can be only as number";


            if (ch != '0') {
                set(index, 1);
            }

            index++;
        }
    }

    bitset(char* str, size_t ARR_SIZE) {
        if (ARR_SIZE > N)
            throw "Array size cannot be more than bits count";


        for (size_t index = 0; index < ARR_SIZE; index++) {
            char ch = str[index];

            if (ch < '0' or ch > '9')
                throw "Char can be only as number";


            if (ch != '0') {
                set(index, 1);
            }
        }
    }

    // 0b0101, for set 0 index to 1 u can do 0b0101 | 0b1000
    void set(size_t index, bool value = true) {
        if (index >= N)
            throw "Index cannot be more than bits count";

        uint8_t byte = bytes[index / 8];
        uint8_t bit_index = index % 8;
        uint8_t bits_count = std::min((size_t) 7, (N - index) / 8 * 8 - 1); // bits count


        if (value) {
            byte |= (uint8_t)pow(2, bits_count - bit_index); // bits_count - bit_index for find the bit, which must to be true
            bytes[index / 8] = byte;
        }
        else
            reset(index);
    }

    // 0b0101, for set 1 index to 0 u can do 0b0101 & 0b1011
    void reset(size_t index) {
        if (index >= N)
            throw "Index cannot be more than bits count";

        uint8_t byte = bytes[index / 8];
        uint8_t bit_index = index % 8;
        uint8_t bits_count = std::min((size_t) 7, (N - index) / 8 * 8 - 1); // bits count

        uint8_t byteForOp = (pow(2, 8) - 1); // 0b11111111
        byteForOp -= pow(2, bits_count - bit_index); // 7-index for reverse index in binary

        byte &= byteForOp;
        bytes[index / 8] = byte;
    }

    bool get(uint8_t index) {
        uint8_t byte = bytes[index / 8];
        uint8_t bit_index = index % 8;

        return (byte << bit_index) & 0b10000000;
    }

    std::string to_string(size_t bits_count = N) {
        if (bits_count > N)
            throw "Provided bits count cannot be more than bits count in class init";
        else if (bits_count == 0)
            throw "Provided bits count cannot be equals 0";


        std::string result = "";

        size_t bytes_count = N / 8 + ((N % 8) > 0);
        size_t last_index = bytes_count - 1;

        for (size_t i = bits_count - 1; i >= 0; i--) {
            bool bit = get(i);
            result.insert(0, (bit == 0 ? "0" : "1"));

            if (i == 0) break;
        }

        return result;
    }
};