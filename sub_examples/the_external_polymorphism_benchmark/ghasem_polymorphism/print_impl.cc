#include <print_interface.hh>

void PrintInterface::print() const { asm volatile("" : : "r,m"(0) : "memory"); }
