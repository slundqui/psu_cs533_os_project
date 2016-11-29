#include <stdio.h>
#include "scheduler.h"

void print_nth_prime(void * pn) {
  int n = *(int *) pn;
  int c = 1, i = 1;
  while(c <= n) {
    ++i;
    int j, isprime = 1;
    for(j = 2; j < i; ++j) {
      if(i % j == 0) {
        isprime = 0;
        break;
      }
    }
    if(isprime) {
      ++c;
    }
    yield();
  }
  spinlock_lock(&printf_lock);
  printf("%dth prime: %d\n", n, i);
  spinlock_unlock(&printf_lock);
}

void print_n(void * n){
    yield();
    int nn = *(int * ) n;
    printf("%d\n", nn);
}


int main(void) {
  scheduler_begin();

  int n1 = 20000, n2 = 10000, n3 = 30000;
  thread_fork(print_nth_prime, &n1);
  thread_fork(print_nth_prime, &n2);
  thread_fork(print_nth_prime, &n3);

  scheduler_end();
}

