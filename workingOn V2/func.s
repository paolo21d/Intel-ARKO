	; rdi - poczatek bitmapy
	; rsi - szerokosc
	; rdx - wysokosc
	; rcx - parameter(wspolczynik zmiany kontrastu)-> r14
	; r8 - opcja (0-rozciaganie histogramu; 1-zmiana kontrastu) -> r15

	; r10 - obliczony x
	; r11 - obliczony y
	; xmm0 - t

section .data
	

section .text
	global func

func:
	push rbp
	mov rbp, rsp

	mov r14, rcx
	mov r15, r8
	
histogram:


kontrast:


end:	

	mov rsp, rbp	
	pop rbp
	ret


