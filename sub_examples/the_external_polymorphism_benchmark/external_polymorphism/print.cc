#include "print.hh"
//

void PrintImpl::print() const { asm volatile("" : : "r,m"(0) : "memory"); }
