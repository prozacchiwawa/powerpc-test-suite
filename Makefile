.c.o:
	gcc -c -g -std=c99 -o $@ $^

.s.o:
	gcc -c -o $@ $^

all: gen_subf_test arith_test

gen_subf_test: gen_subf_test.o
	gcc -g -o $@ $^

arith_test: arith_test_linux arith_test.601
	:

arith_test.s: gen_subf_test
	./gen_subf_test 23481 100 > arith_test.s

arith_test_linux.S: arith_test.s
	:

arith_test_linux: arith_test_linux.o
	gcc -g -o $@ $^

arith_test.601: arith_test_860.o
	gcc -nostdlib -Ttext=0x400000 -o arith_test.601.elf arith_test_860.o
	objcopy -O binary arith_test.601.elf -j .text -j .data arith_test.601

