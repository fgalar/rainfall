int main(int argc,char **argv)
{
  int ret;
  char str[40];
  int n;
  
  n = atoi(argv[1]);
  if (n < 10) {
    memcpy(str, argv[2], n * 4);
	// 1464814662
    if (n == 0x574f4c46) {
      execl("/bin/sh", "sh", 0);
    }
    ret = 0;
  }
  else {
    ret = 1;
  }
  return ret;
}