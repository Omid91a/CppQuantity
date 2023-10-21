#include "Quantity.h"

//-----------------------------------------------------------------------------
//								Signal Frequency
//-----------------------------------------------------------------------------

QFrequency::QFrequency()
{
	ValueMap.insert_or_assign(QuantityUnit::QT_MHz, 0);
	InitConversionMatrix();
}


QFrequency::QFrequency(double value, QuantityUnit QType)
{
	ValueMap.insert_or_assign(QType, value);
	InitConversionMatrix();
}


void QFrequency::GHz(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_GHz, value);
}


void QFrequency::MHz(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_MHz, value);
}


void QFrequency::KHz(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_KHz, value);
}


void QFrequency::Hz(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_Hz, value);
}


//----------------------------------------------
double QFrequency::GHz() const
{
	return GetMount(QuantityUnit::QT_GHz);
}


double QFrequency::MHz() const
{
	return GetMount(QuantityUnit::QT_MHz);
}


double QFrequency::KHz() const
{
	return GetMount(QuantityUnit::QT_KHz);
}


double QFrequency::Hz() const
{
	return GetMount(QuantityUnit::QT_Hz);
}

double QFrequency::GetMount(QuantityUnit return_mode)const
{
	// get the setting unit
	auto v = ValueMap.find(return_mode);
	if (v != ValueMap.end())
		return v->second;

	// check the available unit in map
	auto first_item = ValueMap.begin();
	double converted_value = first_item->second * ConversionMatrix[(int)first_item->first][(int)return_mode];

	return converted_value;
}

void QFrequency::InitConversionMatrix()
{
	double conversion_matrix[(int)QuantityUnit::_NumberOfUnits][(int)QuantityUnit::_NumberOfUnits]
	{
		//QT_GHz,  QT_MHz,  QT_KHz,   QT_Hz
		{ 1      , 1e3    , 1e6     , 1e9  }, //QT_GHz
		{ 1e-3   , 1      , 1e3     , 1e6  }, //QT_MHz
		{ 1e-6   , 1e-3   , 1       , 1e3  }, //QT_KHz
		{ 1e-9   , 1e-6   , 1e-3    , 1    }  //QT_Hz
	};

	int end_index = (int)QuantityUnit::_NumberOfUnits - 1;
	std::copy(&conversion_matrix[0][0], &conversion_matrix[end_index][end_index], &ConversionMatrix[0][0]);
}


//-----------------------------------------------------------------------------
//								Signal Level
//-----------------------------------------------------------------------------

QSignalLevel::QSignalLevel()
{
	ValueMap.insert_or_assign(QuantityUnit::QT_dB, 0);
	InitConversionMatrix();
}


QSignalLevel::QSignalLevel(double value, QuantityUnit QType)
{
	ValueMap.insert_or_assign(QType, value);
	InitConversionMatrix();
}


void QSignalLevel::dBm(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_dBm, value);
}


void QSignalLevel::dB(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_dB, value);
}


void QSignalLevel::Wat(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_Wat, value);
}


void QSignalLevel::mWat(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_mWat, value);
}


void QSignalLevel::volt(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_Volt, value);
}


double QSignalLevel::dBm() const
{
	return GetMount(QuantityUnit::QT_dBm);
}


double QSignalLevel::dB() const
{
	return GetMount(QuantityUnit::QT_dB);
}


double QSignalLevel::Wat() const
{
	return GetMount(QuantityUnit::QT_Wat);
}


double QSignalLevel::mWat() const
{
	return GetMount(QuantityUnit::QT_mWat);
}


double QSignalLevel::volt() const
{
	return GetMount(QuantityUnit::QT_Volt);
}

double QSignalLevel::GetMount(QuantityUnit return_mode)const
{
	// get the setting unit
	auto v = ValueMap.find(return_mode);
	if (v != ValueMap.end())
		return v->second;

	// check the available unit in map
	auto first_item = ValueMap.begin();
	auto f = ConversionMatrix[(int)first_item->first][(int)return_mode];
	double converted_value = f(first_item->second);

	return converted_value;
}

