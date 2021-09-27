all: copy object.o move clean way_home

copy:
	mkdir obj
	cp inc/*.h obj
	cp src/*.c obj

object.o:
	clang -std=c11 -Wall -Wextra -Werror -Wpedantic -c obj/*.c

move:
	cp *.o obj

clean:
	rm *.o
	rm obj/*.h
	rm obj/*.c

way_home:
	clang -std=c11 -Wall -Wextra -Werror -Wpedantic -o way_home obj/*.o

uninstall:
	rm -rf obj
	rm way_home
	rm -rf *.o

reinstall:
	make uninstall
	make