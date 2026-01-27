j MAIN___
main :
addi sp, sp -4
li t0, 4
sw t0, 0(sp)
lw a1, 0(sp)
li a0, 1
ecall
li a0, 11
li a1, 10
ecall
addi sp, sp 4
j END___
MAIN___ : 
call main
END___ :
addi sp, sp 0
