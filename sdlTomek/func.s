	; rdi - poczatek bitmapy
	; rsi - ilosc pixeli
	; rdx - opcja (0-rozciaganie histogramu; 1-zmiana kontrastu) -> r15
	; rcx - parameter(wspolczynik zmiany kontrastu)-> r14


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


