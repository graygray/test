#include<stdlib.h>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<assert.h>

using namespace std; 

#define MIN(a,b) (a>b) ? b : a


int Min(int a,int b, int c)
{
//	(a<=b && a<=c) ? return a :  b;
	return (a<=b && a<=c) ?  a :  ((b<c) ? b :c );
}

//typedef void (*display_func)();
int Fibonacci(int n, void (*f)())
{
	if(n == 1 || n ==2)
	{
		return 1;
	}
	else
	{
		int i;
		int f1 = 1, f2 = 1, f3 = 0;

		for (i = 3; i <= n; ++i) {
			f3 = f1 + f2;
			f1 = f2;
			f2 = f3;

		}

		f();
		return f3;
	}
}

void callbackfunc()
{
	printf(" %s\n", __FUNCTION__);
}

int main(int argc, char *argv[])
{

	printf("argc:%d \n", argc);

	if( argc < 2 )
	{
		printf("need at least one params\n");
		getchar();
		return -1;
	}

	int var;
	for (var = 0; var < argc; ++var) {
		printf("argv[%d]:%s \n", var, argv[var]);
	}

	printf("=====================================\n");
	// cases -------------------------------------------------
	if ( !strcmp(argv[1], "test") ) {

		printf("test!! \n");

	} else if (!strcmp(argv[1], "test2")) {

	} else if (!strcmp(argv[1], "test3")) {

	} else if (!strcmp(argv[1], "test4")) {

	} else {

		printf("not a case!! \n");

	}
	printf("=====================================\n");

//	getchar();
	return 0;

}


