
; sample

	org 0x00
	clrw ;fix
loop
	addlw 0x01
	movwf 20h
	goto loop
	end