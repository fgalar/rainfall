#include <string.h>

class N {				 // 108
	public :
		typedef int (N::*function)(N*);

		function f;      // 4
		char str[100];   // 100
		int i;           // 4		
		
		N(int i);
		void setAnnotation(char *str);
		int operator+(N *obj);
		int operator-(N *obj);
};

N::function tab[2] = { &N::operator+, &N::operator- };

// constructor
N::N(int i)
{
	this->f = tab[0];
	this->i = i;
}

// methods

void N::setAnnotation(char *str)
{
	memcpy(this->str, str, strlen(str));
}

int N::operator+(N *obj)

{
	return obj->i + this->i;
}

int N::operator-(N *obj)
{
	return this->i - obj->i;
}

int main(int argc, char **argv)
{
	N *obj1 ;
	N *obj2;

	if (argc < 2)
		_exit(1);

	obj1 = new N(5);
	obj2 = new N(6);
	obj1->setAnnotation(argv[1]);

	(obj2->*obj2->f)(obj1);
}
