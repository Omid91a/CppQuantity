#include "Quantity.h"

#include <cassert>
#include <iostream>

void QFrequency_TEST()
{

	QFrequency f2(10e6, QFrequency::QuantityUnit::QT_Hz);
	assert(f2.MHz() == 10);
	assert(f2.GHz() == 0.01);
	assert(f2.KHz() == 10e3);
	assert(f2.Hz() == 10e6);

	QFrequency f3(10e3, QFrequency::QuantityUnit::QT_KHz);
	assert(f3.MHz() == 10);
	assert(f3.GHz() == 0.01);
	assert(f3.KHz() == 10e3);
	assert(f3.Hz() == 10e6);

	QFrequency f1(10); // default is mhz
	assert(f1.MHz() == 10);
	assert(f1.GHz() == 0.01);
	assert(f1.KHz() == 10e3);
	assert(f1.Hz() == 10e6);

	QFrequency f4(0.01, QFrequency::QuantityUnit::QT_GHz);
	assert(f4.MHz() == 10);
	assert(f4.GHz() == 0.01);
	assert(f4.KHz() == 10e3);
	assert(f4.Hz() == 10e6);
}

void QSignalLevel_TEST()
{
	QSignalLevel s1(30);
	assert(s1.dBm() == 30);
	assert(s1.dB() == 0);
	assert(s1.Wat() == 1);
	assert(s1.mWat() == 1e3);
	assert(s1.volt() == 1);

	QSignalLevel s2(1,QSignalLevel::QuantityUnit::QT_Wat);
	assert(s2.dBm() == 30);
	assert(s2.dB() == 0);
	assert(s2.Wat() == 1);
	assert(s2.mWat() == 1e3);
	assert(s2.volt() == 1);

	QSignalLevel s3(1000, QSignalLevel::QuantityUnit::QT_mWat);
	assert(s3.dBm() == 30);
	assert(s3.dB() == 0);
	assert(s3.Wat() == 1);
	assert(s3.mWat() == 1e3);
	assert(s3.volt() == 1);

	QSignalLevel s4(1, QSignalLevel::QuantityUnit::QT_Volt);
	//assert(s4.dBm() == 30);
	assert(s4.dB() == 0);
	assert(s4.Wat() == 1);
	assert(s4.mWat() == 1e3);
	assert(s4.volt() == 1);
}

int main()
{
	QFrequency_TEST();
	QSignalLevel_TEST();
	return 0;
}