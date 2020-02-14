;
;
; This program evaluates expressions that are written in postfix notation.
; First, the program reads the input from the keyboard and echoes it onto the console.
; Operands are pushed into the stack and operators pop the last two values from the stack.
; If an invalid expression or operand is entered, an error message is printed to the console.
; stancs2, anudeep2, asanag2
.ORIG x3000
	
;your code goes here
	

INPUT                        ; Subroutine that takes character from keyboard and echoes it onto the console
      
    GETC
    OUT



    LD R1, EQUAL            ; if the character entered is =, then output the value of the expression
    NOT R1, R1
    ADD R1, R1, #1
    ADD R1, R1, R0
    BRz STACK_READ



    LD R1, SPACE            ; ignore spaces and go back to INPUT
    NOT R1, R1    
    ADD R1, R1, #1
    ADD R1, R1, R0
    BRz INPUT



    JSR EVALUATE
    BR INPUT



STACK_READ            
    
    LD R6, STACK_TOP
    LD R7, STACK_START



    NOT R7, R7
    ADD R7, R7, #2
    ADD R6, R7, R6             ; Check to see if the stack is empty



    BRnp OOPS



    JSR POP                    ; Pop the expression values from the stack
    ADD R5, R0, #0
    JSR PRINT_HEX
    BR FINITO



OOPS                        ; Display the error message if there is an invalid input



    LEA R0, INVALID
    PUTS



FINITO
    HALT



SPACE   .FILL x0020
EQUAL .FILL x003D
INVALID .STRINGZ "Invalid Expression!"



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R5- value to print in hexadecimal
PRINT_HEX
    
    LD R6, NUM_OFFSET         ; Load ASCII numerical offset into R6
    AND R4, R4, #0;
    ADD R4, R4, #4            ; Initialize digit counter



EACH_GROUP
    ADD R2, R2, #4            ; Initialize bit counter
    AND R0, R0, #0            ; clear out R0



EACH_BIT       
    ADD R0, R0, R0            ; left shift bit group holder
    ADD R5, R5, #0            ; Check sign of test value
    BRzp TESTSHIFT
    ADD R0, R0, #1



TESTSHIFT 
    ADD R5, R5, R5            ; left shift test value
    ADD R2, R2, #-1            ; decrement bit counter
    BRp EACH_BIT



PRINT    
    AND R3, R3, #0             
    ADD R3, R3, R0
    ADD R3, R3, #-9            ; Check to see if the character is numeric and alphabetic
    BRnz OFFSET



    ADD R0, R0, #7            ; If alphabetic, add extra offset of 7 to make sure letter will print



OFFSET    
    ADD R0, R6, R0    
    OUT      
    ADD R4, R4, #-1         ; decrement digit counter
    BRp EACH_GROUP
    HALT



NUM_OFFSET .FILL x0030
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R5 - current numerical output
;
;
EVALUATE                     ; subroutine that calls the rest of the subroutines that solve the expression



;your code goes here



    ST R6, SaveR6
    ST R7, SaveR7



NUMBER



    LD R6, INV_ZERO
    ADD R6, R6, R0
    BRn NOTNUM
    ADD R6, R6, #-9
    BRp NOTNUM
    
YESNUM



    LD R6, INV_ZERO
    ADD R0, R0, R6
    JSR PUSH
    BR DONEEVAL



