PROGRAM_NAME=GTKGraphicsTest
g++ `pkgconf gtkmm-3.0 --cflags --libs` -std=c++1z -c $PROGRAM_NAME.cpp
g++ $PROGRAM_NAME.o -o $PROGRAM_NAME.elf `pkgconf gtkmm-3.0 --cflags --libs`
rm -rf $PROGRAM_NAME.o
./$PROGRAM_NAME.elf
rm -rf $PROGRAM_NAME.elf
