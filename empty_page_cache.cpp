#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

// Clear `filename' from page cache.
// based on https://alg-eng.blogspot.com/?m=1
void empty_page_cache(const char *filename) {
  const int fd = open(filename, O_RDWR);
  if (fd == -1) {
    std::cerr << "Error opening " << filename << "\n";
    std::exit(EXIT_FAILURE);
  }
  const off_t length = lseek(fd, 0, SEEK_END);
  lseek(fd, 0L, SEEK_SET);
  posix_fadvise(fd, 0, length, POSIX_FADV_DONTNEED);
  close(fd);
}

int main(int argc, char **argv) {
  if (argc != 2) {
	std::cout << "Usage: " << argv[0] << " FILE\n" << std::endl;
	std::exit(EXIT_FAILURE);
  }
  empty_page_cache(argv[1]);
}

