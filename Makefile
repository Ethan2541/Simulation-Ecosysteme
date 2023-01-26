CFLAGS = -g -Wall -Wextra -pedantic
CC = gcc

PROGRAMS = ecosys tests_ecosys

.PHONY:	all clean

all: $(PROGRAMS)


#tests_ecosys: ecosys.c main_tests.c main_ecosys.c
	#$(CC) -o $@ $(CFLAGS) $^


ecosys: ecosys.c main_ecosys.c
	$(CC) -g -o $@ $(CFLAGS) $^

tests_ecosys: ecosys.c main_tests.c
	$(CC) -g -o $@ $(CFLAGS) $^


#Ou plus simplement
#%.o:%.c %.h
#	$(CC)  $(GCC_FLAGS) -c  $<


clean:
	rm -f *.o *~ $(PROGRAMS)
