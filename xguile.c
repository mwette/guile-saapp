/*
 */
#include <stdio.h>
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

SCM scm_load_thunk_from_memory(SCM);

//JGSKH_d
#if 0
extern char _binary_dummy1_go_start[];
extern char _binary_dummy1_go_end[];

static void kont(void *closure, int argc, char **argv) {
  char *ptr, *end;
  size_t siz;
  SCM mem, res;
  SCM load_thunk, mod_init;

  ptr = _binary_dummy1_go_start;
  end = _binary_dummy1_go_end;
  siz = end - ptr;
  mem = zcm_c_pointer_to_bytevector (ptr, siz);

#if 0
  load_thunk = scm_c_public_ref("system vm loader", "load-thunk-from-memory");
  mod_init = scm_call_1(load_thunk, mem);
#else
  mod_init = scm_load_thunk_from_memory(mem);
#endif
  res = scm_call_0(mod_init);

  scm_shell(argc, argv);
  //(*closure)();
}
#endif

#if 1
static void kont2(void *closure, int argc, char **argv) {
   printf("hello\n");
}
int main(int argc, char **argv) {
  scm_boot_guile (argc, argv, kont2, 0);
  return 0;
}
#else
int main(int argc, char **argv) {
  scm_boot_guile (argc, argv, kont, 0);
  return 0;
}
#endif

/* --- last line --- */
