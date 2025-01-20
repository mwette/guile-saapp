/*
 */
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <libguile.h>

/* provides loadem() */
#include "xo.d/xoload.ci"

static void kont(void *closure, int argc, char **argv) {
   loadem();
}

int main(int argc, char **argv) {
  scm_boot_guile (argc, argv, kont, 0);
  return 0;
}

/* --- last line --- */
