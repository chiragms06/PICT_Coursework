section .data
msg1 db "Enter any string :", 0xA
len1 equ $-msg1

msg2 db "Length of string is :"
len2 equ $-msg2

count db 16

section .bss
str: resb 20
str_len: resb 20

section .text
global _start

_start:
mov rax,01			;print msg1
mov rdi,01
mov rsi,msg1
mov rdx,len1
syscall

mov rax,00			;take string input
mov rdi,00
mov rsi,str
mov rdx,20
syscall

dec al                  ; store actual value of string length
mov rbx, rax            
mov rdi, str_len         ; pointer at result


LOOP:
    rol rbx, 4              ; rotate B by 4 bits to left
    mov al, bl  
    and al, 0fh             ; mask at lower byte

    cmp al, 09h
    jbe BELOW_9
    add al, 07h

    BELOW_9:    
    add al, 30h
    mov [rdi], al           ; store hex-ascii value into result

    inc rdi                 ; increment result pointer 
    dec byte[count]	      ; decrement counter
    jnz LOOP                
    
mov rax,01			;print msg2
mov rdi,01
mov rsi,msg2
mov rdx,len2
syscall

mov rax,01			;print string length
mov rdi,01
mov rsi,str_len
mov rdx,20
syscall

mov rax,60			;exit
mov rdi,0
syscall
