#include "fem.h"
#include "read_file.h"
#include <iostream>

int main() {

  Res input_files = read_file("fem2.inp");

  std::cout << fem(input_files) << std::endl;

  return 0;
}