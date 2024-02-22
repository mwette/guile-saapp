/*
 */
#include <limits.h>
#include <stdlib.h>
#include <libguile.h>

//extern char* _binary_dummy1_go_start[_binary_dummy1_go_size];
//extern char _binary_dummy1_go_start[100];
extern char _binary_dummy1_go_start[];
extern char _binary_dummy1_go_end[];

char *abc = "abc";

static void kont(void *closure, int argc, char **argv) {
  char *ptr, *end;
  size_t siz;
  SCM mem, res;
  SCM proc;

  ptr = _binary_dummy1_go_start;
  end = _binary_dummy1_go_end;
  siz = end - ptr;
#if 0
  ptr = _binary_dummy1_go_start;
  end = _binary_dummy1_go_end;
  siz = _binary_dummy1_go_end - _binary_dummy1_go_start;

  siz = *_binary_dummy1_go_size;
  mem = scm_c_take_typed_bytevector(ptr, siz, SCM_ARRAY_ELEMENT_TYPE_U8, 
                                    SCM_BOOL_F);

  //mod = scm_resolve_module("(system vm loader)");
  proc = scm_c_public_ref("(system vm loader)", "load-thunk-from-memory");
  res = scm_call_1(proc, mem);

#endif
  scm_shell(argc, argv);
}

int main(int argc, char **argv) {
  scm_boot_guile (argc, argv, kont, 0);
  return 0;
}

/* --- last line --- */
