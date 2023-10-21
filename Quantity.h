
#include <math.h>
#include <iostream>
#include <string>
#include <map>
#include <functional>

#define M_PI 3.141592653589793238462643383279502884197
//-----------------------------------------------------------------------------
//								Signal Frequency
//-----------------------------------------------------------------------------
class QFrequency
{
public:
	enum class QuantityUnit
	{
		QT_GHz, QT_MHz, QT_KHz, QT_Hz, _NumberOfUnits
	};
	explicit QFrequency();
	explicit QFrequency(double value, QuantityUnit QType = QuantityUnit::QT_MHz);
	void GHz(double value);
	void MHz(double value);
	void KHz(double value);
	void Hz(double value);

	double GHz()const;
	double MHz()const;
	double KHz()const;
	double Hz()const;

private:
	double GetMount(QuantityUnit return_mode) const;
	std::map<QuantityUnit, double> ValueMap;

	double ConversionMatrix[(int)QuantityUnit::_NumberOfUnits][(int)QuantityUnit::_NumberOfUnits];
	void InitConversionMatrix();

	//operators
public:
	QFrequency operator +(QFrequency t) const
	{
		return QFrequency(this->MHz() + t.MHz());
	}

	QFrequency operator -(QFrequency t) const
	{
		return QFrequency(this->MHz() - t.MHz());
	}

	double operator /(QFrequency t) const
	{
		return this->MHz() / t.MHz();
	}

	QFrequency operator !()
	{
		return QFrequency(!this->Hz(), QuantityUnit::QT_Hz);
	}

	bool operator ==(QFrequency t) const
	{
		return(this->MHz() == t.MHz());
	}

	bool operator >(QFrequency t) const
	{
		return(this->MHz() > t.MHz());
	}

	bool operator <(QFrequency t) const
	{
		return(this->MHz() < t.MHz());
	}

	bool operator >=(QFrequency t) const
	{
		return(this->MHz() >= t.MHz());
	}

	bool operator <=(QFrequency t) const
	{
		return(this->MHz() <= t.MHz());
	}

	bool operator !=(QFrequency t) const
	{
		return(this->MHz() != t.MHz());
	}

	QFrequency operator /(double t) const
	{
		return QFrequency(this->MHz() / t);
	}

	QFrequency operator /(int t) const
	{
		return QFrequency(this->MHz() / t);
	}

	QFrequency operator +(double t) const
	{
		return QFrequency(this->MHz() + t);
	}

	QFrequency operator +(int t) const
	{
		return QFrequency(this->MHz() + t);
	}

	QFrequency operator -(double t) const
	{
		return QFrequency(this->MHz() - t);
	}

	QFrequency operator -(int t) const
	{
		return QFrequency(this->MHz() - t);
	}

	QFrequency operator *(double t) const
	{
		return QFrequency(this->MHz() * t);
	}

	QFrequency operator *(int t) const
	{
		return QFrequency(this->MHz() * t);
	}

	operator std::string()
	{
		return std::to_string(this->MHz());
	}
};

//inline QDebug operator<<(QDebug d, const QFrequency& freq)
//{
//	d.nospace() << "QFrequency(" << freq.MHz() << ") MHz";
//	return d.space();
//}


//-----------------------------------------------------------------------------
//								Signal Level
//-----------------------------------------------------------------------------
class QSignalLevel {
public:
	enum class QuantityUnit
	{
		QT_dBm, QT_dB, QT_Wat, QT_mWat, QT_Volt, _NumberOfUnits
	};
	explicit QSignalLevel();
	explicit QSignalLevel(double value, QuantityUnit QType = QuantityUnit::QT_dBm);
	void dBm(double value);
	void dB(double value);
	void Wat(double value);
	void mWat(double value);
	void volt(double value);

	double dBm()const;
	double dB()const;
	double Wat()const;
	double mWat()const;
	double volt()const;

private:
	double GetMount(QuantityUnit return_mode) const;
	std::map<QuantityUnit, double> ValueMap;

	// I need a matrix of operand, as for calculating needs pow and offset, it's not a simple factor.
	std::function<double(double)> ConversionMatrix[(int)QuantityUnit::_NumberOfUnits][(int)QuantityUnit::_NumberOfUnits];
	void InitConversionMatrix();

	// operators
public:
	QSignalLevel operator +(QSignalLevel t)
	{
		return QSignalLevel(this->dBm() + t.dBm());
	}