void QSignalLevel::InitConversionMatrix()
{
	std::function<double(double)> conversion_matrix[(int)QuantityUnit::_NumberOfUnits][(int)QuantityUnit::_NumberOfUnits]
	{
		//QT_dBm,								       QT_dB,						                     QT_Wat,										  QT_mWat,									         QT_Volt
		{[](double v) {return v; },                    [](double v) {return v - 30; },                   [](double v) {return pow(10, (v - 30) / 10.0); },[](double v) {return pow(10, v / 10.0); },         [](double v) {return pow(10, (v - 30.0) / 20.0); }}, //QT_dBm
		{[](double v) {return v + 30; },		       [](double v) {return v; },                        [](double v) {return pow(10, v / 10.0); },		  [](double v) {return pow(10, v / 10.0) * 1000.0; },[](double v) {return pow(10, v / 20.0); }}, //QT_dB
		{[](double v) {return log10(v) * 10.0 + 30; }, [](double v) {return log10(v) * 10.0; },          [](double v) {return v; },						  [](double v) {return v * 1000; },					 [](double v) {return sqrt(v); }}, //QT_Wat
		{[](double v) {return log10(v) * 10.0; },      [](double v) {return log10(v / 1000.0) * 10.0; }, [](double v) {return v / 1000.0; },			  [](double v) {return v; },						 [](double v) {return sqrt(v / 1000.0); }}, //QT_mWat
		{[](double v) {return log10(v) * 20.0 + 30; }, [](double v) {return log10(v) * 20.0; },			 [](double v) {return v * v; },					  [](double v) {return v * v * 1000.0; },			 [](double v) {return v; }}  //QT_Volt
	};

	int end_index = (int)QuantityUnit::_NumberOfUnits - 1;
	std::copy(&conversion_matrix[0][0], &conversion_matrix[end_index][end_index], &ConversionMatrix[0][0]);
}


//-----------------------------------------------------------------------------
//								Times
//-----------------------------------------------------------------------------
///
/// \brief QTimes::QTimes
///
QTimes::QTimes()
{
	ValueMap.insert_or_assign(QuantityUnit::QT_S, 0);
	InitConversionMatrix();
}


QTimes::QTimes(double value, QTimes::QuantityUnit QType)
{
	ValueMap.insert_or_assign(QType, value);
	InitConversionMatrix();
}


void QTimes::S(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_S, value);
}


void QTimes::mS(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_mS, value);
}


void QTimes::uS(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_uS, value);
}


void QTimes::nS(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_nS, value);
}


void QTimes::pS(uint64_t value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_pS, value);
}


double QTimes::S() const
{
	return GetMount(QuantityUnit::QT_S);
}


double QTimes::mS() const
{
	return GetMount(QuantityUnit::QT_mS);
}


double QTimes::uS() const
{
	return GetMount(QuantityUnit::QT_uS);
}


double QTimes::nS() const
{
	return GetMount(QuantityUnit::QT_nS);
}


uint64_t QTimes::pS() const
{
	return uint64_t(GetMount(QuantityUnit::QT_pS));
}


double QTimes::GetMount(QTimes::QuantityUnit return_mode) const
{
	// get the setting unit
	auto v = ValueMap.find(return_mode);
	if (v != ValueMap.end())
		return v->second;

	// check the available unit in map
	auto first_item = ValueMap.begin();
	double converted_value = first_item->second * ConversionMatrix[(int)first_item->first][(int)return_mode];

	return converted_value;
}

