#include "Quantity.h"

#include <cassert>
#include <iostream>

void QFrequency_TEST()
{
	std::cout << std::endl << "Test Case1: QFrequency [Running]" << std::endl;
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

	std::cout << "Test Case1: QFrequency [Pass]" << std::endl;
}

void QSignalLevel_TEST()
{
	std::cout << std::endl << "Test Case2: QSignalLevel [Running]" << std::endl;
	QSignalLevel s1(30);
	assert(s1.dBm() == 30);
	assert(s1.dB() == 0);
	assert(s1.Wat() == 1);
	assert(s1.mWat() == 1e3);
	assert(s1.volt() == 1);

	QSignalLevel s2(1, QSignalLevel::QuantityUnit::QT_Wat);
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
	assert(s4.dBm() == 30);
	assert(s4.dB() == 0);
	assert(s4.Wat() == 1);
	assert(s4.mWat() == 1e3);
	assert(s4.volt() == 1);

	std::cout << "Test Case2: QSignalLevel [Pass]" << std::endl;
}

void QTimes_TEST()
{
	std::cout << std::endl << "Test Case3: QTimes [Running]" << std::endl;

	QTimes t1(1, QTimes::QuantityUnit::QT_S);
	assert(t1.S(), 1);
	assert(t1.mS(), 1e3);
	assert(t1.uS(), 1e6);
	assert(t1.nS(), 1e9);
	assert(t1.pS(), 1e12);

	QTimes t2(1e3, QTimes::QuantityUnit::QT_mS);
	assert(t2.S(), 1);
	assert(t2.mS(), 1e3);
	assert(t2.uS(), 1e6);
	assert(t2.nS(), 1e9);
	assert(t2.pS(), 1e12);

	QTimes t3(1e6, QTimes::QuantityUnit::QT_uS);
	assert(t3.S(), 1);
	assert(t3.mS(), 1e3);
	assert(t3.uS(), 1e6);
	assert(t3.nS(), 1e9);
	assert(t3.pS(), 1e12);

	QTimes t4(1e9, QTimes::QuantityUnit::QT_nS);
	assert(t4.S(), 1);
	assert(t4.mS(), 1e3);
	assert(t4.uS(), 1e6);
	assert(t4.nS(), 1e9);
	assert(t4.pS(), 1e12);

	QTimes t5(1e12, QTimes::QuantityUnit::QT_pS);
	assert(t5.S(), 1);
	assert(t5.mS(), 1e3);
	assert(t5.uS(), 1e6);
	assert(t5.nS(), 1e9);
	assert(t5.pS(), 1e12);

	std::cout << "Test Case3: QTimes [Pass]" << std::endl;
}

void QAngleSpeed_TEST()
{
	std::cout << std::endl << "Test Case4: QAngleSpeed [Running]" << std::endl;

	QAngleSpeed as1(1);
	assert((as1.DpS() - 1) < FLT_EPSILON);
	assert((as1.mDpS() - 1000) < FLT_EPSILON);
	assert((as1.DpM() - 60) < FLT_EPSILON);
	assert((as1.mDpM() - 6e4) < FLT_EPSILON);
	assert((as1.DpH() - 3600) < FLT_EPSILON);
	assert((as1.mDpH() - 3.6e6) < FLT_EPSILON);
	assert((as1.RPM() - 1 / 6.0) < FLT_EPSILON);

	QAngleSpeed as2(1000, QAngleSpeed::QuantityUnit::QT_mDpS);
	assert((as2.DpS() - 1) < FLT_EPSILON);
	assert((as2.mDpS() - 1000) < FLT_EPSILON);
	assert((as2.DpM() - 60) < FLT_EPSILON);
	assert((as2.mDpM() - 6e4) < FLT_EPSILON);
	assert((as2.DpH() - 3600) < FLT_EPSILON);
	assert((as2.mDpH() - 3.6e6) < FLT_EPSILON);
	assert((as2.RPM() - 1 / 6.0) < FLT_EPSILON);

	QAngleSpeed as3(60, QAngleSpeed::QuantityUnit::QT_DpM);
	assert((as3.DpS() - 1) < FLT_EPSILON);
	assert((as3.mDpS() - 1000) < FLT_EPSILON);
	assert((as3.DpM() - 60) < FLT_EPSILON);
	assert((as3.mDpM() - 6e4) < FLT_EPSILON);
	assert((as3.DpH() - 3600) < FLT_EPSILON);
	assert((as3.mDpH() - 3.6e6) < FLT_EPSILON);
	assert((as3.RPM() - 1 / 6.0) < FLT_EPSILON);

	QAngleSpeed as4(6e4, QAngleSpeed::QuantityUnit::QT_mDpM);
	assert((as4.DpS() - 1) < FLT_EPSILON);
	assert((as4.mDpS() - 1000) < FLT_EPSILON);
	assert((as4.DpM() - 60) < FLT_EPSILON);
	assert((as4.mDpM() - 6e4) < FLT_EPSILON);
	assert((as4.DpH() - 3600) < FLT_EPSILON);
	assert((as4.mDpH() - 3.6e6) < FLT_EPSILON);
	assert((as4.RPM() - 1 / 6.0) < FLT_EPSILON);

	QAngleSpeed as5(3600, QAngleSpeed::QuantityUnit::QT_DpH);
	assert((as5.DpS() - 1) < FLT_EPSILON);
	assert((as5.mDpS() - 1000) < FLT_EPSILON);
	assert((as5.DpM() - 60) < FLT_EPSILON);
	assert((as5.mDpM() - 6e4) < FLT_EPSILON);
	assert((as5.DpH() - 3600) < FLT_EPSILON);
	assert((as5.mDpH() - 3.6e6) < FLT_EPSILON);
	assert((as5.RPM() - 1 / 6.0) < FLT_EPSILON);

	QAngleSpeed as6(3.6e6, QAngleSpeed::QuantityUnit::QT_mDpH);
	assert((as6.DpS() - 1) < FLT_EPSILON);
	assert((as6.mDpS() - 1000) < FLT_EPSILON);
	assert((as6.DpM() - 60) < FLT_EPSILON);
	assert((as6.mDpM() - 6e4) < FLT_EPSILON);
	assert((as6.DpH() - 3600) < FLT_EPSILON);
	assert((as6.mDpH() - 3.6e6) < FLT_EPSILON);
	assert((as6.RPM() - 1 / 6.0) < FLT_EPSILON);

	QAngleSpeed as7(0.1666, QAngleSpeed::QuantityUnit::QT_RPM);
	assert((as7.DpS() - 1) < FLT_EPSILON);
	assert((as7.mDpS() - 1000) < FLT_EPSILON);
	assert((as7.DpM() - 60) < FLT_EPSILON);
	assert((as7.mDpM() - 6e4) < FLT_EPSILON);
	assert((as7.DpH() - 3600) < FLT_EPSILON);
	assert((as7.mDpH() - 3.6e6) < FLT_EPSILON);
	assert((as7.RPM() - 1 / 6.0) < FLT_EPSILON);

	std::cout << "Test Case4: QAngleSpeed [Pass]" << std::endl;
}

int main()
{
	QFrequency_TEST();
	QSignalLevel_TEST();
	QTimes_TEST();
	QAngleSpeed_TEST();
	return 0;
}