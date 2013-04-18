CC = gcc
CFLAGS = -Wall -O3 -g

build: sn cn

sn:
	$(CC) sn.c -osn.exe $(CFLAGS)

cn:
	$(CC) cn.c -ocn.exe $(CFLAGS)

install: build
	cp cn.exe /usr/bin
	cp sn.exe /usr/bin

clean:
	-rm cn.exe
	-rm sn.exe