void QTimes::InitConversionMatrix()
{
	double conversion_matrix[(int)QuantityUnit::_NumberOfUnits][(int)QuantityUnit::_NumberOfUnits]
	{
		//QT_S,    QT_mS,   QT_uS,    QT_nS,   QT_pS
		{ 1      , 1e3    , 1e6     , 1e9    , 1e12 }, //QT_S
		{ 1e-3   , 1      , 1e3     , 1e6    , 1e9  }, //QT_mS
		{ 1e-6   , 1e-3   , 1       , 1e3    , 1e6  }, //QT_uS
		{ 1e-9   , 1e-6   , 1e-3    , 1      , 1e3  }, //QT_nS
		{ 1e-12  , 1e-9   , 1e-6    , 1e-3   , 1    }  //QT_pS
	};

	int end_index = (int)QuantityUnit::_NumberOfUnits - 1;
	std::copy(&conversion_matrix[0][0], &conversion_matrix[end_index][end_index], &ConversionMatrix[0][0]);
}


//-----------------------------------------------------------------------------
//								Angle Speed
//-----------------------------------------------------------------------------

///
/// \brief QAngleSpeed::QAngleSpeed
///
QAngleSpeed::QAngleSpeed()
{
	ValueMap.insert_or_assign(QuantityUnit::QT_DpS, 0);
	InitConversionMatrix();
}


QAngleSpeed::QAngleSpeed(double value, QAngleSpeed::QuantityUnit QType)
{
	ValueMap.insert_or_assign(QType, value);
	InitConversionMatrix();
}


void QAngleSpeed::DpS(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_DpS, value);
}


void QAngleSpeed::mDpS(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_mDpS, value);
}


void QAngleSpeed::DpH(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_DpH, value);
}


void QAngleSpeed::mDpH(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_mDpH, value);
}

/// <summary>
/// Degree per second
/// </summary>
/// <returns></returns>
double QAngleSpeed::DpS() const
{
	return GetMount(QuantityUnit::QT_DpS);
}

/// <summary>
/// Degree per minut
/// </summary>
/// <returns></returns>
double QAngleSpeed::DpM() const
{
	return GetMount(QuantityUnit::QT_DpM);
}

/// <summary>
/// Mili degree per second
/// </summary>
/// <returns></returns>
double QAngleSpeed::mDpS() const
{
	return GetMount(QuantityUnit::QT_mDpS);
}

/// <summary>
/// Mili degree per minute
/// </summary>
/// <returns></returns>
double QAngleSpeed::mDpM() const
{
	return GetMount(QuantityUnit::QT_mDpM);
}

/// <summary>
/// Degree per hour
/// </summary>
/// <returns></returns>
double QAngleSpeed::DpH() const
{
	return GetMount(QuantityUnit::QT_DpH);
}

/// <summary>
/// Mili degree per hour
/// </summary>
/// <returns></returns>
double QAngleSpeed::mDpH() const
{
	return GetMount(QuantityUnit::QT_mDpH);
}

/// <summary>
/// Round per Minute
/// </summary>
/// <returns></returns>
double QAngleSpeed::RPM()
{
	return GetMount(QuantityUnit::QT_RPM);
}


double QAngleSpeed::GetMount(QAngleSpeed::QuantityUnit return_mode) const
{
	// get the setting unit
	auto v = ValueMap.find(return_mode);
	if (v != ValueMap.end())
		return v->second;

	// check the available unit in map
	auto first_item = ValueMap.begin();
	double converted_value = first_item->second * ConversionMatrix[(int)first_item->first][(int)return_mode];

	return converted_value;
}

