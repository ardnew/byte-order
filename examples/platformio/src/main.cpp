#include <cstdint>
#include <iostream>

#include "bytes.hpp"

static const uint16_t word = 0x3412;
static const uint16_t swap = bytes::reorder(word);

int main(int argc, char *argv[]) {
  const uint16_t orig = bytes::reorder(swap);
  std::cout << std::hex;
  std::cout << "word = " << word << "\n";
  std::cout << "swap = " << swap << "\n";
  std::cout << "orig = " << orig << "\n";
  return 0;
}
