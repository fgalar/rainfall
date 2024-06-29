# Rainfall - Bonus 1

## Executable Analyse

The program uses two arguments: 
- an int n
- a str string

To run shell n must be less than 10 and equal to 1464814662 ... obviously it is impossible... without overflow.  

The overflow is easy to achieve with the line `memcpy(str, argv[2], n * 4);` because memcpy is vulnerable and str defined just before n.  


## Int Overoverflow

To overwrite str and change the value of n, we will need a buffer of size `n * 4 = 44`, so we need n < 10 and n == 11.  

The exploit resides in variable : atoi returns an int and memcpy takes unsigned int in parameters. 

Using `n = -2**31 - 11 = -2147483637`, n is well below 10 and (n * 4) cast in unsigned int returns well 44.  

To finish the level we need to use the second arguments to overflow str on n and finaly pass the last condition :

```bash
./bonus1 -2147483637 $(python -c 'print "A" * 40 + "\x57\x4f\x4c\x46"[::-1]')
```