	QSignalLevel operator -(QSignalLevel t)
	{
		return QSignalLevel(this->dBm() - t.dBm());
	}

	//   QSignalLevel operator *(QSignalLevel t)
	//   {
	//      return QSignalLevel(this->dBm() * t.dBm());
	//   }

	double operator /(QSignalLevel t)
	{
		return this->dBm() / t.dBm();
	}

	QSignalLevel operator &(QSignalLevel t)
	{
		return QSignalLevel(uint64_t(this->dBm()) & uint64_t(t.dBm()));
	}

	QSignalLevel operator ^(QSignalLevel t)
	{
		return QSignalLevel(uint64_t(this->dBm()) ^ uint64_t(t.dBm()));
	}

	QSignalLevel operator %(QSignalLevel t)
	{
		return QSignalLevel(uint64_t(this->dBm()) % uint64_t(t.dBm()));
	}

	QSignalLevel operator !()
	{
		return QSignalLevel(!this->dBm());
	}

	bool operator ==(QSignalLevel t)
	{
		return(this->dBm() == t.dBm());
	}

	bool operator >(QSignalLevel t)
	{
		return(this->dBm() > t.dBm());
	}

	bool operator <(QSignalLevel t)
	{
		return(this->dBm() < t.dBm());
	}

	bool operator >=(QSignalLevel t)
	{
		return(this->dBm() >= t.dBm());
	}

	bool operator <=(QSignalLevel t)
	{
		return(this->dBm() <= t.dBm());
	}

	bool operator !=(QSignalLevel t)
	{
		return(this->dBm() != t.dBm());
	}

	QSignalLevel operator /(double t)
	{
		return QSignalLevel(this->dBm() / t);
	}

	QSignalLevel operator /(int t)
	{
		return QSignalLevel(this->dBm() / t);
	}

	QSignalLevel operator +(double t)
	{
		return QSignalLevel(this->dBm() + t);
	}

	QSignalLevel operator +(int t)
	{
		return QSignalLevel(this->dBm() + t);
	}

	QSignalLevel operator -(double t)
	{
		return QSignalLevel(this->dBm() - t);
	}

	QSignalLevel operator -(int t)
	{
		return QSignalLevel(this->dBm() - t);
	}

	QSignalLevel operator *(double t)
	{
		return QSignalLevel(this->dBm() * t);
	}

	QSignalLevel operator *(int t)
	{
		return QSignalLevel(this->dBm() * t);
	}

	operator std::string()
	{
		return(std::to_string(this->dBm()));
	}
};

//inline std::cout operator<<(std::cout d, const QSignalLevel& power)
//{
//   d.nospace() << "QSignalLevel(" << power.dBm() << ") dBm";
//   return d.space();
//}


//-----------------------------------------------------------------------------
//								Time
//-----------------------------------------------------------------------------
class QTimes
{
public:
	enum class QuantityUnit
	{
		QT_S, QT_mS, QT_uS, QT_nS, QT_pS, _NumberOfUnits
	};
	explicit QTimes();
	explicit QTimes(double value, QuantityUnit QType = QuantityUnit::QT_mS);
	void S(double value);
	void mS(double value);
	void uS(double value);
	void nS(double value);
	void pS(uint64_t value);

	double S()const;
	double mS()const;
	double uS()const;
	double nS()const;
	uint64_t pS()const;

private:
	QuantityUnit _asToDoubleType = QuantityUnit::QT_mS;
	double GetMount(QuantityUnit return_mode) const;

	std::map<QuantityUnit, double> ValueMap;

	double ConversionMatrix[(int)QuantityUnit::_NumberOfUnits][(int)QuantityUnit::_NumberOfUnits];
	void InitConversionMatrix();
	// operators
public:
	QTimes operator +(QTimes t)
	{
		return QTimes(this->mS() + t.mS());
	}

	QTimes operator -(QTimes t)
	{
		return QTimes(this->mS() - t.mS());
	}

	//   QTimes operator *(QTimes t)
	//   {
	//      return QTimes(this->mS() * t.mS());
	//   }

	double operator /(QTimes t)
	{
		return this->mS() / t.mS();
	}

	QTimes operator &(QTimes t)
	{
		return QTimes(uint64_t(this->mS()) & uint64_t(t.mS()));
	}

	QTimes operator ^(QTimes t)
	{
		return QTimes(uint64_t(this->mS()) ^ uint64_t(t.mS()));
	}

	QTimes operator %(QTimes t)
	{
		return QTimes(uint64_t(this->mS()) % uint64_t(t.mS()));
	}

