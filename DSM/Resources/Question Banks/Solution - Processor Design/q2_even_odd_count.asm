movi R0, 30
movs R0

load R1      ; R1 -> count
movi R0, 40  ; R0 -> pointer
movi R2, 0   ; R2 -> even
movi R3, 0   ; R3 -> odd 
movi R4, 0   ; R4 -> zero 
             ; R5 -> current value

movs R1
ori 00
jumpd<z> DONEDONE

LOOP:
movs R0
load R5
movs R5
ori 0

jumpd<z> ZERO
jumpd<op> ODD

EVEN:
movs R2
adi 1
movd R2
jumpd<u> DONE

ODD:
movs R3
adi 1
movd R3
jumpd<u> DONE

ZERO:
movs R4
adi 1
movd R4

DONE:
movs R0
adi 1
movd R0

movs R1
sbi 1
movd R1

jumpd<nz> LOOP

DONEDONE:
movi R0, 70
movs R0
stor R2

movi R0, 71
movs R0
stor R3

movi R0, 72
movs R0
stor R4

stop