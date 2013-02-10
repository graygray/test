#include<stdlib.h>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<assert.h>

using namespace std; 

#define MIN(a,b) (a>b) ? b : a

void default_func_test(int val=2){

	printf(" default_func_test\n");
	printf(" val=%d\n", val);
}

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

	int var, i=0;
	for (var = 0; var < argc; ++var) {
		printf("argv[%d]:%s \n", var, argv[var]);
	}

	printf("=====================================\n");
	// cases -------------------------------------------------
	if ( !strcmp(argv[1], "test") ) {

		printf("test!! \n");

	// open bin file
	} else if (!strcmp(argv[1], "obf")) {

		printf("[gray] test.cpp:%s:%d\n", __FUNCTION__, __LINE__);
		FILE *fp;

		fp = fopen("T2051.bin", "rb");
		if (!fp) {
			printf("[gray] test.cpp:%s:%d, open fail\n", __FUNCTION__, __LINE__);
			fclose(fp);
			return -1;
		}

		unsigned char c;
		c = fgetc(fp);
		while(!feof(fp))
		{
			i++;
			printf("%02X ", c);
			c = fgetc(fp);
		}
		printf("\n");
		printf("[gray] test.cpp:%s:%d, len:%d\n", __FUNCTION__, __LINE__, i);
		printf("\n");

		fclose(fp);

	// CRC
	} else if (!strcmp(argv[1], "crc")) {

		printf("[gray] test.cpp:%s:%d\n", __FUNCTION__, __LINE__);


	} else {

		printf("not a case!! \n");

	}
	printf("=====================================\n");



//	getchar();
	return 0;

}
