movi R0, 30
movs R0

load R1       ; R1 -> count
movi R0, 40   ; R0 -> pointer (reused for initial loading, array traversal and final storing)
movi R2, 0    ; R2 -> max
movi R3, 255  ; R3 -> min
              ; R4 -> cur val

movs R1
ori 00
jumpd<z> DONE

LOOP:
movs R0
load R4

movs R4

cmp R2
jumpd<p> NEW_MAX

cmp R3
jumpd<n> NEW_MIN

NEW_MAX:
movs R4
movd R2
jumpd<u> NXT

NEW_MIN:
movs R4
movd R3

NXT:
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

movi R0, 71
movs R0
stor R3

stop