	QTimes operator !()
	{
		return QTimes(!this->mS());
	}

	bool operator ==(QTimes t)
	{
		return(this->mS() == t.mS());
	}

	bool operator >(QTimes t)
	{
		return(this->mS() > t.mS());
	}

	bool operator <(QTimes t)
	{
		return(this->mS() < t.mS());
	}

	bool operator >=(QTimes t)
	{
		return(this->mS() >= t.mS());
	}

	bool operator <=(QTimes t)
	{
		return(this->mS() <= t.mS());
	}

	bool operator !=(QTimes t)
	{
		return(this->mS() != t.mS());
	}

	QTimes operator /(double t)
	{
		return QTimes(this->mS() / t);
	}

	QTimes operator /(int t)
	{
		return QTimes(this->mS() / t);
	}

	QTimes operator +(double t)
	{
		return QTimes(this->mS() + t);
	}

	QTimes operator +(int t)
	{
		return QTimes(this->mS() + t);
	}

	QTimes operator -(double t)
	{
		return QTimes(this->mS() - t);
	}

	QTimes operator -(int t)
	{
		return QTimes(this->mS() - t);
	}

	QTimes operator *(double t)
	{
		return QTimes(this->mS() * t);
	}

	QTimes operator *(int t)
	{
		return QTimes(this->mS() * t);
	}

	operator std::string()
	{
		return(std::to_string(this->uS()));
	}

	//QDateTime toDateTime()
	//{
	//   return QDateTime::fromMSecsSinceEpoch(this->S()).toUTC();
	//}

	std::string getTimeDurationString()
	{
		QTimes timeTemp(this->mS());
		double    hours = timeTemp.S() / 3600;

		hours = hours < 0 ? 0 : hours;
		timeTemp.S(timeTemp.S() - (hours * 3600));
		double mins = timeTemp.S() / 60;

		mins = mins < 0 ? 0 : mins;
		timeTemp.S(timeTemp.S() - (mins * 60));
		int seconds = timeTemp.S();
		char* buf;
		//sprintf(buf, "%d:%d:%d", hours, mins, seconds);
		return "";
	}
};

//inline QDebug operator<<(QDebug d, const QTimes& time)
//{
//   d.nospace() << "QTimes(" << QString::number(time.mS(), 'f', 6) << ") mS";
//   return d.space();
//}


//-----------------------------------------------------------------------------
//								Angular Speed
//-----------------------------------------------------------------------------
class QAngleSpeed
{
public:
	enum class QuantityUnit
	{
		QT_DpS, QT_mDpS, QT_DpM, QT_mDpM, QT_DpH, QT_mDpH, QT_RPM, _NumberOfUnits
	};
	explicit QAngleSpeed();
	explicit QAngleSpeed(double value, QuantityUnit QType = QuantityUnit::QT_DpS);
	void DpS(double value);
	void mDpS(double value);
	void DpH(double value);
	void mDpH(double value);

	double DpS()const;
	double DpM()const;
	double DpH()const;
	double mDpS()const;
	double mDpM()const;
	double mDpH()const;
	double RPM();

private:
	QuantityUnit _mountType = QuantityUnit::QT_DpH;
	QuantityUnit _asToDoubleType = QuantityUnit::QT_DpS;
	double GetMount(QuantityUnit returnMode) const;

	std::map<QuantityUnit, double> ValueMap;

	double ConversionMatrix[(int)QuantityUnit::_NumberOfUnits][(int)QuantityUnit::_NumberOfUnits];
	void InitConversionMatrix();
	// operators
public:
	QAngleSpeed operator +(QAngleSpeed t)
	{
		return QAngleSpeed(this->DpS() + t.DpS());
	}

	QAngleSpeed operator -(QAngleSpeed t)
	{
		return QAngleSpeed(this->DpS() - t.DpS());
	}

	QAngleSpeed operator *(QAngleSpeed t)
	{
		return QAngleSpeed(this->DpS() * t.DpS());
	}

	QAngleSpeed operator /(QAngleSpeed t)
	{
		return QAngleSpeed(this->DpS() / t.DpS());
	}

	QAngleSpeed operator &(QAngleSpeed t)
	{
		return QAngleSpeed(uint64_t(this->DpS()) & uint64_t(t.DpS()));
	}

	QAngleSpeed operator ^(QAngleSpeed t)
	{
		return QAngleSpeed(uint64_t(this->DpS()) ^ uint64_t(t.DpS()));
	}

