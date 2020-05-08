#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char*
getline(int fd, char *buf, int max)
{
  int i, cc;
  char c;

  for(i = 0; i + 1 < max;) {
    cc = read(fd, &c, 1);
    if(cc < 1)
      break;
    buf[i++] = c;
    if(c == '\n' || c == '\r')
      break;
  }
  buf[i++] = '\0';
  return buf;
}

void
split(int fd, char *file)
{
  char buf[512], name[3] = "xaa";
  int l, fdt;
  
  do {
    getline(fd, buf, sizeof(buf));
    l = 0;
    if((fdt = open(name, O_CREATE | O_RDWR)) < 0) {
      printf(2, "split: cannot open %s\n", name);
      exit();
    }
    while (buf[0] != '\0' && l < 10) {
      // printf(1, "%d %s\n", l, buf);
      write(fdt, buf, sizeof(buf));
      l++;
      getline(fd, buf, sizeof(buf));
      // if ((l &= 1 && name[3]/2 == 0) || (l &= 0 && name[3]/2 == 1))
        // getline(fd, buf, sizeof(buf));
    }
    close(fdt);

    if (name[2] >= 'a' && name[2] <= 'z') {
      name[2]++;
    } else {
      name[1]++;
      name[2] = 'a';
    }

    // printf(1, "---------------%s---------------\n", name);
  } while (buf[0] != '\0');
  
}

int
main(int argc, char *argv[])
{
  int fd, i;
  if(argc <= 1) {
    // split(0, "");
    exit();
  }

  for(i = 1; i < argc; i++) {
    if((fd = open(argv[i], O_RDONLY)) < 0) {
      printf(2, "split: cannot open %s\n", argv[i]);
      exit();
    }
    split(fd, argv[i]);
    close(fd);
  }
  exit();
}
