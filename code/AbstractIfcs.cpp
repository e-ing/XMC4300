//#include <sstream>

#include <AbstractIfcs.h>

//using namespace std;

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

Abstract_oString& Abstract_oString::operator << (const char* str)
{
	//string stStr = str;
	//return *this << stStr;
	
		if( str != NULL )	
			for	(int i = sizeof(str); i > 0; )
				bigBuff.push_back(str[--i]);
////		bigBuff.push_back(str);
		if( !bigBuff.empty() )
			if( sizeof(cashBuff) == 0  )
			{
				  
					list<int>::iterator it = bigBuff.begin();
					cash [0] = *it;
					bigBuff.pop_front();
					c_cashBuff = PushBuffer(cashBuff);
			}
	
	return *this;
}
Abstract_oString& Abstract_oString::operator << (int val)
{
//	ostringstream oStr;
//	oStr << val;
//	string stStr = oStr.str();
//	return *this << stStr;
	return *this;
}
Abstract_oString& Abstract_oString::operator << (unsigned long val)
{
//	ostringstream oStr;
//	oStr << hex << val;
//	string stStr = oStr.str();
//	return *this << stStr;
	return *this;
}
Abstract_oString& Abstract_oString::operator << (double val)
{
//	ostringstream oStr;
//	oStr << val;
//	string stStr = oStr.str();
//	return *this << stStr;
	return *this;
}
Abstract_oString& Abstract_oString::operator << (bool val)
{
//	string stStr = val? "TRUE" : "FALSE";
//	return *this << stStr;
	return *this;
}
