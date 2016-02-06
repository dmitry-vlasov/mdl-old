/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_misc_Timer.hpp                                      */
/* Description:     simple timer                                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {
namespace misc {

class Timer {
public :
	enum Mode {
		START,
		STOP
	};
	typedef
		:: timeval
		TimeVal_;

	Timer (const bool brief = false, const Mode = STOP);
	Timer (const Timer&);
	virtual ~ Timer();

	void start();
	void stop();
	void mark();
	void clear();

	double getMicroseconds() const;
	double getMilliseconds() const;
	double getSeconds() const;
	double getMinutes() const;
	double getHours() const;
	double getCumulativeSeconds() const;
	double getCumulativeMinutes() const;
	double getCumulativeHours() const;

	bool isUsed() const;
	bool isOn() const;
	bool isOff() const;

	void setShowCumulativeTime (const bool = true) const;
	bool getShowCumulativeTime() const;

	void operator = (const Timer&);
	void operator += (const Timer&);
	void operator /= (const double);
	template<class S>
	void show (S&) const;

	TimeVal_ getDelta() const;
	TimeVal_ getCumulative() const;

	void setDelta (TimeVal_);
	void setCumulative (TimeVal_);

	// nstd :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;

private :
	static void addTime (TimeVal_&, const TimeVal_);

	enum {
		MICROSECONDS_IN_SECOND      = 1000000,
		MICROSECONDS_IN_MILLISECOND = 1000,
		MILLISECONDS_IN_SECOND      = 1000
	};

	template<class S>
	void show (S&, const TimeVal_&) const;

	bool isOn_;
	bool isUsed_;
	bool brief_;

	TimeVal_ startTime_;
	TimeVal_ midTime_;
	TimeVal_ stopTime_;

	TimeVal_ deltaTime_;
	TimeVal_ cumulativeTime_;

	mutable bool showCumulativeTime_;
};

	std :: ostream&
	operator << (std :: ostream&, const Timer&);

	template<class A>
	String<A>&
	operator << (String<A>&, const Timer&);
}
}


