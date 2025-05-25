/*
 * Copyright (C) 2025 Matthew Wette
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, see <http://www.gnu.org/licenses/>.
 *
 */
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <libguile.h>

/* provides loadem() */
#include "xo.d/xoload.ci"

static void kont(void *closure, int argc, char **argv) {
   loadem();
   //scm_ice_9_already_loaded = 1;
}

int main(int argc, char **argv) {
  scm_boot_guile (argc, argv, kont, 0);
  return 0;
}

/* --- last line --- */
