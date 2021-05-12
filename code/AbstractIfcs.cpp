//#include <sstream>

#include <AbstractIfcs.h>

using namespace std;

bool AbstrBitIn::operator == (bool val) const {return GetState() == val;}
bool AbstrBitIn::operator == (AbstrBitIn& other) const {return GetState() == other.GetState();}
bool AbstrBitIn::operator == (AbstrBitOut& outP) const {return GetState() == (bool) outP;}
bool AbstrBitIn::operator != (bool val) const {return GetState() != val;}
bool AbstrBitIn::operator != (AbstrBitOut& outP) const {return GetState() != (bool) outP;}
bool AbstrBitIn::operator != (AbstrBitIn& other) const {return GetState() != other.GetState();}	

AbstrStrOut& AbstrStrOut::operator << (QuickStr str)
{
	if( str.NotEmpty() ) 
		bigBuff.push_back(str);
	if( !bigBuff.empty() )
		if( cash.Empty() )
		{
			list<QuickStr>::iterator it = bigBuff.begin();
			cash = *it;
			bigBuff.pop_front();
			PushBuffer(cash);
		}
	return *this;
}

//bool AbstrIntIn::operator == (int val) const {return GetValue() == val;}
//bool AbstrIntIn::operator == (AbstrIntOut& out) const {return (int) out == GetValue();}
//bool AbstrIntIn::operator == (AbstrIntIn& other) const {return GetValue() == other.GetValue();}
//bool AbstrIntIn::operator != (int val) const {return GetValue() != val;}
//bool AbstrIntIn::operator != (AbstrIntOut& out) const {return (int) out != GetValue();}
//bool AbstrIntIn::operator != (AbstrIntIn& other) const {return GetValue() != other.GetValue();}

//bool AbstrIntIn::operator > (int val) const {return GetValue() > val;}
//bool AbstrIntIn::operator > (AbstrIntOut& out) const {return (int) out > GetValue();}
//bool AbstrIntIn::operator > (AbstrIntIn& other) const {return GetValue() > other.GetValue();}
//bool AbstrIntIn::operator >= (int val) const {return GetValue() >= val;}
//bool AbstrIntIn::operator >= (AbstrIntOut& out) const {return (int) out >= GetValue();}
//bool AbstrIntIn::operator >= (AbstrIntIn& other) const {return GetValue() >= other.GetValue();}
//bool AbstrIntIn::operator < (int val) const {return GetValue() < val;}
//bool AbstrIntIn::operator < (AbstrIntOut& out) const {return (int) out < GetValue();}
//bool AbstrIntIn::operator < (AbstrIntIn& other) const {return GetValue() < other.GetValue();}
//bool AbstrIntIn::operator <= (int val) const {return GetValue() <= val;}
//bool AbstrIntIn::operator <= (AbstrIntOut& out) const {return (int) out <= GetValue();}
//bool AbstrIntIn::operator <= (AbstrIntIn& other) const {return GetValue() <= other.GetValue();}

