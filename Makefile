

V8 = deps/v8/out/native/libv8.dylib
SRC = $(wildcard deps/*.cc)
SRC += src/v8stdio.cc
FLAGS = -Iinclude -Ideps -Ideps/v8/include

test:
	g++ $(V8) $(SRC) $(FLAGS) test.cc -o v8-stdio-test
	@v8-stdio-test
	@rm -rf v8-stdio-test
	@echo

build:
	@if test -d; then rm -rf out/ && mkdir out/; else mkdir out/; fi;
	g++ $(FLAGS) -fpic -c $(SRC)
	g++ $(V8) $(SRC) $(FLAGS) -shared -o out/libv8stdio.so


.PHONY: test build