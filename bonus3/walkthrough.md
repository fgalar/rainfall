# Rainfall - Bonus 3

## Executable Analyse
The executable opens a file descriptor "/home/user/end/.pass".
- First part (0-66) of the hash is copied into a buffer of size 132. 
- A **'\0'** is set at the position entered by the user and parse with an atoi().
- Second part of the hash is copied into buffer (66-131).  

To execute 'execl("/bin/sh", "sh", 0);', our argument must be equal to content find in "/home/user/end/.pass"

## Overjoke

The attack here consists to set argv[1] to NULL  
Because atoi() of null will output 0 and make buffer[0] = 0. 
At the end strcmp will compare null str with null buffer and enter in our precious condition.


```bash
bonus3@RainFall:~$ ./bonus3 ''
```