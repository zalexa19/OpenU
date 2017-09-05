; error example 2
; add cannot receive an intermidiate value as target operand
; MAIN label includes invlalid chars

MAIN%%: add r4, #4 
jmp MAIN

STR: .string "bla bla"
