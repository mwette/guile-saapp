/*
 */
#include <limits.h>
#include <stdlib.h>
#include <libguile.h>

extern void *_binary_dummy1_go_start
	__attribute__((section(".data")));
extern size_t *_binary_dummy1_go_size
	__attribute__((section(".data")));

static void kont(void *closure, int argc, char **argv) {
  char *ptr;
  size_t siz;
  SCM mem, res;
  SCM proc;

  ptr = _binary_dummy1_go_start;
  siz = *_binary_dummy1_go_size;
  mem = scm_c_take_typed_bytevector(ptr, siz, SCM_ARRAY_ELEMENT_TYPE_U8, 
                                    SCM_BOOL_F);

  //mod = scm_resolve_module("(system vm loader)");
  proc = scm_c_public_ref("(system vm loader)", "load-thunk-from-memory");
  res = scm_call_1(proc, mem);

  scm_shell(argc, argv);
}

int main(int argc, char **argv) {
  scm_boot_guile (argc, argv, kont, 0);
  return 0;
}

/* --- last line --- */
