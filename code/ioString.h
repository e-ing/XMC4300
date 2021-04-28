#ifndef IO_STRING_H
#define IO_STRING_H
#include <AbstractIfcs.h>
#include <USIC.h>


//serial ports in and etc
class InStr : public Abstract_iString
{
private:
	static const int MAX_BUFF_SZ = 64;
	USIC_CH_TypeDef* uart;
	unsigned short tmpBuff[MAX_BUFF_SZ];
protected:
	virtual unsigned int GetStr(char* buff);
public:
	InStr ( unsigned char usicN, unsigned char chan,
				  unsigned long wLen, unsigned long frLen);
	virtual unsigned int GetDataLen();
	virtual ~InStr() {}
};

//serial ports in and etc
class OutStr : public Abstract_oString
{
protected:
	USIC_CH_TypeDef* uart;
	virtual const char* PushBuffer(const char* str);
//	virtual unsigned int SendStr(char* buff);
public:
	OutStr ( unsigned char usicN, unsigned char chan,
				  unsigned long wLen, unsigned long frLen);
	virtual unsigned int GetBuffLen();
	virtual ~OutStr() {}
};

#endif
