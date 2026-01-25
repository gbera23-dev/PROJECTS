j MAIN___
hello :
addi sp, sp -4
li t0, 6
sw t0, 0(sp)
lw a1, 0(sp)
li a0, 1
ecall
li a0, 11
li a1, 10
ecall
addi sp, sp 4
ret
main :
addi sp, sp -4
li t0, 3
sw t0, 0(sp)
addi sp, sp -4
li t0, 5
sw t0, 0(sp)
lw t5, 4(sp)
lw t6, 0(sp)
add t0, t5, t6
addi sp, sp -4
sw t0, 0(sp)
lw a1, 0(sp)
li a0, 1
ecall
li a0, 11
li a1, 10
ecall
addi sp, sp -4
li t0, 100
sw t0, 0(sp)
lw t0, 0(sp)
beq t0, zero, L1
L0 :
lw a1, 0(sp)
li a0, 1
ecall
li a0, 11
li a1, 10
ecall
lw t5, 0(sp)
li t6, 1
sub t0, t5, t6
sw t0, 0(sp)
addi sp, sp 0
L1 :
lw t0, 0(sp)
bne t0, zero L0
addi sp, sp -4
sw ra, 0(sp)
call hello
addi sp, sp 0
lw ra, 0(sp)
addi sp, sp 4
addi sp, sp 16
j END___
MAIN___ : 
call main
END___ :
addi sp, sp 0
