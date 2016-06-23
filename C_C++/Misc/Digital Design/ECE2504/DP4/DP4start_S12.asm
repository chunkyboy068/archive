; Thomas Yu 
; Virginia Tech * ECE 2504 * Spring 2012
; Design Project 4:  Vending Machine Controller
; April 28, 2012
; 
; The algorithm used to compute the change and when to dispense consists of
; several conditions that need to be satisfied.  Initially, the coin that is
; inserted is checked.  Since each coin input places a different value in inval,
; inval is checked to see which coin is inserted.  Based on this, a different 
; subroutine is called to calculate the total coins. The next subroutine is
; then called to check whether enough money has been inserted by simply
; subracting the cost from the total inerted.  Depending on this, the dispense
; subroutine is called to calculate change through subtraction.  After change
; is returned, the dispense subroutine then dispenses a snickers bar and returns
; to waiting for input.  An additional subroutine, return-coins, is used when
; the coin return is pressed or a penny is inserted.
; =====================================================================
; This Microchip-developed include file defines CPU registers such as 
; STATUS as 0x03, FSR 0x04, INDF 0x00, C (carry) bit 0x00, Z (zero) bit 
; 0x02 ...
        include P16F84.INC
; =====================================================================
; turn off the watchdog timer to fix odd behavior on long runs.
 	__CONFIG _HS_OSC&_WDT_OFF&_PWRTE_ON&_CP_OFF 

; Program specific equate table
; These are user-defined equate statements naming symbolic labels
; specific to ths program.

coinreturn      equ     1       ; coin return button sets PORTB bit1
penny           equ     2       ; inserting a penny sets PORTB bit2
nickel          equ     3       ; inserting a nickel sets PORTB bit3
dime            equ     4       ; inserting a dime sets PORTB bit4
quarter         equ     5       ; inserting a quarter sets PORTB bit5
dollar			equ		6		; inserting a dollar sets PORTB bit6
numloops		equ		0x03	; used for delay loop
enough          equ     0x46    ; cost of a Snickers bar is $0.80

; Define output locations
; these definitions are supplied to the user and must not be modified
change_ret	equ	0x10	; write 0x10 to this location to return a quarter, 
						; 0x08 to return a dime, 0x04 to return a nickel
coin_return	equ	0x11	; write 0x02 to this location to return all coins inserted
snickers	equ 0x12	; write 0xFF to this location to dispense a Snickers

; Define the data storage locations
; these definitions are supplied to the user and must not be modified
inval		equ 0x20	; the last port value read by the ISR
semaphore	equ 0x21	; an indicator that a value has been loaded into inval
_wstore     equ 0x22 	; a location to hold w during interrupt service routine
totalcoins	equ	0x23	; total currency inserted so far (cents)
change		equ	0x24	; amount of change to be returned
holdcount	equ 0x25	; used for delay loop

; =====================================================================
temp1		equ	0x13	;location of snickers cost
; =====================================================================


; Do not change this section from here to the label "main" at 0x100.
; Start defining the program
; Jump around the interrupt handler return to the main program
		org	0x0
start	bsf		INTCON,GIE	; enable interrupts
		bsf		INTCON,INTE	; enable interupts
		clrf	semaphore	; clear local signalling variable
		goto	main


; ====================================================================
; ISR (= Interrupt Service Routine, or Interrupt Handler).
; It reads a 4-bit value from PORTB and stores it in location "inval".
; In this assignment, assume that 200 cycles or more pass between interrupts.
; First interrupt occurs only after 200 cycles to allow processor to setup after 
; power up.
; Do not modify this ISR code.
		org 0x4
handler	movwf   _wstore        	; temporaily store current w during interrupt service
		movf	PORTB,w			; get pin values
        andlw   0xFE            ; zero out low order bit (INT pin)
		movwf	inval			; put pin values in inval
		bsf		semaphore,0		; indicate that new pin values are available
        movf    _wstore, w      ; restore the old value of w
		bcf		INTCON,INTF		; clear interrupt flag
        bcf     PORTB, 0
		retfie					; return to instruction at which int occurred
; End of interrupt handler section
; ======================================================================

; Beginning of the "real" program
	org 0x100
main
		nop
		clrf	change_ret		;clear all
		clrf	coin_return		
		clrf	snickers
		clrf	totalcoins
		clrf	change
		clrf	temp1
		movlw	0x50			;cost of snickers is 80 cents, 50 in hex
		movwf	temp1			;location of snickers cost
		

; ======================================================================
;		the program sits in this loop waiting for interrupts
;		when a new input value is available, semaphore is set to 1
loop	btfss	semaphore,0
		goto	loop
;		at this point, the location "inval" will have the last 7-bit value read from port B
;		this 7-bit value represents the coins inserted

		bcf		semaphore,0	;reset semaphore to indicate interrupt handled
; =====================================================================

		btfsc	inval,5	;check if dollar
		call	dollar_in
		btfsc	inval,4 ;check if quarter
		call	quarter_in
		btfsc	inval,3	;check if dime
		call	dime_in
		btfsc	inval,2	;check if nickel
		call	nickel_in
		btfsc	inval,6	;check if coin return pressed
		call	return_coins
		btfsc	inval,1	;if penny is inserted, return_coins is also called
		call	return_coins

