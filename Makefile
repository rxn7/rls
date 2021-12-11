all:
	gcc rls.c -o rls

install:
	make
	sudo cp ./rls /usr/bin/
