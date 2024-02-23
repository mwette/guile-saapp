loneli app for guile: create an executable guile w/ embedded modules

foreach file $GO_FILES; do objcopy ... $file $(basname -s .go $file).xo; done
gcc -o app app.c loadem.c *.xo `pkg-config --cflags --libs guile-3.0`


