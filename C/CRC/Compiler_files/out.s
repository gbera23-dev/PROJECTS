addi sp, sp -4
li t0, 20
sw t0, 0(sp)
addi sp, sp -4
li t0, 0
sw t0, 0(sp)
addi sp, sp -4
li t0, 100
sw t0, 0(sp)
addi sp, sp -4
lw t5, 12(sp)
lw t6, 8(sp)
add t0, t5, t6
addi sp, sp -4
sw t0, 0(sp)
lw t5, 0(sp)
lw t6, 8(sp)
slt t0, t5, t6
addi sp, sp -4
sw t0, 0(sp)
lw t0, 0(sp)
sw t0, 8(sp)
addi sp, sp 8
lw t0, 0(sp)
beq t0, zero, L1
L0 :
lw t5, 8(sp)
li t6, 1
add t0, t5, t6
sw t0, 8(sp)
lw t5, 12(sp)
lw t6, 8(sp)
div t0, t5, t6
addi sp, sp -4
sw t0, 0(sp)
lw t5, 16(sp)
li t6, 1
add t0, t5, t6
sw t0, 16(sp)
lw t0, 0(sp)
addi sp, sp -4
sw t0, 0(sp)
lw a1, 0(sp)
li a0, 1
ecall
li a0, 11
li a1, 10
ecall
lw t5, 20(sp)
lw t6, 16(sp)
add t0, t5, t6
addi sp, sp -4
sw t0, 0(sp)
lw t5, 0(sp)
lw t6, 16(sp)
slt t0, t5, t6
addi sp, sp -4
sw t0, 0(sp)
lw t0, 0(sp)
sw t0, 16(sp)
addi sp, sp 8
addi sp, sp 8
L1 :
lw t0, 0(sp)
bne t0, zero L0
addi sp, sp 16