	QAngleSpeed operator %(QAngleSpeed t)
	{
		return QAngleSpeed(uint64_t(this->DpS()) % uint64_t(t.DpS()));
	}

	QAngleSpeed operator !()
	{
		return QAngleSpeed(!this->DpS());
	}

	bool operator ==(QAngleSpeed t) const
	{
		return(this->DpS() == t.DpS());
	}

	bool operator >(QAngleSpeed t) const
	{
		return(this->DpS() > t.DpS());
	}

	bool operator <(QAngleSpeed t) const
	{
		return(this->DpS() < t.DpS());
	}

	bool operator >=(QAngleSpeed t) const
	{
		return(this->DpS() >= t.DpS());
	}

	bool operator <=(QAngleSpeed t) const
	{
		return(this->DpS() <= t.DpS());
	}

	bool operator !=(QAngleSpeed t) const
	{
		return(this->DpS() != t.DpS());
	}

	QAngleSpeed operator /(double t)
	{
		return QAngleSpeed(this->DpS() / t);
	}

	QAngleSpeed operator /(int t)
	{
		return QAngleSpeed(this->DpS() / t);
	}

	QAngleSpeed operator +(double t)
	{
		return QAngleSpeed(this->DpS() + t);
	}

	QAngleSpeed operator +(int t)
	{
		return QAngleSpeed(this->DpS() + t);
	}

	QAngleSpeed operator -(double t)
	{
		return QAngleSpeed(this->DpS() - t);
	}

	QAngleSpeed operator -(int t)
	{
		return QAngleSpeed(this->DpS() - t);
	}

	QAngleSpeed operator *(double t)
	{
		return QAngleSpeed(this->DpS() * t);
	}

	QAngleSpeed operator *(int t)
	{
		return QAngleSpeed(this->DpS() * t);
	}

	operator std::string()
	{
		return std::to_string(this->DpS());
	}
};

//inline QDebug operator<<(QDebug d, const QAngleSpeed& time)
//{
//   d.nospace() << "QAngleSpeed(" << QString::number(time.DpS(), 'f', 3) << ") DpS";
//   return d.space();
//}


//-----------------------------------------------------------------------------
//								Angle
//-----------------------------------------------------------------------------
class QAngle
{
public:
	enum class QuantityUnit
	{
		QT_Deg, QT_mDeg, QT_Rad, _NumberOfUnits
	};
	explicit QAngle();
	explicit QAngle(double value, QuantityUnit QType = QuantityUnit::QT_Deg);
	void Deg(double value);
	void Rad(double value);
	void mDeg(double value);

	double Deg()const;
	double Rad()const;
	double mDeg()const;
	static QAngle Wrap360(QAngle angle);
	static QAngle Wrap180(QAngle angle);
	static QAngle Wrap90(QAngle angle);

private:
	QuantityUnit _mountType = QuantityUnit::QT_Deg;
	QuantityUnit _asToDoubleType = QuantityUnit::QT_Deg;
	double GetMount(QuantityUnit returnMode) const;
	std::map<QuantityUnit, double> ValueMap;

	double ConversionMatrix[(int)QuantityUnit::_NumberOfUnits][(int)QuantityUnit::_NumberOfUnits];
	void InitConversionMatrix();
	// operators
public:
	QAngle operator +(QAngle t)
	{
		return QAngle(this->Deg() + t.Deg());
	}

	QAngle operator -(QAngle t)
	{
		return QAngle(this->Deg() - t.Deg());
	}

	QAngle operator *(QAngle t)
	{
		return QAngle(this->Deg() * t.Deg());
	}

	QAngle operator /(QAngle t)
	{
		return QAngle(this->Deg() / t.Deg());
	}

	QAngle operator &(QAngle t)
	{
		return QAngle(uint64_t(this->Deg()) & uint64_t(t.Deg()));
	}

	QAngle operator ^(QAngle t)
	{
		return QAngle(uint64_t(this->Deg()) ^ uint64_t(t.Deg()));
	}

	QAngle operator %(QAngle t)
	{
		return QAngle(uint64_t(this->Deg()) % uint64_t(t.Deg()));
	}

	QAngle operator !()
	{
		return QAngle(!this->Deg());
	}

	bool operator ==(QAngle t)
	{
		return(this->Deg() == t.Deg());
	}

	bool operator >(QAngle t)
	{
		return(this->Deg() > t.Deg());
	}

	bool operator <(QAngle t)
	{
		return(this->Deg() < t.Deg());
	}

