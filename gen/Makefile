.SUFFIXES: .c .o .S .s .linux .601

.s.o:
	gcc -c -o $@ $^

.s.linux:
	sed -e "s/@@INCLUDE@@/\"$<\"/g" < ../template/test_linux.S.template > $@.linux.S
	gcc -g -o $@ $@.linux.S

.s.601:
	sed -e "s/@@INCLUDE@@/\"$<\"/g" < ../template/test_860.S.template > $@.601.S
	gcc -nostdlib -Ttext=0x400000 -o $@.601.elf $@.601.S
	objcopy -O binary $@.601.elf -j .text -j .data $@

all: arith_test crbit_test

arith_test: arith_test.linux arith_test.601
	:

crbit_test: crbit_test.linux crbit_test.601
	:

arith_test.s:
	../src/gen_subf_test 23481 100 > $@

crbit_test.s:
	../src/gen_crbit_test > $@
