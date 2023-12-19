section .data
msg1 db "Number of positive numbers :",0xA
len1 equ $-msg1

msg2 db "Number of negative numbers :",0xA
len2 equ $-msg2

arr dq 0xFFFF111122223333,0x1FFF111122223333,0x2FFF111122223333,0x8FFF111122223333,0xAFFF111122223333
poscnt dq 0h
negcnt dq 0h
counter db 05h
mov al,00h
mov r8,00h

newline db 0xA
len equ $-newline

%macro print 2
mov rax,01
mov rdi,01
mov rsi,%1
mov rdx,%2
syscall
%endmacro

%macro NewLine 0
mov rax,01
mov rdi,01
mov rsi,newline
mov rdx,len
syscall
%endmacro

section .bss
result: resq 1

section .text
global _start

_start:
mov r8,arr

loop:
mov rax,qword[r8]
BT rax,63
jnc label
add qword[negcnt],01h
jmp l1

label:
add qword[poscnt],01h

l1:
add r8,8h
dec byte[counter]
jnz loop

mov rax,qword[poscnt]
call HEX_TO_ASCII
print msg1,len1
print result,16
NewLine
mov rax,qword[negcnt]
call HEX_TO_ASCII
print msg2,len2
print result,16
NewLine

exit:
mov rax,60
mov rdi,0
syscall

;----PROCEDURE-----

HEX_TO_ASCII:
	mov byte[counter],16
	mov rbp,result

	l2:
    	rol rax, 4             
    	mov bl, al  
    	and bl, 0Fh           
    	cmp bl, 09h
    	jbe BELOW_9
    	add bl, 07h 

    	BELOW_9:    
    	add bl, 30h
    	mov byte[rbp], bl          

    	inc rbp                 
    	dec byte[counter]	      
    	jnz l2

ret