	bool operator >=(QAngle t)
	{
		return(this->Deg() >= t.Deg());
	}

	bool operator <=(QAngle t)
	{
		return(this->Deg() <= t.Deg());
	}

	bool operator !=(QAngle t)
	{
		return(this->Deg() != t.Deg());
	}

	QAngle operator /(double t)
	{
		return QAngle(this->Deg() / t);
	}

	QAngle operator /(int t)
	{
		return QAngle(this->Deg() / t);
	}

	QAngle operator +(double t)
	{
		return QAngle(this->Deg() + t);
	}

	QAngle operator +(int t)
	{
		return QAngle(this->Deg() + t);
	}

	QAngle operator -(double t)
	{
		return QAngle(this->Deg() - t);
	}

	QAngle operator -(int t)
	{
		return QAngle(this->Deg() - t);
	}

	QAngle operator *(double t)
	{
		return QAngle(this->Deg() * t);
	}

	QAngle operator *(int t)
	{
		return QAngle(this->Deg() * t);
	}

	operator std::string()
	{
		return std::to_string(this->Deg());
	}
};

//inline QDebug operator<<(QDebug d, const QAngle& time)
//{
//   d.nospace() << "QAngle(" << QString::number(time.Deg(), 'f', 6) << ") Deg";
//   return d.space();
//}


//-----------------------------------------------------------------------------
//								Ground Speed
//-----------------------------------------------------------------------------
class QGroundSpeed
{
public:
	enum class QuantityUnit
	{
		QT_MPS, QT_KMPS, QT_MPH, QT_KMPH, _NumberOfUnits
	};
	explicit QGroundSpeed();
	explicit QGroundSpeed(double value, QuantityUnit QType = QuantityUnit::QT_KMPH);
	void KMPh(double value);
	void MPh(double value);
	void KMPs(double value);
	void MPs(double value);

	double KMPh()const;
	double MPh()const;
	double KMPs()const;
	double MPs()const;

	// convert quantity to double for some times when you want use in other types like QCPRange
	double toDouble();

	// you can set default type for toDouble method
	void setAsToDoubleType(QuantityUnit type);
	QGroundSpeed::QuantityUnit getAsToDoubleType(QuantityUnit type);

private:
	QuantityUnit _mountType = QuantityUnit::QT_KMPH;
	QuantityUnit _asToDoubleType = QuantityUnit::QT_KMPH;
	double GetMount(QuantityUnit returnMode) const;

	std::map<QuantityUnit, double> ValueMap;

	double ConversionMatrix[(int)QuantityUnit::_NumberOfUnits][(int)QuantityUnit::_NumberOfUnits];
	void InitConversionMatrix();

	// operators
public:
	QGroundSpeed operator +(QGroundSpeed t)
	{
		return QGroundSpeed(this->KMPh() + t.KMPh());
	}

	QGroundSpeed operator -(QGroundSpeed t)
	{
		return QGroundSpeed(this->KMPh() - t.KMPh());
	}

	double operator /(QGroundSpeed t)
	{
		return this->KMPh() / t.KMPh();
	}

	bool operator ==(QGroundSpeed t)
	{
		return(this->KMPh() == t.KMPh());
	}

	bool operator >(QGroundSpeed t)
	{
		return(this->KMPh() > t.KMPh());
	}

	bool operator <(QGroundSpeed t)
	{
		return(this->KMPh() < t.KMPh());
	}

	bool operator >=(QGroundSpeed t)
	{
		return(this->KMPh() >= t.KMPh());
	}

	bool operator <=(QGroundSpeed t)
	{
		return(this->KMPh() <= t.KMPh());
	}

	bool operator !=(QGroundSpeed t)
	{
		return(this->KMPh() != t.KMPh());
	}

	operator std::string()
	{
		return std::to_string(this->KMPh());
	}
};

//-----------------------------------------------------------------------------
//								Distance
//-----------------------------------------------------------------------------
class QDistance
{
public:
	enum class QuantityUnit
	{
		QT_MM, QT_CM, QT_M, QT_KM, QT_Mile, QT_INCH, QT_Foot, _NumberOfUnits
	};
	explicit QDistance();
	explicit QDistance(double value, QuantityUnit QType = QuantityUnit::QT_M);
	void Mm(double value);
	void Cm(double value);
	void M(double value);
	void Km(double value);
	void Mi(double value);
	void Inch(double value);
	void Foot(double value);
	double Mm()const;
	double Cm()const;
	double M()const;
	double Km()const;
	double Mi()const;
	double Inch()const;
	double Foot()const;

private:
	//QT_MM, QT_CM, QT_M, QT_KM, QT_Mile, QT_INCH, QT_Foot, NumberOfUnits
	std::map<QuantityUnit, double> ValueMap;

