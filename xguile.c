/*
 */
#include <limits.h>
#include <stdlib.h>
#include <libguile.h>

SCM zcm_c_pointer_to_bytevector(void *pointer, size_t size) {
  SCM ptr, len, mem;

  ptr = scm_from_pointer(pointer, NULL);
  len = scm_from_size_t(size);
  mem = scm_pointer_to_bytevector(ptr, len, SCM_UNDEFINED, SCM_UNDEFINED); 
  return mem;
}

extern char _binary_dummy1_go_start[];
extern char _binary_dummy1_go_end[];

static void kont(void *closure, int argc, char **argv) {
  char *ptr, *end;
  size_t siz;
  SCM mem, res;
  SCM proc;

  ptr = _binary_dummy1_go_start;
  end = _binary_dummy1_go_end;
  siz = end - ptr;
  mem = zcm_c_pointer_to_bytevector (ptr, siz);

  proc = scm_c_public_ref("system vm loader", "load-thunk-from-memory");
  res = scm_call_1(proc, mem);

  scm_shell(argc, argv);
}

int main(int argc, char **argv) {
  scm_boot_guile (argc, argv, kont, 0);
  return 0;
}

/* --- last line --- */
