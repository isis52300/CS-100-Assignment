#include <iostream>

#include "executor.h"
#include "executor.cpp"
#include "tokenizer.h"

using namespace std;

int main() {
  
   Executor* execute = new Executor();
   execute->execute();
  
    return 0;
}
