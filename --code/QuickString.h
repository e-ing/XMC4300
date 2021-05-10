#ifndef QUICK_STRING_H
#define QUICK_STRING_H

#include <stdio.h>
#include <string.h>


class QuickStr
{
private:
	unsigned int sz;// , pos;
	char* xStr;
	char* str0;
public:
	QuickStr() : sz(0)
	{
		xStr = new char[1];
		xStr[0] = 0;
		str0 = xStr;
	}

	QuickStr(const char* str) :
	sz( strlen(str) + 1 )
	{
		xStr = new char[sz + 1];
		for (int i = sz - 1; i >= 0; --i)
			xStr[i] = str[i];
		xStr[sz] = 0;
		str0 = xStr;
	}

	QuickStr(int val)
	{
		char txV[16];
		sprintf(txV, "%d", val);
		sz = strlen(txV) + 1;
		xStr = new char[sz + 1];
		for (int i = sz - 1; i >= 0; --i)
			xStr[i] = txV[i];
		xStr[sz] = 0;
		str0 = xStr;
	}

	QuickStr(unsigned long val) 
	{
		char txV[16];
		sprintf(txV, "%x", (int) val);
		sz = strlen(txV) + 1;
			xStr = new char[sz + 1];
		for (int i = sz - 1; i >= 0; --i)
			xStr[i] = txV[i];
		xStr[sz] = 0;
		str0 = xStr;
	}

	QuickStr(double val)
	{
		char txV[32];
		sprintf(txV, "%.4f", val);
		sz = strlen(txV) + 1;
		xStr = new char[sz + 1];
		for (int i = sz - 1; i >= 0; --i)
			xStr[i] = txV[i];
		xStr[sz] = 0;
		str0 = xStr;
	}

	QuickStr(bool val)
	{
		const char TX_TR[] = "TRUE";
		const char TX_FL[] = "FALSE";
		const char* ptr = val ? TX_TR : TX_FL;
		sz = strlen(ptr) + 1;
		xStr = new char[sz + 1];
		for (int i = sz - 1; i >= 0; --i)
			xStr[i] = ptr[i];
		xStr[sz] = 0;
		str0 = xStr;
	}

	QuickStr(const QuickStr& any)
	{
		sz = any.sz;
		xStr = new char[sz + 1];
		str0 = xStr;
		for (int i = sz; i >= 0; --i)
			xStr[i] = any.xStr[i];
	}

	QuickStr& operator = (const QuickStr& any)
	{
		if (str0 != NULL)
			delete[] str0;
		sz = any.sz;
		xStr = new char[sz + 1];
		for (int i = sz; i >= 0; --i)
			xStr[i] = any.xStr[i];
		str0 = xStr;
		return *this;
	}
//Discard n elements from the beginning of the string 
	void CutOff ( unsigned int nnn )
	{ 	
		if (sz > 0)
		{
			nnn = (nnn > sz)? sz : nnn;
			sz -= nnn;
			xStr += nnn;
		}
	}
	unsigned int Size() { return sz; }
	bool NotEmpty() { return (sz > 0); }
	bool Empty() { return (sz == 0); }
	operator const char* ()
	{
		return xStr;
	}

	~QuickStr() 
	{
		delete[] str0;
	}
};

#endif
