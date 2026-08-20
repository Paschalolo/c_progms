# RANDOM C/C++ PROGRAMS FOR SYSTEM PROGRAMMING

Programs here cover interacting the os system calls 
memory mapping , networking both conectionless and connection orirented streams . 
Other  distrubuted systen i.e multicasting , broadcasting 
Network programming at its finest . 
We write a runtime dynamic loader and also a feature of readelf or objdump capable of extracting symbols from an executable .
We experiment on new linux tools for greater perfromance AF_XDP , io_uring .It gets complex and we fight cache lines and tlb eviction . Its better to aviod sharing 
```nasm
section .text
    global _start
align 8
_start:
    ; creating a socket 
    sub rsp , 48 
    mov rax , 0x29 ; System call to socket()
    mov edi , 0x02 ; AF_INET 
    mov esi , 1 ; SOCK_STREAMS 
    mov edx , 0 
    syscall ; Invoke the kernel
    cmp eax  , -1 ; eax contains our fd or a negative value if error 
    jl __exit 
    ; ... set sockaddr and other things 

; Finito 
    add rsp , 48 
    mov rax , 0x5d 
    mov rdi , 1 
    syscall 
__exit : 
    add rsp , 48
    mov rax , 0x5d 
    mov rdi , 1 
    syscall 
```
