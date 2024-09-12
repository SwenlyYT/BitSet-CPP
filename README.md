# BitSet-C-

Include
```c++
#include "BitSet.h"
```

Example
```c++
bitset<8> byte = bitset<8>("00000001");

std::cout << sizeof(byte) << '\n'; // 1

byte.set(1);
byte.set(2);

std::cout << byte.to_string() << '\n'; // 01100001

byte.reset(2);

std::cout << byte.to_string() << '\n'; // 01000001

byte.set(2);
byte.set(5);
byte.reset(0);

std::cout << byte.to_string() << '\n'; // 01100101
```
