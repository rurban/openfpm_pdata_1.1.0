include ../../example.mk

CC=mpic++

LDIR =

OBJ = main.o update_new.o

%.o: %.f90
	mpif90 -ffree-line-length-none -fno-range-check -fno-second-underscore  -fimplicit-none  -mavx -O3 -c -g -o $@ $<

%.o: %.cpp
	$(CC) -O3 -mavx  -g -c --std=c++11 -Wno-ignored-attributes  -o  $@ $< $(INCLUDE_PATH) -I/where/is/vc/installation/include

gray_scott: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS_PATH) $(LIBS) -L/where/is/vc/installation/lib  # -lVc (Add -lVc if you use VCDevel)

all: gray_scott

run: all
	mpirun -np 4 ./gray_scott

.PHONY: clean all run

clean:
	rm -f *.o *~ core gray_scott

