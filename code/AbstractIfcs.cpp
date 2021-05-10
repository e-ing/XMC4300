//#include <sstream>

#include <AbstractIfcs.h>

using namespace std;

//Abstract_oString& Abstract_oString::operator << (const string str)
//{
////	if( !str.empty() ) 
////		bigBuff.push_back(str);
////	if( !bigBuff.empty() )
////		if( cashBf.empty() )
////		{
////			list<string>::iterator it = bigBuff.begin();
////			cashBf = *it;
////			bigBuff.pop_front();
////			cashBf = PushBuffer(cashBf);
////		}
//	return *this;
//}

bool AbstrBitIn::operator == (bool val) const {return GetState() == val;}
bool AbstrBitIn::operator == (AbstrBitIn& other) const {return GetState() == other.GetState();}
bool AbstrBitIn::operator == (AbstrBitOut& outP) const {return GetState() == (bool) outP;}
bool AbstrBitIn::operator != (bool val) const {return GetState() != val;}
bool AbstrBitIn::operator != (AbstrBitOut& outP) const {return GetState() != (bool) outP;}
bool AbstrBitIn::operator != (AbstrBitIn& other) const {return GetState() != other.GetState();}	


Abstract_oString& Abstract_oString::operator << (QuickStr str)
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

