/*************************************************************/
/* Ex6-2 Try to use long jump into a function already closed */
/* 							     */
/* Author: David Ogor					     */
/* Date: 06-24-2015					     */
/*************************************************************/
#include <stdio.h>
#include <setjmp.h> 

jmp_buf env;

int func() {
  int res =  setjmp(env);
  printf("inside function\n");
  return res;
}

int func1(int a, int b) {
  printf("Inside function 1\n");
  return 1;
}

int main(int argc, char *argv[]) {
  int res = 0;
  res = func();

  switch (res) {
  case 0:
    printf("First jump\n");
    func1(1, 2);
    longjmp(env, 1);
    break;
  case 1:
    printf("Return from the first jump.\n");
    break;
  default:
    printf("Error encountered!\n");
  }

  return 0;
}
