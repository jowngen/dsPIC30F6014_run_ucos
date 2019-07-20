; This is dummy task for testing purposes.
; It writes zeros to some working registers,
; just to see that this does not affect 
; other tasks (every task lives in it's own context).

    .equ __30F6014, 1
    .include "p30f6014A.inc"

	.text

; -------------------------------------------   
    .global _dummy_task
_dummy_task:

    ; write zeros to some registers
1:
    .irp reg,0,1,2,3,4,5,6,7,8,9,10,11,12,13
    clr w\reg
    .endr
    bra 1b
    
