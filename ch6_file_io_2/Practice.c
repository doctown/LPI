#include <unistd.h>
#include <stdio.h>

void env() {
  printf("%s\n", getenv("SHELL"));
}

int main(void) {
  env();

  return 0;
}
