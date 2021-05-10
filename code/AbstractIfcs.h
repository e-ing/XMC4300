#ifndef ABSTRACT_IFCS_H
#define ABSTRACT_IFCS_H
#include  <QuickString.h>
//v2-09.04.21
//input

class AbstrBitOut;

class Abstract_iPort
{
public:
	virtual Abstract_iPort& operator >> (void* any) = 0;
	virtual ~Abstract_iPort() {}
};

//GPin and etc
class AbstrBitIn : public  Abstract_iPort
{
protected:
	virtual bool GetState() const = 0;
public:
	virtual Abstract_iPort& operator >> (void* any)
	{
		*((bool*)any) = GetState();
		return *this;
	}
	virtual operator bool() const { return GetState(); }
	virtual operator int() const { return (GetState() == false) ? 0 : 1; };
	virtual void PullH() = 0;
	virtual void PullD() = 0;
	virtual void PushPull() = 0;
	virtual void SetSpeed(unsigned int speed) = 0;
	
	virtual bool operator == (bool val) const;// {return GetState() == val;}
	virtual bool operator == (AbstrBitIn& other) const;//  {return GetState() == other.GetState();}
	virtual bool operator == (AbstrBitOut& outP) const;//  {return GetState() == (bool) outP;}
	virtual bool operator != (bool val) const;//  {return GetState() != val;}
	virtual bool operator != (AbstrBitOut& outP) const;//  {return GetState() != (bool) outP;}
	virtual bool operator != (AbstrBitIn& other) const;//  {return GetState() != other.GetState();}	
	virtual ~AbstrBitIn() {}
};

//ADCs  and etc
class AbstrIntIn : public  Abstract_iPort
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
	virtual ~AbstrIntIn() {}
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

class AbstrBitOut 
{
protected:	
	virtual bool GetState() const = 0;
	virtual void SetState( bool val)  = 0;
	virtual void Toggle() = 0;
	virtual void Set() = 0;
	virtual void Clear() = 0;
public:
	virtual void SetSpeed(unsigned int speed) = 0;
	virtual void SetPushPull() = 0;
	virtual void SetOpenDr() = 0; 
	virtual void SetAltFn(unsigned  long funcN) = 0;

	virtual AbstrBitOut& operator = (const AbstrBitOut& other) 
	{
		SetState(other.GetState());
		return *this;
	}
	
	virtual AbstrBitOut& operator = (const AbstrBitIn& inPin) 
	{
		SetState((bool) inPin);
		return *this;
	}
	
	virtual AbstrBitOut& operator = (int val) 
	{
		SetState((val > 0)? true : false);
		return *this;
	}
	
	virtual AbstrBitOut&  operator = (bool val) 
	{
		SetState(val);
		return *this;
	} 
	
	virtual operator int() const { return (GetState() == false) ? 0 : 1; };
	virtual operator bool() const { return GetState(); }
	virtual bool operator == (bool val) const {return GetState() == val;}
	virtual bool operator == (AbstrBitOut& other) const {return GetState() == other.GetState();}
	virtual bool operator == (AbstrBitIn& inp) const {return GetState() == (bool) inp;}
	virtual bool operator != (bool val) const {return GetState() != val;}
	virtual bool operator != (AbstrBitOut& other) const {return GetState() != other.GetState();}
	virtual bool operator != (AbstrBitIn& inp) const {return GetState() != (bool) inp;}
	virtual AbstrBitOut& operator !()
	{
		Toggle();
		return *this;
	}

	virtual ~AbstrBitOut(){} 

};




//class Abstract_oBit : public  Abstract_oPort
//{
//protected:
//	virtual bool GetState() const {return true;};
//	virtual void SetValue( bool x) = 0;
//	virtual void Toggle () = 0;
//	virtual void SetState(void* state)
//	{
//		SetValue(*((bool*) state));
//	}
//public:
//	
//	virtual void Set() = 0;
//	virtual void Clear() = 0;
//	virtual void SetSpeed(unsigned int speed) = 0;
//	
//	virtual Abstract_oPort& operator << (void* any)
//	{
//		SetState(any);
//		return *this;
//	}
//	virtual operator bool() { return GetState(); }
//	virtual operator int() { return (GetState() == false) ? 0 : 1; };
//	virtual Abstract_oBit&  operator = (bool val) 
//	{
//		SetValue(val);
//		return *this;
//	} 
//	
////	virtual Abstract_oBit&  operator = (const Abstract_oBit &other) = 0;
//	
//	virtual void StSt(bool st) {SetValue(st);} 
//	
//	virtual Abstract_oBit& operator = (int val) 
//	{
//		SetValue((val==0)? false : true);
//		return *this;
//	}
//	virtual Abstract_oBit& operator !()
//	{
//		Toggle();
//		return *this;
//	}
//	virtual void SetPushPull() = 0;
//	virtual void SetOpenDr() = 0; 
//	virtual void SetAltFn(unsigned  long funcN) = 0;
//	virtual ~Abstract_oBit() {}
//};

extern const char LOAD[];
extern const char ASYNC_MODE[];
extern const char SYNC_MODE[];

class AbstrIntOut// : public  Abstract_oPort
{
protected:
	int lastVal;
public:
	virtual bool SetVal(int val) = 0;
	virtual operator int () const {return lastVal;}
	virtual AbstrIntOut&  operator = (int val) { SetVal(val); return *this;}
	virtual AbstrIntOut&  operator = (const char* cmd) = 0;
	virtual AbstrIntOut&  operator = (const AbstrIntOut &any) { *this = any.lastVal; return *this;}
	virtual AbstrIntOut& operator += (int val) { SetVal(lastVal + val); return *this;}
	virtual AbstrIntOut& operator -= (int val) { SetVal(lastVal + val); return *this;}
	
	virtual bool operator == (int val) const {return lastVal == val;}
	virtual bool operator == (AbstrIntOut& other) const {return lastVal == other.lastVal;}
	virtual bool operator == (AbstrIntIn& inp) const {return lastVal  == (int) inp;}
	virtual bool operator != (int val) const {return lastVal != val;}
	virtual bool operator != (AbstrIntOut& other) const {return lastVal != other.lastVal;}
	virtual bool operator != (AbstrIntIn& inp) const {return lastVal  != (int) inp;}
	
	virtual bool operator > (int val) const {return lastVal > val;}
	virtual bool operator > (AbstrIntOut& other) const {return lastVal > other.lastVal;}
	virtual bool operator > (AbstrIntIn& inp) const {return lastVal  > (int) inp;}
	virtual bool operator >= (int val) const {return lastVal >= val;}
	virtual bool operator >= (AbstrIntOut& other) const {return lastVal >= other.lastVal;}
	virtual bool operator >= (AbstrIntIn& inp) const {return lastVal  >= (int) inp;}
	virtual bool operator < (int val) const {return lastVal < val;}
	virtual bool operator < (AbstrIntOut& other) const {return lastVal < other.lastVal;}
	virtual bool operator < (AbstrIntIn& inp) const {return lastVal  < (int) inp;}
	virtual bool operator <= (int val) const {return lastVal <= val;}
	virtual bool operator <= (AbstrIntOut& other) const {return lastVal <= other.lastVal;}
	virtual bool operator <= (AbstrIntIn& inp) const {return lastVal  <= (int) inp;}
	
	
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

//class Xyz
//{
//public:
//	Xyz() {}
////protected:
//	void Any() {}
//};

//class Abc : public Xyz
//{
//private:
//	int yyy;
//	public:
//		Abc () : Xyz() {yyy = 5;}
//		void Some (Xyz &x) {x.Any();}	
//};

#endif

