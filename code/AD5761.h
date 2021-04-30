#ifndef AD5761_H
#define AD5761_H
#include <AbstractIfcs.h>



class AD5761 : public Abstract_oInt
{
protected:
	virtual void SetVal(int val) = 0;
	Abstract_oBit* pinLoad;
public:
	AD5761(unsigned char usicN, unsigned char chan, Abstract_oBit &loadPin );
	virtual ~AD5761(){}
};

#endif
