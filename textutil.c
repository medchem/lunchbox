#define UNICODE
#define _UNICODE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#ifdef WIN32
	#include <windows.h>
#endif
#include <ctype.h>
#include <iconv.h>
#include "textutil.h"

void readline(char *dest)
{
	char *ps=dest;
	char ch;
	while((ch=getchar())=='\n')
		;
	while((ch!='\n')){
		*ps=ch;
		ch=getchar();
		ps++;
	}
	 *ps='\0';
}
/*
 *size_t iconv (iconv_t cd,
              const char* * inbuf, size_t * inbytesleft,
              char* * outbuf, size_t * outbytesleft);
 * 
 */
#ifdef WIN32
void read_utf_to_950(const char *src, char *dest)
{
	iconv_t cd = iconv_open("cp950", "utf-8"); 
	size_t inlen=2*strlen(src);
	size_t outlen=inlen;

	iconv(cd, &src, &inlen, &dest, &outlen);
	
	iconv_close(cd);
}

void read_950_to_utf(const char *src, char *dest)
{
	iconv_t cd = iconv_open("utf-8", "cp950"); 
	size_t inlen=2*strlen(src);
	size_t outlen=inlen;

	iconv(cd, &src, &inlen, &dest, &outlen);
	
	iconv_close(cd);
	/*
	int len=strlen(src)+1;
	
	wchar_t medium[50];

	
	MultiByteToWideChar(950, MB_COMPOSITE, src, len, medium, 50);
	len=wcslen(medium);
	WideCharToMultiByte(CP_UTF8, 0, medium, 2*len, dest, \
			2*len, NULL, NULL);
	*/
}
#endif
