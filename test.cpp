#include<stdlib.h>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<assert.h>
#include "lib_crc.h"

// add at ubuntu 18.04
#include<stdint.h>
#include <string.h> 

using namespace std; 

#define MIN(a,b) (a>b) ? b : a
#define MAX_STRING_SIZE	2048

void default_func_test(int val=2){

	printf(" default_func_test\n");
	printf(" val=%d\n", val);
}

//#define POLY 0x1021
#define POLY 0x8810
//#define POLY 0x8408
unsigned short crc16(unsigned char *data_p, unsigned short length)
{
      unsigned char i;
      unsigned int data;
      unsigned int crc = 0xffff;

      if (length == 0)
            return (~crc);

      do
      {
            for (i=0, data=(unsigned int)0xff & *data_p++;
                 i < 8;
                 i++, data >>= 1)
            {
                  if ((crc & 0x0001) ^ (data & 0x0001))
                        crc = (crc >> 1) ^ POLY;
                  else  crc >>= 1;
            }
      } while (--length);

      crc = ~crc;
      data = crc;
      crc = (crc << 8) | (data >> 8 & 0xff);

      return (crc);
}

static const unsigned short crc16tab[256]= {
	0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
	0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef,
	0x1231,0x0210,0x3273,0x2252,0x52b5,0x4294,0x72f7,0x62d6,
	0x9339,0x8318,0xb37b,0xa35a,0xd3bd,0xc39c,0xf3ff,0xe3de,
	0x2462,0x3443,0x0420,0x1401,0x64e6,0x74c7,0x44a4,0x5485,
	0xa56a,0xb54b,0x8528,0x9509,0xe5ee,0xf5cf,0xc5ac,0xd58d,
	0x3653,0x2672,0x1611,0x0630,0x76d7,0x66f6,0x5695,0x46b4,
	0xb75b,0xa77a,0x9719,0x8738,0xf7df,0xe7fe,0xd79d,0xc7bc,
	0x48c4,0x58e5,0x6886,0x78a7,0x0840,0x1861,0x2802,0x3823,
	0xc9cc,0xd9ed,0xe98e,0xf9af,0x8948,0x9969,0xa90a,0xb92b,
	0x5af5,0x4ad4,0x7ab7,0x6a96,0x1a71,0x0a50,0x3a33,0x2a12,
	0xdbfd,0xcbdc,0xfbbf,0xeb9e,0x9b79,0x8b58,0xbb3b,0xab1a,
	0x6ca6,0x7c87,0x4ce4,0x5cc5,0x2c22,0x3c03,0x0c60,0x1c41,
	0xedae,0xfd8f,0xcdec,0xddcd,0xad2a,0xbd0b,0x8d68,0x9d49,
	0x7e97,0x6eb6,0x5ed5,0x4ef4,0x3e13,0x2e32,0x1e51,0x0e70,
	0xff9f,0xefbe,0xdfdd,0xcffc,0xbf1b,0xaf3a,0x9f59,0x8f78,
	0x9188,0x81a9,0xb1ca,0xa1eb,0xd10c,0xc12d,0xf14e,0xe16f,
	0x1080,0x00a1,0x30c2,0x20e3,0x5004,0x4025,0x7046,0x6067,
	0x83b9,0x9398,0xa3fb,0xb3da,0xc33d,0xd31c,0xe37f,0xf35e,
	0x02b1,0x1290,0x22f3,0x32d2,0x4235,0x5214,0x6277,0x7256,
	0xb5ea,0xa5cb,0x95a8,0x8589,0xf56e,0xe54f,0xd52c,0xc50d,
	0x34e2,0x24c3,0x14a0,0x0481,0x7466,0x6447,0x5424,0x4405,
	0xa7db,0xb7fa,0x8799,0x97b8,0xe75f,0xf77e,0xc71d,0xd73c,
	0x26d3,0x36f2,0x0691,0x16b0,0x6657,0x7676,0x4615,0x5634,
	0xd94c,0xc96d,0xf90e,0xe92f,0x99c8,0x89e9,0xb98a,0xa9ab,
	0x5844,0x4865,0x7806,0x6827,0x18c0,0x08e1,0x3882,0x28a3,
	0xcb7d,0xdb5c,0xeb3f,0xfb1e,0x8bf9,0x9bd8,0xabbb,0xbb9a,
	0x4a75,0x5a54,0x6a37,0x7a16,0x0af1,0x1ad0,0x2ab3,0x3a92,
	0xfd2e,0xed0f,0xdd6c,0xcd4d,0xbdaa,0xad8b,0x9de8,0x8dc9,
	0x7c26,0x6c07,0x5c64,0x4c45,0x3ca2,0x2c83,0x1ce0,0x0cc1,
	0xef1f,0xff3e,0xcf5d,0xdf7c,0xaf9b,0xbfba,0x8fd9,0x9ff8,
	0x6e17,0x7e36,0x4e55,0x5e74,0x2e93,0x3eb2,0x0ed1,0x1ef0
};

