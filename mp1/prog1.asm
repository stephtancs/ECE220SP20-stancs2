;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments

; Intro: In this MP we take the input string and compute the histogram for it, which is then printed to the screen
;		 The histogram code is provided to us, we needed to implement the Print hist part, which required us to
;		 calculate the offsets and then print to to screen with the character, space then the value of how many times
;		 the character repeated in the string. Then move the next line and do it all over again, until we reach Z.
;		 All the tests are correct after the testing!
;
; partners: stancs2, anudeep2, asanag2


PRINT_HIST	

			LD R5, HIST_ADDR    ; load the starting address of the histogram into R5
			LD R3, NUM_BINS     ; load the bin counter into R3

BIN_OUT		LD R2, AT_ASCIICODE ; load the ASCII value of @ into R2 to use it as an offset
			LD R6, HIST_ADDR    ; load the starting address of the histogram into R6
			NOT R6, R6			;
			ADD R6, R6, #1		;
			ADD R6, R5, R6      ; subtract R6 from R5 to obtain ASCII offset

LABEL_SPACE	ADD R0, R2, R6		; add the offset to the histogram starting address
			OUT  ; print out bin label
			LD R0, SPACE_ASCIICODE ; load the ASCII value for space and print out
			OUT; print out to screen

HIST_DATA	AND R0, R0, #0		; clear out R0
			AND R2, R2, #0		; clear out R2
			AND R4, R4, #0		; clear out R4
			AND R6, R6, #0		; clear out R6
			LD R6, NUM_OFFSET   ; Load ASCII numerical offset into R6
			LDR R1, R5, #0 		; load the data in the current histogram address into R1
			ADD R4, R4, #4 		; initialize digit counter

EACH_GROUP	ADD R2, R2, #4 		; initialize bit counter
			AND R0, R0, #0 		; clear out R0

EACH_BIT 	ADD R0, R0, R0 		; left shift digit holder
			ADD R1, R1, #0 		; check sign of test value
			BRzp TESTSHIFT
			ADD R0, R0, #1 		; add 1 to R0

TESTSHIFT 	ADD R1, R1, R1 		; left shift test value
			ADD R2, R2, #-1		; decrement bit counter
			BRp EACH_BIT		;

PRINT   	ADD R0, R0, #-9 	; subtract 9 from R0
			BRnz OFFSET
			ADD R0, R0, #7  	; add 7 to R0

OFFSET  	ADD R0, R0, #9  	; add back previously subtracted 9
			ADD R0, R6, R0 		; add ASCII offset to number
			OUT      			;
			ADD R4, R4, #-1 	; decrement digit counter
			BRp EACH_GROUP		; if postive, digits still

			LD R0, NEWLINE_CHAR	; print newline
			OUT					; print to screen
			ADD R5, R5, #1  	; increment histogram pointer
			ADD R3, R3, #-1		; decrement bin counter
			BRp BIN_OUT			; if pos, continue till Z
			BRnz DONE 			; done

DONE		HALT				; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
