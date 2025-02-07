#include <logs.h>

#include <iostream>


void test_f(void) {
  LOG_ERROR << "ERROR";
}

int main(void) {
  LOG_INFO << "INFO";
  test_f();
}