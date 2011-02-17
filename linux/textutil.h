/* 
 * textutil.h
 * Utility for manipulating strings, as well as transformation 
 * of encoding. 
 * Uses WIN32 API!!
 */
#ifndef TEXTUTIL_H
#define TEXTUTIL_H

#define STRMAX 50
void readline(char *dest);
void read_utf_to_950(const char *src, char *dest);
void read_950_to_utf(const char *src, char *dest);

#endif
