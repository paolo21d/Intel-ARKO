	; rdi - poczatek bitmapy -> r15
	; rsi - ilosc pixeli ->r14
	; rdx - opcja (0-rozciaganie histogramu; 1-zmiana kontrastu)
	; xmm0 - parameter(wspolczynik zmiany kontrastu)-> r13 (tylko jesli kontrast)


section .data
	align 64
	lutR TIMES 256 DB 0
	lutG TIMES 256 DB 0
	lutB TIMES 256 DB 0
	lut TIMES 256 DB 0 ;zmiana kontrastu
	minMaxTable TIMES 256 DB 0 ;Bmin, Bmax, Gmin, Gmax, Rmin, Rmax, Amin, Amax
	bitmap: dd 0 

section .text
	global func

func:
	push rbp
	mov rbp, rsp

	mov r15, rdi ;dane o pixelach
	push r15 ;na stosie jest poczatek danych
	mov r14, rsi ;ilosc pixeli

	mov byte [minMaxTable], 255
	mov byte [minMaxTable+1], 0
	mov byte [minMaxTable+2], 255
	mov byte [minMaxTable+3], 0
	mov byte [minMaxTable+4], 255
	mov byte [minMaxTable+5], 0

	cmp rdx, 1
	jl histogram

kontrast:
	mov r13, 0
	;cvtsi2ss xmm1, rcx
	;cvtss2si r11, xmm10 ;zamiana double->int
k_calcLut:
	inc r13
	mov r12b, byte [r15]
	cvtsi2ss xmm1, r12

histogram:
	
	mov r13, 0
findMinMax:
	inc r13
	mov r8b, byte[r15]

end:	

	mov rsp, rbp	
	pop rbp
	ret


