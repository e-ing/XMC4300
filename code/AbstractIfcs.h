#ifndef ABSTRACT_IFCS_H
#define ABSTRACT_IFCS_H
#include  <QuickString.h>
//v2-09.04.21
//input
class Abstract_iPort
{
public:
	virtual Abstract_iPort& operator >> (void* any) = 0;
	virtual ~Abstract_iPort() {}
};

//GPin and etc
class Abstract_iBit : public  Abstract_iPort
{
protected:
	virtual bool GetState() = 0;
public:
	virtual Abstract_iPort& operator >> (void* any)
	{
		*((bool*)any) = GetState();
		return *this;
	}
	virtual operator bool() { return GetState(); }
	virtual operator int() { return (GetState() == false) ? 0 : 1; };
	virtual void PullH() = 0;
	virtual void PullD() = 0;
	virtual void PushPull() =0;
	virtual void SetSpeed(unsigned int speed) = 0;
	virtual ~Abstract_iBit() {}
};

//ADCs  and etc
class Abstract_iInt : public  Abstract_iPort
{
protected:
	virtual int GetValue() = 0;
public:
	virtual Abstract_iPort& operator >> (void* any)
	{
		*((int*)any) = GetValue();
		return *this;
	}
	virtual operator int() { return GetValue(); }
	virtual ~Abstract_iInt() {}
};

//Serial ports in and etc
class Abstract_iString : public  Abstract_iPort
{
protected:
	unsigned int sz;
	char* bfr;
	virtual unsigned int GetStr(char* buff) = 0;
public:
	virtual Abstract_iPort& operator >> (void* any)
	{
		sz = GetStr((char*) any);
		return *this;
	}
	virtual operator char* ()
 {
		sz = GetStr(bfr);
		return bfr;
 }
	virtual unsigned int GetDataLen() = 0;
	virtual ~Abstract_iString() {}
};

////Memorys in  and etc

class Abstract_iArray : public  Abstract_iPort
{
	unsigned int index;
	unsigned int rdSz;
	virtual unsigned int GetData(unsigned int idx, void* data, unsigned int sz) = 0;
	virtual unsigned int GetData(unsigned int idx) = 0;
public:
	virtual void SetIdx(unsigned int idx) { index = idx; }
	virtual unsigned int operator[] (unsigned int idx)
	{
		return GetData(index);
	}
	virtual unsigned int GetIdx() { return index; }
	void SetSz(unsigned int sz) { rdSz = sz; }
	virtual Abstract_iPort& operator >> (void* any) 
	{
			GetData(index, any, rdSz);
		return *this;
	}

	virtual operator int()
	{
		return GetData(index);
	}
	virtual ~Abstract_iArray() {}
};
//out
class Abstract_oPort
{
public:
	virtual Abstract_oPort& operator << (void* any) = 0;
	virtual ~Abstract_oPort() {}
};

//GPout and etc
class Abstract_oBit : public  Abstract_oPort
{
protected:
	virtual bool GetState() = 0;
	virtual void SetValue( bool x) =0;
	virtual void Toggle () = 0;
	virtual void SetState(void* state)
	{
		SetValue(*((bool*) state));
	}
public:
	virtual void Set() = 0;
	virtual void Clear() = 0;
	virtual void SetSpeed(unsigned int speed) = 0;
	
	virtual Abstract_oPort& operator << (void* any)
	{
		SetState(any);
		return *this;
	}
	virtual operator bool() { return GetState(); }
	virtual operator int() { return (GetState() == false) ? 0 : 1; };
	virtual Abstract_oBit&  operator = (bool val) 
	{
		SetValue(val);
		return *this;
	} 
	
	virtual void StSt(bool st) {SetValue(st);} 
	
	virtual Abstract_oBit& operator = (int val) 
	{
		SetValue((val==0)? false : true);
		return *this;
	}
	virtual Abstract_oBit& operator !()
	{
		Toggle();
		return *this;
	}
	virtual void SetPushPull() = 0;
	virtual void SetOpenDr() = 0; 
	virtual void SetAltFn(unsigned  long funcN) = 0;
	virtual ~Abstract_oBit() {}
};

class Abstract_oInt// : public  Abstract_oPort
{
protected:
	int lastVal;
	virtual void SetVal(int val) = 0;
public:
	virtual operator int () {return lastVal;}
	virtual Abstract_oInt&  operator = (int val) { SetVal(val); return *this;}
	virtual Abstract_oInt&  operator = (const Abstract_oInt &any) { *this = any.lastVal; return *this;}
	virtual Abstract_oInt& operator += (int val) { SetVal(lastVal + val); return *this;}
	virtual Abstract_oInt& operator -= (int val) { SetVal(lastVal + val); return *this;}
	
//	virtual Abstract
};


//serial ports in and etc

//#include <iostream>
//#include <sstream> 
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>





#include <list>
using namespace std;
class Abstract_oString
{
protected:
	list<QuickStr> bigBuff;
	QuickStr cash;
	virtual void PushBuffer(QuickStr &qst) = 0;
public:
//	virtual Abstract_oString& operator << (const string str);
	virtual Abstract_oString& operator << (QuickStr str);
//	{
//		SendStr((char*) any);
//		return *this;
//	}

	virtual unsigned int GetBuffLen() = 0;
	virtual ~Abstract_oString() {}
};

#endif