unsigned short crc16_ccitt(const void *buf, int len)
{
	register int counter;
	register unsigned short crc = 0;
	char *buf2 = (char *)buf;
	for( counter = 0; counter < len; counter++)
		crc = (crc<<8) ^ crc16tab[((crc>>8) ^ *(char *)buf2++)&0x00FF];
	return crc;
}

uint32_t crc_table[256];
/* Run this function previously */
void make_crc_table(void) {
    for (uint32_t i = 0; i < 256; i++) {
        uint32_t c = i;
        for (int j = 0; j < 8; j++) {
            c = (c & 1) ? (0xEDB88320 ^ (c >> 1)) : (c >> 1);
        }
        crc_table[i] = c;
    }
}

uint32_t crc32(uint8_t *buf, size_t len) {
    uint32_t c = 0xFFFFFFFF;
    for (size_t i = 0; i < len; i++) {
        c = crc_table[(c ^ buf[i]) & 0xFF] ^ (c >> 8);
    }
    return c ^ 0xFFFFFFFF;
}

//#define CRC32Const 0x04C11DB7
#define CRC32Const 0xEDB88320
//#define CRC32Const 0x82608EDB
unsigned int crc(
		unsigned char* data, unsigned int data_len,
		unsigned int gen, unsigned int gen_len) {

	unsigned int crc = 0;

//	crc = data[0] << 24;
//	printf("[gray] test.cpp:%s:%d, crc:0x%X\n", __FUNCTION__, __LINE__, crc);
//	crc = crc | (data[1] << 16);
//	printf("[gray] test.cpp:%s:%d, crc:0x%X\n", __FUNCTION__, __LINE__, crc);
//	crc = crc | (data[2] << 8);
//	printf("[gray] test.cpp:%s:%d, crc:0x%X\n", __FUNCTION__, __LINE__, crc);
//	crc = crc | ( data[3] );
//	printf("[gray] test.cpp:%s:%d, crc:0x%X\n", __FUNCTION__, __LINE__, crc);

	int i, j;
	int var;
	for (i = 0; i < data_len; ++i)
	{

		// count in a byte
		for (j = 0; j < 8; ++j)
		{

			if (crc & 0x80000000)
			{
				crc = crc ^ CRC32Const;
			}
			crc = crc << 1;
			crc = crc | (data[i] >> (7 - j) & 1);

		}
	printf("[gray] test.cpp:%s:%d, crc:0x%X, i:%d\n", __FUNCTION__, __LINE__, crc, i);
	}

	for (var = 0; var < 31; ++var)
	{

		if (crc & 0x80000000)
		{
			crc = crc ^ CRC32Const;
		}
		crc = crc << 1;
	}

	printf("[gray] test.cpp:%s:%d, crc:0x%X, i:%d\n", __FUNCTION__, __LINE__, crc, i);
	return crc;

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
		unsigned char buf[512];

		memset(buf, 0, sizeof(buf));

		fp = fopen("Y0199.bin", "rb");
//		fp = fopen("T2051.bin", "rb");
//		fp = fopen("C0877.bin", "rb");
		if (!fp) {
			printf("[gray] test.cpp:%s:%d, open fail\n", __FUNCTION__, __LINE__);
			fclose(fp);
			return -1;
		}

		unsigned char c;
		c = fgetc(fp);
		while(!feof(fp))
		{
			printf("%02X ", c);		// print file content
			buf[i] = c;				// read to buffer
			i++;
			c = fgetc(fp);
		}
		printf("\n");
		printf("[gray] test.cpp:%s:%d, len:%d\n", __FUNCTION__, __LINE__, i);
		printf("\n");
		fclose(fp);

		// crc16
		printf("[gray] test.cpp:%s:%d, mycrc:0x%X\n", __FUNCTION__, __LINE__, crc(buf, i, 0x04C11DB7 , 32));
		printf("[gray] test.cpp:%s:%d, crc16:0x%X\n", __FUNCTION__, __LINE__, crc16(buf, i));
		printf("[gray] test.cpp:%s:%d, crc16_ccitt:0x%X\n", __FUNCTION__, __LINE__, crc16_ccitt(buf, i));

		// crc32
		make_crc_table();
		printf("[gray] test.cpp:%s:%d, crc32:0x%X\n", __FUNCTION__, __LINE__, crc32(buf, i));


	// use crc library
	// >> x crc fileName
	} else if (!strcmp(argv[1], "crc")) {

		printf("[gray] test.cpp:%s:%d\n", __FUNCTION__, __LINE__);

	    char input_string[MAX_STRING_SIZE];
	    char *ptr, *dest, hex_val, prev_byte;
	    unsigned short crc_16, crc_16_modbus, crc_ccitt_ffff, crc_ccitt_0000, crc_ccitt_1d0f, crc_dnp, crc_sick, crc_kermit;
	    unsigned short low_byte, high_byte;
	    unsigned long crc_32;
	    int a, ch, do_ascii, do_hex;
	    FILE *fp;

	    do_ascii = FALSE;
	    do_hex   = FALSE;

	    crc_16 = 0;
		crc_16_modbus = 0xffff;
		crc_dnp = 0;
		crc_sick = 0;
		crc_ccitt_0000 = 0;
		crc_ccitt_ffff = 0xffff;
		crc_ccitt_1d0f = 0x1d0f;
		crc_kermit = 0;
		crc_32 = 0xffffffffL;

		prev_byte = 0;
		fp = fopen(argv[2], "rb");

		if (fp != NULL)
		{
			while ((ch = fgetc(fp)) != EOF)
			{
				crc_16 = update_crc_16(crc_16, (char) ch);
				crc_16_modbus = update_crc_16(crc_16_modbus, (char) ch);
				crc_dnp = update_crc_dnp(crc_dnp, (char) ch);
				crc_sick = update_crc_sick(crc_sick, (char) ch, prev_byte);
				crc_ccitt_0000 = update_crc_ccitt(crc_ccitt_0000, (char) ch);
				crc_ccitt_ffff = update_crc_ccitt(crc_ccitt_ffff, (char) ch);
				crc_ccitt_1d0f = update_crc_ccitt(crc_ccitt_1d0f, (char) ch);
				crc_kermit = update_crc_kermit(crc_kermit, (char) ch);
				crc_32 = update_crc_32(crc_32, (char) ch);

				prev_byte = (char) ch;
			}
			fclose(fp);
		}
		else
			printf("%s : cannot open file\n", argv[2]);

		crc_32 ^= 0xffffffffL;

		crc_dnp = ~crc_dnp;
		low_byte = (crc_dnp & 0xff00) >> 8;
		high_byte = (crc_dnp & 0x00ff) << 8;
		crc_dnp = low_byte | high_byte;

		low_byte = (crc_sick & 0xff00) >> 8;
		high_byte = (crc_sick & 0x00ff) << 8;
		crc_sick = low_byte | high_byte;

		low_byte = (crc_kermit & 0xff00) >> 8;
		high_byte = (crc_kermit & 0x00ff) << 8;
		crc_kermit = low_byte | high_byte;

		printf("%s%s%s :\nCRC16              = 0x%04X      /  %u\n"
				"CRC16 (Modbus)     = 0x%04X      /  %u\n"
				"CRC16 (Sick)       = 0x%04X      /  %u\n"
				"CRC-CCITT (0x0000) = 0x%04X      /  %u\n"
				"CRC-CCITT (0xffff) = 0x%04X      /  %u\n"
				"CRC-CCITT (0x1d0f) = 0x%04X      /  %u\n"
				"CRC-CCITT (Kermit) = 0x%04X      /  %u\n"
				"CRC-DNP            = 0x%04X      /  %u\n"
				"CRC32              = 0x%08lX  /  %lu\n",
				(do_ascii || do_hex) ? "\"" : "",
				(!do_ascii && !do_hex) ? argv[2] : input_string,
				(do_ascii || do_hex) ? "\"" : "", crc_16, crc_16, crc_16_modbus,
				crc_16_modbus, crc_sick, crc_sick, crc_ccitt_0000,
				crc_ccitt_0000, crc_ccitt_ffff, crc_ccitt_ffff, crc_ccitt_1d0f,
				crc_ccitt_1d0f, crc_kermit, crc_kermit, crc_dnp, crc_dnp,
				crc_32, crc_32);

	} else {

		printf("not a case!! \n");

	}
	printf("=====================================\n");

//	getchar();
	return 0;

}
