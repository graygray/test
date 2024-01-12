
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <thread>
#include <unistd.h>

// add at ubuntu 18.04
#include <stdint.h>
#include <string.h> 

#define MIN(a,b) (a>b) ? b : a
#define MAX_STRING_SIZE	2048

#define DEBUGX
#ifndef DEBUGX
#define xlog
#else
#define xlog printf
#endif

//#define POLY 0x1021
#define POLY 0x8810
//#define POLY 0x8408

//#define CRC32Const 0x04C11DB7
#define CRC32Const 0xEDB88320
//#define CRC32Const 0x82608EDB

int Min(int a,int b, int c);
int Fibonacci(int n, void (*f)());

void make_crc_table(void);
unsigned short crc16(unsigned char *data_p, unsigned short length);
unsigned short crc16_ccitt(const void *buf, int len);
uint32_t crc32(uint8_t *buf, size_t len);
unsigned int crc(unsigned char* data, unsigned int data_len, unsigned int gen, unsigned int gen_len);