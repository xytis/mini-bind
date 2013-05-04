/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Mini Bind test
 *
 *        Version:  1.0
 *        Created:  05/04/2013 11:07:20 PM
 *       Revision:  none
 *       Compiler:  g++ -std=c++11
 *
 *         Author:  Vytis Valentinavičius (), vytis.valentinavicius@gmail.com
 *        Company:  Nolife4Life
 *
 * =====================================================================================
 */

#include <iostream>
#include "minibind.hpp"

void f0 () {
  std::cout << " executing f0 with no params" << std::endl;
}

void f1 (int p1) {
  std::cout << " executing f1 with p1=" << p1 << std::endl;
}

void f2 (int p1, int p2) {
  std::cout << " executing f2 with p1=" << p1 << " p2=" << p2 << std::endl;
}

void f3 (int p1, int p2, int p3) {
  std::cout << " executing f3 with p1=" << p1 << " p2=" << p2 << " p3=" << p3 << std::endl;
}

int sum (int a, int b) {
  return a + b;
}

int main(int argc, const char * argv[]) {
  bind<void>(&f0)();
  bind<void>(&f1, _1)(1);
  bind<void>(&f2, _2, _1)(2,1);
  bind<void>(&f3, 1, 2, 3)();
  bind<void>(&f3, _1, _1, _1)(0);
  for (int i = 0; i < 5; ++i) {
    std::cout << "Sum of 1 + " << i << " is " << bind<int>(&sum, 1, _1)(i) << std::endl;
  }
}
