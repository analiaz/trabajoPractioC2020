#
# Compilers
#
CC = gcc
#CC=g++

#
# exes
#
#EXE0=main-files
EXE0=test-props
EXE1=main-test
EXE2=read-write-matrix

#
# Flags
#
CFLAGS=-Wall -std=c99 -g 
#CFLAGS=-Wall -std=c99 -G

#
# Libs + Incs
#
#MYLIBDIR=-Llib
#lib=ABC
#INC=-IA -B -C
INC=-I. -Ilist

#   
# set object files   
#   
OBJ0=$(EXE0).o
OBJ1=$(EXE1).o
OBJ2=$(EXE2).o

#
# Other objects
#
OOBJS=error-mat.o mat.o list/list.o
EOBJS=

#
# SRC
#
HEADERS=error-mat.h mat.h list/list.h
FILE0=test7.m

-include dummy

.PHONY: clean all splash

## make all
all: $(EXE0) $(EXE1) $(EXE2)

# make main
$(EXE0): $(OBJ0) $(OOBJS) 
	$(CC) $(CFLAGS) $(INC) $(OBJ0) $(OOBJS) $(MYLIBDIR) $(lib) -o $@

$(EXE1): $(OBJ1) $(OOBJS) 
	$(CC) $(CFLAGS) $(INC) $(OBJ1) $(OOBJS) $(MYLIBDIR) $(lib) -o $@

$(EXE2): $(OBJ2) 
	$(CC) $(CFLAGS) $(OBJ2) -o $@

# Old-fashioned suffix rule (cannot have any prerequisites of their own)
#.c.o: $(HEADERS)
# New-fashioned pattern rule (not posix 2 compliant)
%.o: %.c $(HEADERS) 
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f *.o $(EXE0) $(EXE1) $(EXE2) *.i a.out core $(OOBJS)

dummy: Makefile
	@touch $@
	@$(MAKE) -s clean

splash:
	rm -f *~ list/*~

test: $(EXE0) $(FILE0)
#	./$(EXE0) --invalid $(FILE0)
	./$(EXE0) --in1 $(FILE0)
#	./$(EXE0) --1 $(FILE0)
	./$(EXE0) -1 $(FILE0)

#memtest: $(EXE0) $(FILE0)
#	valgrind --leak-check=full ./test-props --in1 test7.m 
#	valgrind --leak-check=full ./main-test < test7.m

### EOF ###
