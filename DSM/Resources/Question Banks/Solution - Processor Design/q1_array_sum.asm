movi R0, 30
movs R0

load R1      ; R1 -> count
movi R0, 40  ; R0 -> pointer (reused for initial loading, array traversal and final storing)
movi R2, 0   ; R2 -> sum
             ; R3 -> current value

movs R1
ori 00
jumpd<z> DONE

LOOP:
movs R0
load R3

movs R2
add R3
movd R2

movs R0
adi 1
movd R0

movs R1
sbi 1
movd R1

jumpd<nz> LOOP

DONE:
movi R0, 70
movs R0
stor R2