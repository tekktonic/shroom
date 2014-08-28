CFLAGS = `pkg-config --cflags sdl2 SDL2_image` -Iinc -std=c11 -Wall -Wextra -pedantic -g -pg -fprofile -ftest-coverage
LDFLAGS = `pkg-config --libs sdl2 SDL2_image jansson` -lm -g -pg -fprofile -ftest-coverage

TESTABLE = src/dtype.o src/err.o src/tonic.o
NONMAIN = $(TESTABLE) src/resourcemanager.o src/sprite.o src/window.o
OBJFILES = src/main.o $(NONMAIN)

all: $(OBJFILES)
	$(CC) $(LDFLAGS) $(OBJFILES) -o shroom

clean:
	find . -name "*~" -exec rm {} \;
	find . -name "*.o" -exec rm {} \;
	find . -name "*.gcno" -exec rm {} \;
	find . -name "*.out" -exec rm {} \;
	find . -name "1" -exec rm {} \;
	if [ -e test ]; then rm test; fi;
	if [ -e squid ]; then rm squid; fi;

test: clean tests/test.o tests/test_dtype.h $(TESTABLE)
# err is sufficiently stupid that it doesn't need to be tested.
	$(CC) $(LDFLAGS) -lcunit tests/test.o $(TESTABLE) -o test

test_run: test
	./test
