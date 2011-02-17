#include <stdio.h>
#include <ctype.h>
#include "textutil.h"
#define MAX_HEADER_SIZE 30
#define MAX_BODY_SIZE 500

int read_header(FILE *fp, char header[], int header_size);
int read_body(FILE *fp, char body[], int body_size);

int main()
{
	FILE *fp=fopen("lunchbase.dat", "r");
	int ch;	
	char testheader[MAX_HEADER_SIZE], testbody[MAX_BODY_SIZE];
	#ifdef WIN32
	char outheader[MAX_HEADER_SIZE], outbody[MAX_BODY_SIZE];
	#endif
	if (!fp){
		printf("Can't open lunchbase.dat.\n");
		return 1;
	}
	while((ch=fgetc(fp))!=EOF){
		ungetc(ch, fp);
		read_header(fp, testheader, MAX_HEADER_SIZE);

		#ifdef WIN32
		read_utf_to_950(testheader, outheader);
		printf("Header:\n%s\n", outheader);
		#else
		printf("Header:\n%s\n", testheader);
		#endif
		
		read_body(fp, testbody, MAX_BODY_SIZE);
		#ifdef WIN32
		read_utf_to_950(testbody, outbody);
		printf("Body:\n%s\n", outbody);
		#else
		printf("Body:\n%s\n", testbody);
		#endif
		fgetc(fp);
	}
	return 0;
}

int read_header(FILE *fp, char header[], int header_size)
{
	int ch;
	register int i=0;
	while(isspace(ch=fgetc(fp)))
		;
	if (ch!='['){
		printf("Error reading header.\n");
		return -1;
	}
	while((ch=fgetc(fp))!=']'){
		if (ch==EOF){
			printf("Reached end of file.\n");
			return -2;
		}
		if (i>header_size){
			printf("Buffer overrun.\n");
			return -3;
		}
		header[i]=ch;
		i++;
	}
	header[i]='\0';
	return i;
}

int read_body(FILE *fp, char body[], int body_size)
{
	int ch;
	register int i=0;
	while(isspace(ch=fgetc(fp)))
		;
	if (ch!='{'){
		printf("Error reading body.\n");
		return -1;
	}
	while((ch=fgetc(fp))!='}'){
		if (ch==EOF){
			printf("Reached end of file.\n");
			return -2;
		}
		if (i>body_size){
			printf("Buffer overrun.\n");
			return -3;
		}
		body[i]=ch;
		i++;
	}
	body[i]='\0';
	return i;
}


