#include "fem.h"
#include <iostream>

int main() {

  std::cout << plate(10, 20, 1, 1000000) << std::endl;

  return 0;
}