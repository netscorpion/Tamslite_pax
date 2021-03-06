#ifndef  _DEBUG_H
#define _DEBUG_H

#define LOG_HEX_PRINTF(a,b,c)   log_hex_printf(__FILE__,__LINE__,a,b,c)

char *DebugMessage;

void log_hex_printf (char*a_szFile, long a_lLine, char* a_szMessage, unsigned char* a_ucBuffer, short a_sBufferLen);
void SendDebug(const char *message);

void LOG_PRINTF(char *message ,...);


#endif