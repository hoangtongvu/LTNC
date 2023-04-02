#include "TEST_CLASS.h"



TESS_CLASS::TESS_CLASS(int _value)
{
	value = _value;
}


void TESS_CLASS::TestFunc()
{
	cout << value;
}



TESS_CLASS::~TESS_CLASS()
{
}
