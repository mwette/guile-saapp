/*
#   _binary_${1}_go_start
#   _binary_${1}_go_size
#   _binary_${1}_go_end

 */
#include <limits.h>
#include <stdlib.h>
#include <libguile.h>
#include "<elf.h>"

static void loadem(char *argv0) {
  char pbuf[2048], *path;
  off_t end;
  char *data;

  path = realpath(argv0, pbuf);
  fd = open(path, O_RDONLY);
  end = lseek (fd, 0, SEEK_END);
  data = mmap (NULL, len, PROT_READ, MAP_PRIVATE, fd, 0);
  (void) close (fd);

  header = (Elf_Ehdr*) data;
  /* get symbol table */
  /* find above and call load_thunk_from_memory() on those */
}

/* --- last line --- */
