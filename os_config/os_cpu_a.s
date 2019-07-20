; This file is part of "uC/OS-II port to dsPIC30 microcontroller"
; Copyright (C) 2004 Zoran Bosnjak <zoran.bosnjak at trio-b.si>
; 
; This program is free software; you can redistribute it and/or
; modify it under the terms of the GNU General Public License
; as published by the Free Software Foundation; either version 2
; of the License, or (at your option) any later version.

; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
; 
; You should have received a copy of the GNU General Public License
; along with this program; if not, write to the Free Software
; Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

; assembler part of dsPIC30 port

    .equ __30F6014, 1
    .include "p30f6014A.inc"

	.text
	
; save registers to curent stack (MACRO)
.macro save_regs
	push.d w0   ; w0 + w1
    push.d w2 
	push.d w4
	push.d w6
	push.d w8
	push.d w10 
	push.d w12
	push w14    ; don't push w15 (this is actual stack pointer)!!

	push ACCAL
	push ACCAH
	push ACCAU
	push ACCBL
	push ACCBH
	push ACCBU
	push TBLPAG
	push PSVPAG
	push RCOUNT
	push DCOUNT
	push DOSTARTL
	push DOSTARTH
	push DOENDL
	push DOENDH
	
	push SR
	push CORCON
	
.endm

; restore registers from the stack (MACRO)
.macro restore_regs

    pop CORCON
    pop SR
 
    pop DOENDH
    pop DOENDL
    pop DOSTARTH
    pop DOSTARTL
    pop DCOUNT
    pop RCOUNT
    pop PSVPAG
    pop TBLPAG
    pop ACCBU
    pop ACCBH
    pop ACCBL
    pop ACCAU
    pop ACCAH
    pop ACCAL

    pop w14     ; don't pop w15!!
    pop.d w12
    pop.d w10 
    pop.d w8
    pop.d w6
    pop.d w4
    pop.d w2 
    pop.d w0
.endm	

; -------------------------------------------
	.global _OSStartHighRdy
_OSStartHighRdy:
	call _OSTaskSwHook 		; call user definable hook

	; set OSRunning to TRUE
	mov #0x0001, w0
	mov.b wreg, _OSRunning

	; get stack pointer of the task to resume
	mov _OSTCBHighRdy, w0	; get index
	mov [w0], w15

	restore_regs 			; restore all registers from the stack
	
	retfie 					; return from interrupt
	
; -------------------------------------------
; context switch and interrupt context switch
; share some code (last part of the function is the same)
	.global _OSCtxSw
    .global _OSIntCtxSw
_OSCtxSw:
    ; TRAP (interrupt) should bring us here, not 'call'.
    ; Since dsPIC has no TRAP, correct stack to simulate interrupt.
    ; That means to save also SR and IPL3 to the stack, not just PC.
    mov.b SRL, wreg     ; load SRL
    sl w0, #8, w0       ; shift left by 8
    btsc CORCON, #IPL3  ; test IPL3 bit, skip if clear
    bset w0, #7;        ; ... (copy IPL3 to bit7 of w0)
    
    ior w0, [--w15], w0 ; merge bits
    mov w0, [w15++]     ; write back

	save_regs 			; save processor registers

	; save current task's stack pointer 
	; into the current task's OS_TCB
	mov _OSTCBCur, w0	; get index
	mov w15, [w0]
	; go on with OSIntCtxSw

_OSIntCtxSw:
	call _OSTaskSwHook ; call hook

    ; set high prio. task to current
    mov _OSTCBHighRdy, w1
    mov w1, _OSTCBCur
    mov.b _OSPrioHighRdy, wreg
    mov.b wreg, _OSPrioCur
    
    ; get new stack pointer
    mov [w1], w15   ; stack pointer from OSTCBHighRdy

    restore_regs 	; restore registers
	
	retfie 			; return from interrupt

; -------------------------------------------
; tick interrupt handler
    .global __T1Interrupt
__T1Interrupt:
	save_regs 				; save processor registers
	
	inc.b _OSIntNesting		; Call OSIntEnter() or increment OSIntNesting
	
	; if OSIntNesting==1, save stack pointer
    dec.b _OSIntNesting, wreg
    bra nz, 1f
    mov _OSTCBCur, w0
    mov w15, [w0]    
1:
    
    BCLR.b IFS0, #T1IF 		; clear int. device

    ; re-enable interrupts
    ; this should be on by default ??
    
    call _OSTimeTick
    call _OSIntExit
    
    restore_regs 			; restore registers

	retfie 					; return from interrupt

