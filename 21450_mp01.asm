section .data            ;to allocate and initialize the variables
msg1 db "Enter any five 64 bit number :",0xA      ;0xA for new line
len1 equ $-msg1

msg2 db "The numbers are :"
len2 equ $-msg2 

count db 5h

section .bss
array resb 85

section .text
global _start

_start:
mov rax,01      	;write msg1 system call
mov rdi,01
mov rsi,msg1
mov rdx,len1
syscall

mov r8,array		;set pointer to the start of array

input:
mov rax,00      	;read num system call
mov rdi,00
mov rsi,r8
mov rdx,17
syscall

add r8,17		;incrementing pointer to the next memory space
dec byte[count]
jnz input

mov rax,01      	;write msg2 system call
mov rdi,01
mov rsi,msg2
mov rdx,len2
syscall

mov byte[count],5h      ;re-initializing the count variable
mov r8,array

output:         
mov rax,01      	;write num system call
mov rdi,01
mov rsi,r8
mov rdx,17
syscall

add r8,17
dec byte[count]   
jnz output          

mov rax,60         	;exit from program system call
mov rdi,0
syscall