	double ConversionMatrix[(int)QuantityUnit::_NumberOfUnits][(int)QuantityUnit::_NumberOfUnits];
	void InitConversionMatrix();

	double GetMount(QuantityUnit return_mode) const;

	// operators
public:
	QDistance operator +(QDistance t)
	{
		return QDistance(this->M() + t.M());
	}

	QDistance operator -(QDistance t)
	{
		return QDistance(this->M() - t.M());
	}

	double operator /(QDistance t)
	{
		return this->M() / t.M();
	}

	bool operator ==(QDistance t)
	{
		return(this->M() == t.M());
	}

	bool operator >(QDistance t)
	{
		return(this->M() > t.M());
	}

	bool operator <(QDistance t)
	{
		return(this->M() < t.M());
	}

	bool operator >=(QDistance t)
	{
		return(this->M() >= t.M());
	}

	bool operator <=(QDistance t)
	{
		return(this->M() <= t.M());
	}

	bool operator !=(QDistance t)
	{
		return(this->M() != t.M());
	}
};
//inline QDebug operator<<(QDebug d, const QDistance& dis)
//{
//   d.nospace() << "QDistance(" << dis.Km() << ") KM";
//   return d.space();
//}


//-----------------------------------------------------------------------------
//								Quantity Range
//-----------------------------------------------------------------------------
template<class T>
class QRange
{
public:
	explicit QRange() {}
	explicit QRange(T lower, T upper);

	void setLower(T lower);
	void setUpper(T upper);
	void expand(T includeCoord);
	void expand(const QRange<T>& otherRange);

	bool isInRange(T value) { return value > lower() && value < upper(); }
	bool contains(T value) const { return value >= lower_ && value <= upper_; }
	bool contains(QRange<T> range) const { return range.lower_ >= lower_ && range.upper_ <= upper_; }

	T lower()const;
	T upper()const;
	T center()const;
	T size()const;

private:
	T lower_;
	T upper_;

public:
	QRange operator +(double t) { return QRange(this->lower() + t, this->upper() + t); }

	QRange operator +(int t) { return QRange(this->lower() + t, this->upper() + t); }

	QRange operator -(double t) { return QRange(this->lower() - t, this->upper() - t); }

	QRange operator -(int t) { return QRange(this->lower() - t, this->upper() - t); }

	bool operator ==(const QRange& t) const { return(this->lower() == t.lower() && this->upper() == t.upper()); }

	bool operator >(const QRange& t) const { return(this->lower() > t.lower() && this->upper() > t.upper()); }

	bool operator <(const QRange& t) const { return(this->lower() < t.lower() && this->upper() < t.upper()); }

	bool operator >=(const QRange& t) const { return(this->lower() >= t.lower() && this->upper() >= t.upper()); }

	bool operator <=(const QRange& t) const { return(this->lower() <= t.lower() && this->upper() <= t.upper()); }

	bool operator !=(const QRange& t) const { return(this->lower() != t.lower() && this->upper() != t.upper()); }
};
//
//template<typename T>
//inline QDebug operator<<(QDebug d, const QRange<T>& range)
//{
//	if (typeid(T) == typeid(QFrequency))
//	{
//		d.nospace() << "QRange<QFrequency>(" << range.lower() << ", " << range.upper() << ")";
//	}
//	else if (typeid(T) == typeid(QSignalLevel))
//	{
//		d.nospace() << "QRange<QSignalLevel>(" << range.lower() << ", " << range.upper() << ")";
//	}
//	else if (typeid(T) == typeid(QTimes))
//	{
//		d.nospace() << "QRange<QTimes>(" << range.lower() << ", " << range.upper() << ")";
//	}
//	else if (typeid(T) == typeid(QAngle))
//	{
//		d.nospace() << "QRange<QAngle>(" << range.lower() << ", " << range.upper() << ")";
//	}
//	else if (typeid(T) == typeid(QAngleSpeed))
//	{
//		d.nospace() << "QRange<QAngleSpeed>(" << range.lower() << ", " << range.upper() << ")";
//	}
//	else
//	{
//		d.nospace() << "QRange(" << range.lower() << ", " << range.upper() << ")";
//	}
//	return d.space();
//}

