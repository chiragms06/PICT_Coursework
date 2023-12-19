section .data
num1 dq 06h
num2 dq 03h
count db 0

menu db "MENU :",0xA
     db "1.ADDITION",0xA
     db "2.SUBTRACTION",0xA
     db "3.MULTIPLICATION",0xA
     db "4.DIVISION",0xA
menulen equ $-menu

numbers db "Numbers are :",0xA
numlen equ $-numbers

option db "Enter your choice :",0xA
oplen equ $-option

newline db 0xA
len equ $-newline

msg1 db "Addition is :",0xA
len1 equ $-msg1

msg2 db "Subtraction is :",0xA
len2 equ $-msg2

msg3 db "Multiplication is :",0xA
len3 equ $-msg3

msg4 db "Division is :",0xA
len4 equ $-msg4

%macro print 2   
mov rax,01
mov rdi,01
mov rsi,%1    ;result
mov rdx,%2    ;no.of bytes
syscall
%endmacro

%macro Newline 0
mov rax,01
mov rdi,01
mov rsi,newline
mov rdx,len
syscall
%endmacro

section .bss
result: resq 1
op: resb 2

section .text
global _start

_start:
Show_menu:
print menu,menulen
Newline
print option,oplen

mov rax,00
mov rdi,00
mov rsi,op
mov rdx,2
syscall

cmp byte[op],'1'
je ADDITION

cmp byte[op],'2'
je SUBTRACTION

cmp byte[op],'3'
je MULTIPLICATION

cmp byte[op],'4'
je DIVISION

cmp byte[op],'5'
jmp exit

ADDITION:
	mov rax,qword[num1]
	mov rbx,qword[num2]
	add rax,rbx
	
	call HEX_TO_ASCII
	print msg1,len1
	print result,16
	Newline
	jmp exit
	
SUBTRACTION:
	mov rax,qword[num1]
	mov rbx,qword[num2]
	sub rax,rbx
	
	call HEX_TO_ASCII
	print msg2,len2
	print result,16
	Newline
	jmp exit
	
MULTIPLICATION:
	mov rax,qword[num1]
	mov rbx,qword[num2]
	mul rbx
	
	push rax
	mov rax,rdx
	
	call HEX_TO_ASCII
	print msg3,len3
	print result,16
	
	pop rax 
	call HEX_TO_ASCII
	print result,16
	Newline
	jmp exit
	
DIVISION:
	xor rdx,rdx
	mov rax,qword[num1]
	mov ebx,dword[num2]
	div ebx
	
	push rax
	mov rax,rdx
	
	call HEX_TO_ASCII
	print msg4,len4
	print result,16
	
	pop rax
	call HEX_TO_ASCII
	print result,16
	Newline
	jmp exit

exit:	
mov rax,60
mov rdi,0
syscall

;----PROCEDURE-----

HEX_TO_ASCII:
	mov byte[count],16
	mov rdi,result

	LOOP:
    		rol rax, 4              ; rotate B by 4 bits to left
    		mov bl, al  
    		and bl, 0Fh             ; mask at lower byte

    		cmp bl, 09h
    		jbe BELOW_9
    		add bl, 07h 

    		BELOW_9:    
    		add bl, 30h
    		mov byte[rdi], bl           ; store hex-ascii value into result

    		inc rdi                 ; increment result pointer 
    		dec byte[count]	      ; decrement counter
    		jnz LOOP

	ret

