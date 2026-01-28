j MAIN___
IlovePointers :
lw a1, 0(sp)
li a0, 1
ecall
li a0, 11
li a1, 10
ecall
addi sp, sp -4
lw t0, 8(sp)
lw t0, 0(t0)
addi sp, sp -4
sw t0, 0(sp)
lw t0, 0(sp)
sw t0, 4(sp)
addi sp, sp 4
lw a1, 0(sp)
li a0, 1
ecall
li a0, 11
li a1, 10
ecall
addi sp, sp -4
lw t0, 16(sp)
lw t0, 0(t0)
addi sp, sp -4
sw t0, 0(sp)
lw t0, 0(sp)
sw t0, 4(sp)
addi sp, sp 4
addi sp, sp -4
lw t0, 4(sp)
lw t0, 0(t0)
addi sp, sp -4
sw t0, 0(sp)
lw t0, 0(sp)
sw t0, 4(sp)
addi sp, sp 4
lw a1, 0(sp)
li a0, 1
ecall
li a0, 11
li a1, 10
ecall
addi sp, sp 12
ret
main :
addi sp, sp -4
li t0, 1
sw t0, 0(sp)
addi sp, sp -4
addi t0, sp, 4
addi sp, sp -4
sw t0, 0(sp)
lw t0, 0(sp)
sw t0, 4(sp)
addi sp, sp 4
addi sp, sp -4
li t0, 5
sw t0, 0(sp)
addi sp, sp -4
addi t0, sp, 4
addi sp, sp -4
sw t0, 0(sp)
lw t0, 0(sp)
sw t0, 4(sp)
addi sp, sp 4
addi sp, sp -4
addi t0, sp, 4
addi sp, sp -4
sw t0, 0(sp)
lw t0, 0(sp)
sw t0, 4(sp)
addi sp, sp 4
addi sp, sp -4
addi sp, sp -4
addi sp, sp -4
sw ra, 0(sp)
lw t0, 4(sp)
addi sp, sp -4
sw t0, 0(sp)
lw t0, 12(sp)
addi sp, sp -4
sw t0, 0(sp)
lw t0, 20(sp)
addi sp, sp -4
sw t0, 0(sp)
lw t0, 28(sp)
addi sp, sp -4
sw t0, 0(sp)
lw t0, 44(sp)
addi sp, sp -4
sw t0, 0(sp)
call IlovePointers
addi sp, sp 20
lw ra, 0(sp)
addi sp, sp 4
addi sp, sp 28
j END___
MAIN___ : 
call main
END___ :
addi sp, sp 0