void QAngleSpeed::InitConversionMatrix()
{
	double conversion_matrix[(int)QuantityUnit::_NumberOfUnits][(int)QuantityUnit::_NumberOfUnits]
	{
		//QT_DpS,      QT_mDpS,     QT_DpM,    QT_mDpM,   QT_DpH,   QT_mDpH,   QT_RPM
		{ 1          , 1e3        , 60       , 6e4      , 3600    , 3.6e6    , 1/6.0       }, //QT_DpS
		{ 1e-3       , 1          , 0.06     , 60       , 3.6     , 3.6e3    , 1e-3 / 6.0  }, //QT_mDpS
		{ 1.0/60.0   , 100/6.0    , 1        , 1e3      , 60.0    , 60e3     , 1 / 360.0   }, //QT_DpM
		{ 1.0/6e4    , 1.0 / 60   , 1e-3     , 1        , 6e-2    , 1 / 60.0 , 1.0 / 36e4  }, //QT_mDpM
		{ 1 / 3600.0 , 1 / 3.6    , 1 / 60.0 , 100 / 6.0, 1       , 1e3      , 1.0 / 2.16e4}, //QT_DpH
		{ 1.0 / 3.6e6, 1.0 / 3.6e3, 1.0 / 6e4, 1 / 60.0 , 1e-3     , 1       , 1.0 / 2.16e7}, //QT_mDpH
		{ 6          , 6e3        , 360      , 36e4     , 21600   , 21.6e6   , 1           }  //QT_RPM
	};

	int end_index = (int)QuantityUnit::_NumberOfUnits - 1;
	std::copy(&conversion_matrix[0][0], &conversion_matrix[end_index][end_index], &ConversionMatrix[0][0]);
}


//-----------------------------------------------------------------------------
//								Angle
//-----------------------------------------------------------------------------
///
/// \brief QAngle::QAngle
///
QAngle::QAngle()
{
	ValueMap.insert_or_assign(QuantityUnit::QT_Deg, 0);
	InitConversionMatrix();
}


QAngle::QAngle(double value, QAngle::QuantityUnit QType)
{
	ValueMap.insert_or_assign(QType, value);
	InitConversionMatrix();
}


void QAngle::Deg(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_Deg, value);
}


void QAngle::Rad(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_Rad, value);
}


void QAngle::mDeg(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_mDeg, value);
}


double QAngle::Deg() const
{
	return GetMount(QuantityUnit::QT_Deg);
}


double QAngle::Rad() const
{
	return GetMount(QuantityUnit::QT_Rad);
}


double QAngle::mDeg() const
{
	return GetMount(QuantityUnit::QT_mDeg);
}


QAngle QAngle::Wrap360(QAngle angle)
{
	QAngle returnAngle = angle;

	while (returnAngle.Deg() >= 360)
	{
		returnAngle.Deg(returnAngle.Deg() - 360);
	}
	while (returnAngle.Deg() < 0)
	{
		returnAngle.Deg(returnAngle.Deg() + 360);
	}
	return returnAngle;
}


QAngle QAngle::Wrap180(QAngle angle)
{
	QAngle returnAngle = angle;

	while (returnAngle.Deg() >= 180)
	{
		returnAngle.Deg(returnAngle.Deg() - 180);
	}
	while (returnAngle.Deg() < 0)
	{
		returnAngle.Deg(returnAngle.Deg() + 180);
	}
	return returnAngle;
}


QAngle QAngle::Wrap90(QAngle angle)
{
	QAngle returnAngle = angle;

	while (returnAngle.Deg() >= 90)
	{
		returnAngle.Deg(returnAngle.Deg() - 90);
	}
	while (angle.Deg() < 0)
	{
		returnAngle.Deg(returnAngle.Deg() + 90);
	}
	return returnAngle;
}


double QAngle::GetMount(QAngle::QuantityUnit return_mode) const
{
	// get the setting unit
	auto v = ValueMap.find(return_mode);
	if (v != ValueMap.end())
		return v->second;

	// check the available unit in map
	auto first_item = ValueMap.begin();
	double converted_value = first_item->second * ConversionMatrix[(int)first_item->first][(int)return_mode];

	return converted_value;
}


void QAngle::InitConversionMatrix()
{
	double conversion_matrix[(int)QuantityUnit::_NumberOfUnits][(int)QuantityUnit::_NumberOfUnits]
	{
		//QT_Deg, QT_mDeg,  QT_Rad
		{ 1      , 1e3    , 0.01745}, //QT_Deg
		{ 1e-3   , 1      , 17.4533}, //QT_mDeg
		{ 57.2958, 57295.8, 1      }  //QT_Rad
	};

	int end_index = (int)QuantityUnit::_NumberOfUnits - 1;
	std::copy(&conversion_matrix[0][0], &conversion_matrix[end_index][end_index], &ConversionMatrix[0][0]);
}

