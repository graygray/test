#include "test.h"
#include "lib_crc.h"

using namespace std; 

uint32_t crc_table[256];

void thread1(void) {
	xlog("%s:%d \n\r", __func__, __LINE__);
	int counter = 0;
	while (true)
	{
		xlog("%s:%d, counter:%d \n\r", __func__, __LINE__, counter++);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));	
	}
}

void thread2(void) {
	xlog("%s:%d \n\r", __func__, __LINE__);
	int counter = 0;
	while (true)
	{
		xlog("%s:%d, counter:%d \n\r", __func__, __LINE__, counter++);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));	
	}
}

void defaultFun(void) {
	xlog("%s:%d \n\r", __func__, __LINE__);

	std::thread threads[2];
	threads[0] = std::thread(thread1);
	threads[1] = std::thread(thread2);
    for (auto& t: threads) {
        t.join();
    }
}

int main(int argc, char *argv[])
{
	xlog("%s:%d, argc:%d \n\r", __func__, __LINE__, argc);
	for (int i = 0; i < argc; ++i) {
		xlog("%s:%d, argv[%d]:%s \n\r", __func__, __LINE__, i, argv[i]);
	}

	if( argc < 2 )
	{
		xlog("%s:%d, input more than 1 params... \n\r", __func__, __LINE__);
		defaultFun();
		return -1;
	}

	xlog("%s:%d, ===================================== \n\r", __func__, __LINE__);
	// cases -------------------------------------------------
	if ( !strcmp(argv[1], "test") ) {

		xlog("%s:%d, test... \n\r", __func__, __LINE__);

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
		int i = 0;
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
	    // char *ptr, *dest, hex_val, prev_byte;
	    char prev_byte;
	    unsigned short crc_16, crc_16_modbus, crc_ccitt_ffff, crc_ccitt_0000, crc_ccitt_1d0f, crc_dnp, crc_sick, crc_kermit;
	    unsigned short low_byte, high_byte;
	    unsigned long crc_32;
	    int ch, do_ascii, do_hex;
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

		xlog("%s:%d, not a case!! \n\r", __func__, __LINE__);

	}
	xlog("%s:%d, ===================================== \n\r", __func__, __LINE__);

//	getchar();
	return 0;

}

int Min(int a,int b, int c) {
	return (a<=b && a<=c) ?  a :  ((b<c) ? b :c );
}

//typedef void (*display_func)();
int Fibonacci(int n, void (*f)()) {
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

unsigned short crc16(unsigned char *data_p, unsigned short length) {
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

unsigned short crc16_ccitt(const void *buf, int len) {
	register int counter;
	register unsigned short crc = 0;
	char *buf2 = (char *)buf;
	for( counter = 0; counter < len; counter++)
		crc = (crc<<8) ^ crc16tab[((crc>>8) ^ *(char *)buf2++)&0x00FF];
	return crc;
}

uint32_t crc32(uint8_t *buf, size_t len) {
    uint32_t c = 0xFFFFFFFF;
    for (size_t i = 0; i < len; i++) {
        c = crc_table[(c ^ buf[i]) & 0xFF] ^ (c >> 8);
    }
    return c ^ 0xFFFFFFFF;
}

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
	for (i = 0; i < (int)data_len; ++i)
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
