public class N {         // 108
	private void *f          // 4
	private char str[100]; // 100
	private int i;         // 4
}

int ( *tab[2])(N *, N *) = { &N::operator+, &N::operator- };

// constructor
void N::N(int i)
{
	this->f = tab;
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

void main(int argc, char **argv)
{
	N *obj1 ;
	N *obj2;

	if (argc < 2)
		_exit(1);

	obj1 = new N(5);
	obj2 = new N(6);
	obj1->setAnnotation(argv[1]);

	obj2->f(obj1);

	return;
}
