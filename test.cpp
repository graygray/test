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

int main() {

	printf("start %s\n", __FUNCTION__);

	Fibonacci(5, callbackfunc);

	printf("%d\n", 5^10);

	/*test assert*/
//	assert(1 == 2);
//	printf("continous\n");

	/*print ascii*/
//	for (int var = 0; var < 129; ++var) {
//	    printf("%c\t", var);
//	}

//	getchar();
	return 0;

}


