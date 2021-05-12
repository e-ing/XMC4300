#ifndef ABSTRACT_IFCS_H
#define ABSTRACT_IFCS_H
#include  <QuickString.h>
//v2-09.04.21
//input

class AbstrBitOut;
class AbstrIntOut;

//GPin and etc
class AbstrBitIn 
{
protected:
	virtual bool GetState() const = 0;
public:
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
class AbstrIntIn 
{
protected:
	virtual int GetValue() const = 0;
public:
	virtual operator int() const { return GetValue(); }
	
	
	virtual bool operator == (int val) const;
	virtual bool operator == (AbstrIntOut& out) const;
	virtual bool operator == (AbstrIntIn& inp) const;
	virtual bool operator != (int val) const;
	virtual bool operator != (AbstrIntOut& other) const;
	virtual bool operator != (AbstrIntIn& inp) const;
	
	virtual bool operator > (int val) const;
	virtual bool operator > (AbstrIntOut& other) const;
	virtual bool operator > (AbstrIntIn& inp) const;
	virtual bool operator >= (int val) const;
	virtual bool operator >= (AbstrIntOut& other) const;
	virtual bool operator >= (AbstrIntIn& inp) const;
	virtual bool operator < (int val) const;
	virtual bool operator < (AbstrIntOut& other) const;
	virtual bool operator < (AbstrIntIn& inp) const;
	virtual bool operator <= (int val) const;
	virtual bool operator <= (AbstrIntOut& other) const;
	virtual bool operator <= (AbstrIntIn& inp) const;
	
	virtual ~AbstrIntIn() {}
};

template <class Tc, class Tel>
	
class I_ADC
{
protected:
  Tc data;		
public:
	virtual void CnvStart() = 0;
	virtual bool IsCnvReadY() = 0;
	Tel operator []  (unsigned int chan) const {return data[chan];}
	operator Tc () const {return data;}
};

//Serial ports in and etc
class AbstrStrIn
{
protected:
	unsigned int sz;
	char* bfr;
	virtual unsigned int GetStr(char* buff) = 0;
public:
	virtual AbstrStrIn& operator >> (char* any)
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
	virtual ~AbstrStrIn() {}
};

////Memorys in  and etc

//class Abstract_iArray
//{
//	unsigned int index;
//	unsigned int rdSz;
//	virtual unsigned int GetData(unsigned int idx, void* data, unsigned int sz) = 0;
//	virtual unsigned int GetData(unsigned int idx) = 0;
//public:
//	virtual void SetIdx(unsigned int idx) { index = idx; }
//	virtual unsigned int operator[] (unsigned int idx)
//	{
//		return GetData(index);
//	}
//	virtual unsigned int GetIdx() { return index; }
//	void SetSz(unsigned int sz) { rdSz = sz; }
//	virtual Abstract_iArray& operator >> (void* any) 
//	{
//			GetData(index, any, rdSz);
//		return *this;
//	}

//	virtual operator int()
//	{
//		return GetData(index);
//	}
//	virtual ~Abstract_iArray() {}
//};
//out

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

extern const char LOAD[];
extern const char ASYNC_MODE[];
extern const char SYNC_MODE[];

class AbstrIntOut
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
	virtual ~AbstrIntOut() {};
};


//serial ports in and etc

//#include <iostream>
//#include <sstream> 
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>


#include <list>
using namespace std;
class AbstrStrOut
{
protected:
	list<QuickStr> bigBuff;
	QuickStr cash;
	virtual void PushBuffer(QuickStr &qst) = 0;
public:
//	virtual AbstrStrOut& operator << (const string str);
	virtual AbstrStrOut& operator << (QuickStr str);
//	{
//		SendStr((char*) any);
//		return *this;
//	}

	virtual unsigned int GetBuffLen() = 0;
	virtual ~AbstrStrOut() {}
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

