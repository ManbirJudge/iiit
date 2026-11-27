movi R0, 30
movs R0
load R5

; R1 -> mult res
; R2 -> a1
; R3 -> a2
; R0, R4 -> tmp
; R5 -> N
; R11 -> return val

jumpd<u> MAIN

FACT:
    pop R0  ; <- n
    movs R0 ; [AR] <- n
    movd R2 ; <- n
    sbi 1   ; [AR] <- (n-1)
    jumpd<z> FACT_BASE_CASE

    movs R0 ; <- n-1
    push R0 ; push (n-1)
    cd<u> FACT

    movs R11
    movd R3 ; <- fact(n-1)

    cd<u> MUL
    movs R1
    movd R11 ; <- fact(n)
    
    ret<u>

FACT_BASE_CASE:
    movi R11, 1
    ret<u>

MUL:
    movi R1, 0

MUL_LOOP:
    movs R1
    add R2
    movd R1

    movs R3
    sbi 1
    movd R3

    jumpd<nz> MUL_LOOP

    ret<u>

MAIN:
    push R5
    call<u> FACT

    movi R0, 70
    movs R0
    stor R11