//-----------------------------------------------------------------------------
//								Ground Speed
//-----------------------------------------------------------------------------
///
/// \brief QGroundSpeed
///
//
QGroundSpeed::QGroundSpeed()
{
	ValueMap.insert_or_assign(QuantityUnit::QT_KMPH, 0);
	InitConversionMatrix();
}


QGroundSpeed::QGroundSpeed(double value, QGroundSpeed::QuantityUnit QType)
{
	ValueMap.insert_or_assign(QType, value);
	InitConversionMatrix();
}


void QGroundSpeed::KMPh(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_KMPH, value);
}


void QGroundSpeed::MPh(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_MPH, value);
}


void QGroundSpeed::KMPs(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_KMPS, value);
}


void QGroundSpeed::MPs(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_MPS, value);
}


double QGroundSpeed::KMPh() const
{
	return GetMount(QuantityUnit::QT_KMPH);
}


double QGroundSpeed::MPh() const
{
	return GetMount(QuantityUnit::QT_MPH);
}


double QGroundSpeed::KMPs() const
{
	return GetMount(QuantityUnit::QT_KMPS);
}


double QGroundSpeed::MPs() const
{
	return GetMount(QuantityUnit::QT_MPS);
}


double QGroundSpeed::toDouble()
{
	return GetMount(_asToDoubleType);
}


void QGroundSpeed::setAsToDoubleType(QGroundSpeed::QuantityUnit type)
{
	_asToDoubleType = type;
}


QGroundSpeed::QuantityUnit QGroundSpeed::getAsToDoubleType(QGroundSpeed::QuantityUnit type)
{
	return _asToDoubleType;
}


double QGroundSpeed::GetMount(QGroundSpeed::QuantityUnit return_mode) const
{
	// get the setting unit
	auto v = ValueMap.find(return_mode);
	if (v != ValueMap.end())
		return v->second;

	// check the available unit in map
	auto first_item = ValueMap.begin();
	double converted_value = first_item->second * ConversionMatrix[(int)first_item->first][(int)return_mode];

	return converted_value;
}

void QGroundSpeed::InitConversionMatrix()
{
	double conversion_matrix[(int)QuantityUnit::_NumberOfUnits][(int)QuantityUnit::_NumberOfUnits]
	{
		//QT_MPS, QT_KMPS, QT_MPH, QT_KMPH
		{ 1     , 1e-3   , 60    , 60e-3  }, //QT_MPS
		{ 1e3   , 1      , 60e3  , 60     }, //QT_KMPS
		{ 0.0166, 1.66e-5, 1     , 1e-3   }, //QT_MPH
		{ 6e4   , 60     , 1e3   , 1      }  //QT_KMPH
	};

	int end_index = (int)QuantityUnit::_NumberOfUnits - 1;
	std::copy(&conversion_matrix[0][0], &conversion_matrix[end_index][end_index], &ConversionMatrix[0][0]);
}


//-----------------------------------------------------------------------------
//								Distance
//-----------------------------------------------------------------------------

///
/// \brief QDistance::_getMount
/// \param returnMode
/// \return
///
QDistance::QDistance()
{
	ValueMap.insert_or_assign(QuantityUnit::QT_M, 0);
	InitConversionMatrix();
}


QDistance::QDistance(double value, QDistance::QuantityUnit QType)
{
	ValueMap.insert_or_assign(QType, value);
	InitConversionMatrix();
}


void QDistance::Mm(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_MM, value);
}


void QDistance::Cm(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_CM, value);
}


void QDistance::M(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_M, value);
}


void QDistance::Km(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_KM, value);
}


void QDistance::Mi(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_Mile, value);
}


void QDistance::Inch(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_INCH, value);
}