NOTNUM    



    ADD R6, R0, #0              ; save R0 to R6



   JSR POP                    ; pop the first value
   ADD R4, R0, #0              ; store it in R4
   JSR POP                     ; pop the second value
   ADD R3, R0, #0              ; store it in R3
   ADD R5, R5, #0             ; check for underflow and branch back if there is a bad input or invalid expression
   BRnp OOPS              



   ADD R0, R6, #0              ; restore R0 from R6



    LD R6, INV_PLUS             ; check to see if the operator is a plus sign
    ADD R6, R6, R0
    BRnp #2
    JSR PLUS                 ; if so, perform the addition operation
    BR RESULT
    
    LD R6, INV_MINUS         ; check to see if the operator is a minus sign
    ADD R6, R6, R0
    BRnp #2
    JSR MIN                     ; if so, perform the subtraction operation
    BR RESULT



    LD R6, INV_MULT             ; check to see if the operator is a multiplication sign
    ADD R6, R6, R0
    BRnp #2
    JSR MUL                     ; if so, perform the multiplication operation
    BR RESULT



    LD R6, INV_DIV              ; check to see if the operator is a division sign
    ADD R6, R6, R0
    BRnp #2
    JSR DIV                     ; if so, perform the division operation
    BR RESULT



    LD R6, INV_EXP             ; check to see if the operator is an exponent sign
    ADD R6, R6, R0
    BRnp #2
    JSR EXP                     ; if so, perform the exponential operation
    BR RESULT
    
    BR OOPS



RESULT
   JSR PUSH                 ; Push R0 to stack
   ADD R5, R0, #0           ; Store R0 in R5



DONEEVAL
    LD R6, SaveR6
    LD R7, SaveR7
    RET



SaveR6 .BLKW #1
SaveR7 .BLKW #1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS                         ; Addition Subroutine
;your code goes here



    ADD R0, R3, R4
    RET
    
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN                             ; Subtraction Subroutine
;your code goes here
    
    NOT R4, R4
    ADD R4, R4, #1
    ADD R0, R3, R4
    RET
    
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4                
;out R0



MUL                         ; Multiplication Subroutine
;your code goes here
    
    ST R4, MUL_R4
    AND R0, R0, #0



PROD                          ; Repeated addition loop that performs the multiplication
    ADD R0, R0, R3
    ADD R4, R4, #-1            ; decrement counter of repeated addition
    BRp PROD



    LD R4, MUL_R4



    RET



MUL_R4 .BLKW #1



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0



DIV                             ; Division Subroutine
;your code goes here
    ST R2,DIV_R2            ; save R2
    ST R3,DIV_R3            ; save R3
    NOT R2,R4                
    ADD R2,R2,#1
    AND R0,R0,#0
    ADD R0,R0,#-1
DIV_LOOP                    ; repeated subtraction loop
    ADD R0,R0,#1
    ADD R3,R3,R2
    BRzp DIV_LOOP
    ADD R1,R3,R4
    LD R2,DIV_R2
    LD R3,DIV_R3
    RET



DIV_R2 .BLKW #1
DIV_R3 .BLKW #1
    
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here



   ST R3, EXP_SaveR3       ; save R3
   ST R4, EXP_SaveR4       ; save R4
   ST R5, EXP_SaveR5       ; save R5
   ST R7, EXP_SaveR7       ; save R7



   ADD R5, R4, #0          ; move the exponent to R5
   ADD R4, R3, #0          ; move the base to R4
   AND R3, R3, #0          ; set R3 to 1
   ADD R3, R3, #1
EXP_LOOP
   ADD R5, R5, #-1         ; decrement the power
   BRn EXP_DONE            ; multiply current total by the base if not negative
   JSR MUL                 ; store result of computation in R0
   ADD R3, R0, #0          ; put the result back in R3
   BR EXP_LOOP



EXP_DONE
   ADD R0, R3, #0          ; put the final result in R0



   LD R3, EXP_SaveR3
   LD R4, EXP_SaveR4
   LD R5, EXP_SaveR5
   LD R7, EXP_SaveR7
   RET



EXP_SaveR3      .BLKW #1
EXP_SaveR4      .BLKW #1
EXP_SaveR5      .BLKW #1
EXP_SaveR7      .BLKW #1

;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;

INV_ZERO        .FILL xFFD0 ;
INV_PLUS        .FILL xFFD5 ;
INV_MINUS       .FILL xFFD3 ;
INV_MULT       .FILL xFFD6 ;
INV_DIV         .FILL xFFD1 ;
INV_EXP         .FILL xFFA2 ;


.END
