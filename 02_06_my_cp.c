#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int fd_src, fd_dst;
  caddr_t addr_src, addr_dst;
  struct stat filestat;

  fd_src = open(argv[1], O_RDONLY);
  fd_dst = open(argv[2], O_RDWR | O_CREAT);

  // get size of src file
  fstat(fd_src, &filestat);

  // make dst file size same as src
  lseek(fd_dst, filestat.st_size - 1, SEEK_SET);
  write(fd_dst, "", 1);

  // copy through shared memory
  addr_src = mmap((caddr_t)0, filestat.st_size, PROT_READ, MAP_SHARED, fd_src, 0);
  addr_dst = mmap((caddr_t)0, filestat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_dst, 0);
  memcpy(addr_dst, addr_src, filestat.st_size);
  exit(0);
}