void QDistance::Foot(double value)
{
	ValueMap.insert_or_assign(QuantityUnit::QT_Foot, value);
}


double QDistance::Mm() const
{
	return GetMount(QuantityUnit::QT_MM);
}


double QDistance::Cm() const
{
	return GetMount(QuantityUnit::QT_CM);
}


double QDistance::M() const
{
	return GetMount(QuantityUnit::QT_M);
}


double QDistance::Km() const
{
	return GetMount(QuantityUnit::QT_KM);
}


double QDistance::Mi() const
{
	return GetMount(QuantityUnit::QT_Mile);
}


double QDistance::Inch() const
{
	return GetMount(QuantityUnit::QT_INCH);
}


double QDistance::Foot() const
{
	return GetMount(QuantityUnit::QT_Foot);
}


void QDistance::InitConversionMatrix()
{
	double conversion_matrix[(int)QuantityUnit::_NumberOfUnits][(int)QuantityUnit::_NumberOfUnits] =
		//QT_MM,    QT_CM,  QT_M,      QT_KM,     QT_Mile,     QT_INCH, QT_Foot
	{ { 1,        0.01,   1e-3,        1e-6,      6.2137e-7,   0.0393701,0.00328084},    // QT_MM
	  { 10,       1,      0.01,        1e-5,      6.21371e-6,  0.393701 ,0.0328084 },    // QT_CM
	  { 1e3,      1e2,    1,           1e-3,      0.000621371, 39.3701  ,3.28084   },    // QT_M
	  { 1e6,      1e5,    1e3,         1,         0.621371,    39370.1  ,3280.84   },    // QT_KM
	  { 1.609e+6, 160934, 1609.34,     1.60934,   1,           63360    ,5280	   },    // QT_Mile
	  { 25.4,     2.54,   0.0254,      2.54e-5,   1.5783e-5,   1        ,0.0833333 },    // QT_Inch
	  { 304.8,    30.48,  0.0003048,   0.0003048, 0.000189394, 12       ,1		   }     // QT_Foot
	};
	int end_index = (int)QuantityUnit::_NumberOfUnits - 1;
	std::copy(&conversion_matrix[0][0], &conversion_matrix[end_index][end_index], &ConversionMatrix[0][0]);
}

double QDistance::GetMount(QDistance::QuantityUnit return_mode) const
{
	// get the setting unit
	auto v = ValueMap.find(return_mode);
	if (v != ValueMap.end())
		return v->second;

	// check the available unit in map
	auto first_item = ValueMap.begin();
	double converted_value = first_item->second * ConversionMatrix[(int)first_item->first][(int)return_mode];

	return converted_value;
}


template<class T>
inline QRange<T>::QRange(T lower, T upper)
{
	if (lower > upper)
	{
		lower_ = upper;
		upper_ = lower;
	}
	else
	{
		lower_ = lower;
		upper_ = upper;
	}
}

template<class T>
inline void QRange<T>::setLower(T lower)
{
	lower_ = lower;
}

template<class T>
inline void QRange<T>::setUpper(T upper)
{
	upper_ = upper;
}

template<class T>
inline T QRange<T>::lower() const
{
	return lower_;
}

template<class T>
inline T QRange<T>::upper() const
{
	return upper_;
}

template<class T>
inline T QRange<T>::center() const
{
	return (upper() + lower()) / 2.0;
}

template<class T>
inline T QRange<T>::size() const
{
	return(upper() - lower());
}

template<class T>
inline void QRange<T>::expand(T includeCoord)
{
	if (lower_ > includeCoord)
	{
		lower_ = includeCoord;
	}
	if (upper_ < includeCoord)
	{
		upper_ = includeCoord;
	}
}

template<class T>
inline void QRange<T>::expand(const QRange<T>& otherRange)
{
	if (lower_ > otherRange.lower())
	{
		lower_ = otherRange.lower();
	}
	if (upper_ < otherRange.upper())
	{
		upper_ = otherRange.upper();
	}
}
