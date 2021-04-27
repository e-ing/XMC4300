#ifndef IO_STRING_H
#define IO_STRING_H
#include <AbstractIfcs.h>
#include <USIC.h>

//serial ports in and etc
class InStr : public Abstract_iString
{
protected:
	virtual unsigned int GetStr(char* buff);
public:
	InStr ( unsigned char usicN, unsigned char chan,
				  unsigned long wLen, unsigned long frLen);
	virtual unsigned int GetDataLen();
	virtual ~InStr() {}
};

#endif
