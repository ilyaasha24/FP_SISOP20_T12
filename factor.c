#include "types.h"
#include "stat.h"
#include "user.h"

void
factor(char* str) {
  int n = atoi(str);
  if (!n) {
    printf(1, "factor: ‘%s’ is not integer greater than zero\n", str);
    return;
  }
  if (n == 1) {
    printf(1, "%d: 1\n", n);
    return;
  }

  printf(1, "%d: ", n);
  while (n % 2 == 0) { 
    printf(1, "%d ", 2); 
    n /= 2; 
  } 

  for (int i = 3; i <= (i > 4 ? n/2 : n) ; i += 2) {
    while (n % i == 0) 
    { 
      printf(1, "%d ", i); 
      n /= i; 
    } 
  } 

  if (n > 2) 
    printf (1, "%d ", n); 
printf(1, "\n"); 
}

int
main(int argc, char *argv[]) {
  if(argc <= 1) {
    char buf[512];
    while (1) {
      gets(buf, 512);
      factor(buf);
    }
    exit();
  }

  for(int i = 1; i < argc; i++) {
    factor(argv[i]);
  }
  exit();
}