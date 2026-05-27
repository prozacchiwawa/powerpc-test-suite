.c.o:
	gcc --std=c99 -c -o $@ $^

all: gen_subf_test gen_crbit_test

gen_subf_test: gen_subf_test.o lfsr.o instruction.o register.o

gen_crbit_test: gen_crbit_test.o lfsr.o instruction.o register.o


