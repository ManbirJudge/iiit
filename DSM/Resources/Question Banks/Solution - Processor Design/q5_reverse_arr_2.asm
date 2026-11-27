jumpd<u> MAIN

; --- multiplication ---
MULT:
    pop R0
    pop R1
    pop R2
    push R0

    ; R1 -> a
    ; R2 -> b
    ; R3 -> a*b

    movi R3, 0

    movs R1
    cmi 1
    jumpd<z> MULT_DONE
    
    movs R2
    cmi 1
    jumpd<z> MULT_DONE

MULT_LOOP:
    movs R3
    add R1
    movd R3

    movs R2
    sbi 1
    movd R2

    jumpd<nz> MULT_LOOP

    jumpd<u> MULT_DONE

MULT_DONE:
    movs R3
    movd R11
    ret<u>

; --- factorial ---
FACT:
    pop R0
    pop R1  ; -> n
    push R0

    movs R1
    sbi 1
    movd R2 ; -> n-1
    jumpd<z> FACT_BASE

    push R1  ; storing registers
    push R2

    push R2
    cd<u> FACT
    movs R11
    movd R3 ; -> (n-1)!

    pop R2  ; restoring registers
    pop R1

    push R1
    push R3
    cd<u> MULT
    ; result of MULT is the final result, it remain in R11

FACT_DONE:
    ret<u>

FACT_BASE:
    movi R11, 1
    jumpd<u> FACT_DONE

; --- main ---
MAIN:
    movi R5, 4
    push R5

    cd<u> FACT 

    movi R5, 100
    movs R5
    stor R11