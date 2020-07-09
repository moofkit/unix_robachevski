#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  struct stat filestat;
  char *ptype;
  lstat (argv[1], &filestat);
  if(S_ISREG(filestat.st_mode)) ptype = "file";
  else if(S_ISDIR(filestat.st_mode)) ptype = "dir";
  else if(S_ISLNK(filestat.st_mode)) ptype = "symlink";
  else if(S_ISCHR(filestat.st_mode)) ptype = "char special";
  else if(S_ISBLK(filestat.st_mode)) ptype = "block device";
  else if(S_ISSOCK(filestat.st_mode)) ptype = "socket";
  else if(S_ISFIFO(filestat.st_mode)) ptype = "FIFO";
  else ptype = "unknown";

  printf("type = %s\n", ptype);
  printf("size = %d\n", filestat.st_size);
  printf("permissions = %o\n", filestat.st_mode);
  printf("inode = %d\n", filestat.st_ino);
  printf("nlink = %d\n", filestat.st_nlink);
  printf("dev = (%d, %d)\n", major(filestat.st_dev), minor(filestat.st_dev));
  printf("UID = %d\n", filestat.st_uid);
  printf("GID = %d\n", filestat.st_gid);
  printf("rdev = (%d, %d)\n", major(filestat.st_rdev), minor(filestat.st_rdev));
  printf("lastaccess = %s\n", ctime(&filestat.st_atime));
  printf("modified = %s\n", ctime(&filestat.st_mtime));
  printf("metamodified = %s\n", ctime(&filestat.st_ctime));
}
