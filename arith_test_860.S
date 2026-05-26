	.text
	.globl puts
	.globl exit
	.globl print_hex
	.globl main

main:
	.include "arith_test.s"

	xor 3,3,3
	bl exit

print_hex:
	lis 4,string@h
	addi 4,4,string@l
	mr 7,4

	li 6,8
print_hex_loop:
	mr 5,3
	slwi 3,3,4

	srwi 5,5,28
	li 8,15
	and 5,5,8
	cmplwi 5,10
	blt digit
	addi 5,5,87
	b end_digit
digit:	
	addi 5,5,48
end_digit:	
	stb 5,0(4)
	addi 4,4,1

	subi 6,6,1
	cmplwi 6,0
	bne print_hex_loop

out_loop:
	lbz 3,0(7)
	cmplwi 3,0
	beq end_print
	
	addi 7,7,1
	lis 4,0x8000
	addi 4,4,0x3f8
	stb 3,0(4)
	b out_loop

end_print:
	blr

exit:
	b exit
	
	.data
string:
	.byte 48
	.byte 48
	.byte 48
	.byte 48
	.byte 48
	.byte 48
	.byte 48
	.byte 48
	.byte 10
	.byte 0
