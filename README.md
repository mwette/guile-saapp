saapp, for sand-alone app, for guile

This is a work in progress.

create an executable guile w/ embedded modules

$ guild compile dummy1.scm 
$ ./cnvtgo dummy1.go
$ ./build
$ ./xguile
scheme@(guile-user)> ,use (dummy1)
scheme@(guile-user)> foo1
$1 = 123


