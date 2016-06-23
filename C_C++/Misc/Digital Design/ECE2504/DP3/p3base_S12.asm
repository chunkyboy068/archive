; Thomas Yu * 04/17/2012
; Virginia Tech * ECE 2504 * Spring 2012
; Design Project 3
; 
; =====================================================================
; This Microchip-developed include file defines CPU registers such as 
; STATUS as 0x03, FSR 0x04, INDF 0x00, C (carry) bit 0x00, Z (zero) bit 
; 0x02, etc.
		include		P16F84.INC

; The '__CONFIG' directive is used to embed configuration data within .asm file.
; Here, we turn off the Watchdog Timer.
		__CONFIG	_WDT_OFF
 
; Some listing control directives
		list		p=16f84	; we are using the PIC 16f84 processor.
		title		"Design Project 3" 


; =====================================================================
; Program specific equate table
; These are user-defined equate statements naming symbolic labels
; specific to this program.
avg_val	equ		0x20		; address of average value (computed by this program)
max_val	equ		0x21		; address of maximum value (computed by this program)
num_arr	equ		0x30		; address of first item in data array 
total	equ		0x2f		; address of the sum of numbers in array
loopct	equ		0x2d		; address of the loop counter
temp1 	equ		0x22		; address of temporary location 1
temp2	equ		0x24		; address of temporary location 2
; =====================================================================
; Main program follows.
	
		org		0x00		; start program at program memory location 0

program_start

		movlw	0x08		;puts 8 into w
		movwf	loopct		;puts 8 into 0x2d
		movlw	num_arr		;puts the location of the first number in w
		movwf	FSR			;puts w into FSR
		movfw	num_arr		;places first number into w
		movwf	max_val		;the first number will always be the first max

loop
		movfw	INDF		;moves contents of address in INDF to w
		movwf	temp1		;moves data value to 0x22
		btfsc	temp1,7		;checks if 0x22 is negative
		call	neg_op		;negative operation to get total
		btfss	temp1,7		;checks if 0x22 is positive
		call	pos_op		;positive operation to get total

		call 	compute_max	;computs whether 0x21 or 0x22 is bigger
		incf	FSR			;increments FSR, now points to next number
		decfsz	loopct		;dec loop from 8 to 0, ends loop if zero
		goto loop

		call	compute_avg	;computes average value


last	goto	last		; infinite loop





compute_avg
		nop

		movlw	0x03	;moves literal value of 3 to w.  3 is the loop count
		movwf	loopct	;moves w to 0x2D
		movfw	total	;moves total to w
		movwf	temp1	;moves	w to 0x22
		bsf		STATUS,C;sets the carry bit to 1 in case it was zero before

loop1
		btfss	temp1,7	;checks positon 7 to see if set, skips if it is
		bcf		STATUS,C;if it is positive, then the carry bit needs to be cleared
		rrf		temp1	;rotate 0x22, essentially a division by 2
		bsf		STATUS,C;resets the carry bit
		decfsz	loopct	;dec the loop counter. if it hits zero, ends loop
		goto loop1

		movfw	temp1	;moves the final number, the average, to w
		movwf	avg_val	;moves w to the final register position
				
		movlw	0x00	;moves literal value of 0 to w
		movwf	total	;places 0 into 0x2f so that another average can be calculated

		return			; end of compute_avg, return




compute_max
		nop

		movfw	temp1	; moves new number to w
		movwf	temp2	; moves w to temp position 2 to preserve the number
		btfsc	max_val,7; test current max if negative, skip if it is
		goto 	cond3

		btfsc	temp1,7	;if the new number is negative
		goto	cond1	;goto condition 1
		goto	cond2	;goto condition 2

cond1
		btfss	max_val,7	;if the current max negative, skip next line
		goto 	endmax	
		btfsc	max_val,7	;if the current max is negative
		goto	cond2
cond2					
		comf	temp1	;begins 2's complement of F
		incf	temp1	;finishes 2's complement by increasing F by 1
		movfw	max_val	;moves current max into f
		addwf	temp1,1	;adds the two numbers and places back into 0x22
		btfss	temp1,7	;checks to see if the new number is negative
		goto 	endmax	;if not the current max is bigger
		movfw	temp2	;otherwise the new number is bigger and is moved into w
		movwf	max_val	;the new number is moved into max_val
		goto	endmax

cond3
		btfsc	temp1,7	;check new number if positive, if it is skip next
		goto	cond2
		movfw	temp1	;moves new number into w
		movwf	max_val	;the new number is positive and the current max negative, new becomes max
		goto	endmax
		
		
endmax		
		return			; end of compute_avg, return



neg_op					;this operation is used if a negative number is added
		nop
		
		movfw	temp1	;moves current number to w
		movwf	temp2	;moves w to 0x24
		decf	temp2	;begins to undo 2's complement. subtracts 1
		comf	temp2	;finishes undoing 2's complement by complementing 
		movfw	temp2	;moves value to w
		subwf	total,1	;subtracts w from the total, places back in total position

		return		



pos_op					;this operation is used if a positive number is added
		nop

		movfw	temp1	;the number is placed into w
		addwf	total,1	;w is added to total and placed back into the total position

		return



		end




