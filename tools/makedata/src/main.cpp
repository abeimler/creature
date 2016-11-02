#include <iostream>

#include <cxxopts.hpp>





int main(int argc, char* argv[]) {
  try {
    cxxopts::Options options(argv[0], " - creature_makedata command line options");

  } catch (const cxxopts::OptionException& e) {
    std::cout << "error parsing options: " << e.what() << std::endl;
    exit(1);
  }

  return 0;
}
