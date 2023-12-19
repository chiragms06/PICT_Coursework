section .data
arr db 10,34,45,90,0xA
count db 5h

msg db "The largest number is :"
len equ $-msg

section .bss
max: resb 16

section .text
global _start

_start:
mov al,0h
mov r8,arr

l1:
cmp al,byte[r8]
ja l2

mov al,byte[r8]

l2:
inc r8
dec byte[count]
jnz l1

mov r8,max
mov byte[count],2

LOOP:
    rol al, 4              ; rotate B by 4 bits to left
    mov bl, al  
    and bl, 0Fh             ; mask at lower byte

    cmp bl, 09h
    jbe BELOW_9
    add bl, 07h

    BELOW_9:    
    add bl, 30h
    mov [r8], bl           ; store hex-ascii value into result

    inc r8                 ; increment result pointer 
    dec byte[count]	      ; decrement counter
    jnz LOOP         

mov rax,01
mov rdi,01
mov rsi,msg
mov rdx,len
syscall

mov rax,01
mov rdi,01
mov rsi,max
mov rdx,2
syscall
  
mov rax,60
mov rdi,0
syscall