next	goto	loop
; End of 'main'
;=================================================================================
return_coins
		movlw	0x02					;moves literal of 0x02 into the
		movwf	coin_return				;coin_return position
		clrf	totalcoins				;all variables are cleared to reset
		clrf	change
		call	countto15				;0x02 held for 30 cycles
		call	countto15
		clrf	coin_return				;0x02 cleared
		return
;=================================================================================
nickel_in
		movlw	0x05					;literal value of 5 is moved into w
		addwf	totalcoins,1			;5 is added into the total coins register
		call	check_amount			;check amount is called
		return
;=================================================================================
dime_in
		movlw	0x0A					;literal value of 10 is moved to w
		addwf	totalcoins,1			;10 is added to total coins
		call	check_amount			;check amount called
		return
;=================================================================================
quarter_in
		movlw	0x19					;literal value of 25 moved into w
		addwf	totalcoins,1			;25 is added to total coins
		call	check_amount			;check amount called
		return

;=================================================================================
dollar_in
		movlw	0x64
		addwf	totalcoins,1	;places 100 into total inserted
		call	check_amount
		return
;=================================================================================
check_amount	btfsc	totalcoins,7	;checks if equal 80 cents has been input
				goto 	not_equal		;if it gets through all the bit tests,
				btfss	totalcoins,6	;then there is exactly 80 cents and
				goto	not_equal		;dispense is called. otherwise, as soon
				btfsc	totalcoins,5	;as there is a different bit, not_equal 
				goto	not_equal		;is called
				btfss	totalcoins,4
				goto	not_equal
				btfsc	totalcoins,3
				goto	not_equal	
				btfsc	totalcoins,2
				goto	not_equal
				btfsc	totalcoins,1
				goto	not_equal
				btfsc	totalcoins,0
				goto	not_equal
				call	dispense		;if equal, then call exact change
				goto	end_check

not_equal
				bsf		STATUS,C		;C bit of STATUS is reset to 1
				movfw	temp1			;0x50 (80 decimal) is subtracted from
				subwf	totalcoins,0	;total coins. if negative, then not 
				btfsc	STATUS,C		;enough has been inserted
				call	dispense

end_check
		return
;================================================================================
dispense	movfw	temp1				;move the hex 50 (80 decimal) into w
			subwf	totalcoins,0		;subtract this from total coins
			movwf	change				;move the result into change 
changeloop
			btfsc	change,6			;check bit 6 of change, if set, largest
			goto	return_quarter		;subtractable coin is quarter, call quarter
			btfsc	change,5			;check bit 5, same as above
			goto	return_quarter		
			btfsc	change,4			;check bit 4, could be quarter or dime
			goto	quarter_or_dime
			btfsc	change,3			;check bit 3, largest is dime
			goto	return_dime
			btfsc	change,2			;check bit 2, largest is nickel
			goto	return_nickel
			goto	give_candy			;if none are set, then candy is dispensed

quarter_or_dime							;this selects whther a quarter or dime
			btfsc	change,3			;should be dispensed by checking bit3
			goto	return_quarter		;checking bit 3 tells us if the value is
			goto	return_dime			;20 or 25
			

return_quarter							
			movlw	0x19				;moves 0x19 (decimal 25) to w
			subwf	change,1			;subtracts
			movlw	0x10				;moving 0x10 to change_ret means quarter
			movwf	change_ret			;is returned
			call	countto15			;delay for 15 cycles
			call	countto15			;delay for another 15 cycles
			clrf	change_ret			;clears change_ret
			goto	changeloop			;recalculates change needed

return_dime								;this does the exact same with a
			movlw	0x0A				;dime as it does with the quarter. for
			subwf	change,1			;reference, check return_quarter
			movlw	0x08
			movwf	change_ret
			call 	countto15
			call 	countto15
			clrf	change_ret
			goto	changeloop

return_nickel
			movlw	0x05				;does the exact same as return_quarter
			subwf	change,1			;but with a nickel. for reference,
			movlw	0x04				;check return_quarter
			movwf	change_ret
			call	countto15
			call	countto15
			clrf	change_ret
			goto	changeloop

give_candy
			movlw	0xFF				;gives candy. after all the change is
			movwf	snickers			;dispensed, 0xFF is written to location
			call	countto15			;snickers to dispense snickers bar and
			call	countto15			;held for 30 cycles. location snickers
			clrf	snickers			;is then returned and the coins inserted
			clrf	totalcoins			;is cleared
			return
			

; ======================================================================
; This subroutine provides a delay loop of approximately 15 cycles
countto15       movlw   numloops	;number of times to loop initialized
                movwf   holdcount
				nop
again           decfsz  holdcount	;tight loop based on numloops variable
                goto    again
                return				;delay of about 15 cycles complete
									;Note: branches, including call, skip
									;and goto, require 2 cycles
; ======================================================================
	


		end
