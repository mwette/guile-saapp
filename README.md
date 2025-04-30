saapp, for stand-alone app, for guile

This is a work in progress.

create an executable guile w/ embedded modules

1. compile mydemo1.scm with 
   $ guild compile mydemo1.scm
2. run 
   $ ./findgos
   This generates mydemo1.gos
3. create the .xo (aka binary .elf) versions the .gos
   $ ./makexo mydemo1.gos
   This generates a populated xo.d/ directory
4. Build the binary:
   $ ./build


