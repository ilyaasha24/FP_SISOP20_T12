#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

void
truncate(int fd, int sz)
{
  char buf[512];
  int n, fdt;
  if ((fdt = open("tmp", O_CREATE | O_RDWR)) < 0) {
    printf(2, "truncate: cannot create temporary file");
    exit();
  }
  while ((n = read(fd, buf, sz < 512 ? sz : 512)) > 0) {
    sz -= n;
    write(fdt, buf, n);
  }
  if (sz) {
    char pad[sz];
    write(fdt, pad, sz);
  }
  close(fdt);
}

int
main(int argc, char *argv[]) {
  if(argc <= 1) {
    
    exit();
  }

  char prefix = 0, tmp[32];
  int fd, oldsize, size, n, i, j, lenarg2;
  oldsize = size = n = i = j = 0;
  struct stat ref, st;

  if (argv[++n][0] == '-') {
    switch (argv[n][1]) {
    case 's':
      lenarg2 = strlen(argv[++n]);
      if (argv[n][0] < '0' || argv[n][0] > '9') {
        prefix = argv[n][0];
        i++;
      }
    
      while (argv[n][i] >= '0' && argv[n][i] <= '9') {
        tmp[j] = argv[n][i];
        j++;
        i++;
      }
      size = atoi(tmp);

      j = lenarg2 - i;
      if (j) {
        switch (j) {
        case 1:
          switch (argv[n][i]) {
          case 'k':
          case 'K':
            size *= 1000;
            break;
          case 'm':
          case 'M':
            size *= 1000000;
            break;
          }
          break;
        case 2:
          if (argv[n][i+1] == 'B' || argv[n][i+1] == 'b') {
            switch (argv[n][i]) {
            case 'k':
            case 'K':
              size *= 1024;
              break;
            case 'm':
            case 'M':
              size *= 1048576;
              break;
            }
          }
          break;
        }
      }
      break;

    case 'r':
      stat(argv[++n], &ref);
      size = ref.size;
      break;
    }
  }

  if ((fd = open(argv[++n], O_RDONLY)) < 0) {
    printf(2, "truncate: cannot open %s\n", argv[n]);
    exit();
  }

  if (prefix) {  
    stat(argv[n], &st);
    oldsize = st.size;
    switch (prefix) {
    case '+':
      size = oldsize + size;
      break;
    case '-':
      size = oldsize - size;
      break;
    case '[': // '<' overwritten by file redirector
      if (oldsize < size) exit();
      break;
    case ']': // '>' overwritten by file redirector
      if (oldsize > size) exit();
      break;
    case '/':
      size = (oldsize / size) * size;
      break;
    case '%':
      if ((oldsize % size) > 0)
        size = ((oldsize / size) + 1) * size;
      else
        size = (oldsize / size) * size;
      break;
    }
  }

  truncate(fd, size);

  if(unlink(argv[n]) < 0)
    printf(2, "truncate: failed to delete %s\n", argv[n]);

  if(link("tmp", argv[n]) < 0)
    printf(2, "truncate: failed to rename tmp -> %s\n", argv[n]);

  if(unlink("tmp") < 0)
    printf(2, "truncate: failed to delete tmp\n");

  close(fd);
  exit();
}
