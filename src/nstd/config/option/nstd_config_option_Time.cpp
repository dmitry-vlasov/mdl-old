/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_config_option_Time.cpp                              */
/* Description:     config option for time                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONFIG_OPTION_TIME_CPP_
#define NSTD_CONFIG_OPTION_TIME_CPP_

namespace nstd {
namespace config {
namespace option {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Time :: Time
	(
		const nstd :: Time defaultTime,
		const char* cmdString,
		const char* usageMessage,
		const char  cmdChar,
		const int   largeIndent
	) :
	stringOption_ ("", cmdString, usageMessage, cmdChar,largeIndent),
	time_ (defaultTime),
	isCorrect_ (true) {
	}
	inline
	Time :: ~ Time() {
	}

	inline nstd :: Time
	Time :: getTime() const {
		return time_;
	}
	inline void
	Time :: setTime (const nstd :: Time time) {
		time_ = time;
	}

	inline bool
	Time :: isScaned() const {
		return stringOption_.isScaned();
	}
	bool
	Time :: isCorrect() const {
		return isCorrect_;
	}

	inline const char*
	Time :: getName() const {
		return stringOption_.getName();
	}
	inline const char*
	Time :: getString() const {
		return stringOption_.getString();
	}
	inline const char*
	Time :: getUsageMessage() const {
		return stringOption_.getUsageMessage();
	}

	bool
	Time :: proceedStringOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		if (stringOption_.proceedStringOption (opt, argCount, argValues, i)) {
			parseString();
			return true;
		} else {
			return false;
		}
	}
	bool
	Time :: proceedOneCharOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		if (stringOption_.proceedOneCharOption (opt, argCount, argValues, i)) {
			parseString();
			return true;
		} else {
			return false;
		}
	}

	template<class S>
	inline void
	Time :: showUsageMessage (S& os) const {
		stringOption_.showUsageMessage(os);
	}
	template<class S>
	inline void
	Time :: showOptionValues (S& os) const {
		stringOption_.showOptionValues(os);
	}

	void
	Time :: commitSuicide() {
		delete this;
	}
	inline Size_t
	Time :: getVolume() const
	{
		Size_t volume = 0;
		volume += stringOption_.getVolume();
		return volume;
	}
	inline Size_t
	Time :: getSizeOf() const {
		return sizeof (Time);
	}
	template<class S>
	inline void
	Time :: show (S& string) const {
		stringOption_.show<S> (string);
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Time :: parseString()
	{
		//std :: cout << "stringOption_.value() = " << stringOption_.value() << std :: endl;
		const int length = strlen (stringOption_.value().c_str());
		char string [length + 1];
		for (int i = 0; i < length; ++ i) {
			string [i] = stringOption_.value() [i];
		}
		string [length] = chars :: NULL_CHAR;

		//std :: cout << "string = " << string << std :: endl;
		enum {
			MAX_LENTGH = 4
		};
		int numbers [MAX_LENTGH];
		char chars  [MAX_LENTGH];
		parse (string, numbers, chars, MAX_LENTGH);
		time_ = initTime (numbers, chars, MAX_LENTGH);
	}
	void
	Time :: parse
	(
		char* string,
		int* numbers,
		char* chars,
		const int size
	)
	{
		// format of time string:
		// 1d_5h__45m_10s, 2h30m

		int c = 0;
		char* beg = string;
		char* end = string;
		bool inNumber = true;
		bool inChar = false;

		while (*end != '\0') {
			const char ch = *end;
			if ('0' <= ch && ch <= '9') {
				if (!inNumber) {
					beg = end;
				}
				inNumber = true;
				inChar = false;
			} else if ((ch == 'd') || (ch == 'h') ||
						(ch == 'm') || (ch == 's')) {
				*end = chars :: NULL_CHAR;
				sscanf (beg, "%d", numbers + c);
				beg = end;
				chars [c] = ch;
				++ c;
				inNumber = false;
				inChar = true;
				if (c == size) {
					break;
				}
			} else if (ch == '_') {
				inNumber = false;
				inChar = false;
			} else {
				showParseError (std :: cout);
				isCorrect_ = false;
			}
			++ end;
		}
		if ((c == 0) || inNumber) {
			showParseError (std :: cout);
			isCorrect_ = false;
		}
	}
	nstd :: Time
	Time :: initTime (const int* numbers, const char* chars, const int size)
	{
		nstd :: Time time = 0;
		for (int i = 0; i < size; ++ i) {
			const int n = numbers [i];
			const char ch = chars [i];
			switch (ch) {
			case 'd' : time += n * time :: DAY;    break;
			case 'h' : time += n * time :: HOUR;   break;
			case 'm' : time += n * time :: MINUTE; break;
			case 's' : time += n * time :: SECOND; break;
			default  : break;
			}
		}
		return time;
	}
	void
	Time :: writeString()
	{
		stringOption_.value().clear();
		nstd :: Time time = time_;
		const int days = floor (time / time :: DAY);
		time -= days * time :: DAY;
		const int hours = floor (time / time :: HOUR);
		time -= hours * time :: HOUR;
		const int minutes = floor (time / time :: MINUTE);
		time -= minutes * time :: MINUTE;
		const int seconds = floor (time / time :: SECOND);

		if (days > 0) {
			stringOption_.value() << days << "d";
			if ((hours > 0) || (minutes > 0) || (seconds > 0)) {
				stringOption_.value() << "_";
			}
		}
		if (hours > 0) {
			stringOption_.value() << hours << "h";
			if ((minutes > 0) || (seconds > 0)) {
				stringOption_.value() << "_";
			}
		}
		if (minutes > 0) {
			stringOption_.value() << minutes << "m";
			if (seconds > 0) {
				stringOption_.value() << "_";
			}
		}
		if (seconds > 0) {
			stringOption_.value() << seconds << "s";
		}
	}
	void
	Time :: showParseError (std :: ostream& os, const char* message) const
	{
		//os << message << std :: endl;
		os << "incorrect time format: " << stringOption_.getValue() << std :: endl;
		os << "time should look like:" << std :: endl;
		os << "\t1d_5h_45m_10s" << std :: endl;
		os << "\t2h30m" << std :: endl;
		os << "\t2h__30m" << std :: endl;
	}
}
}
}

#endif /*NSTD_CONFIG_OPTION_TIME_CPP_*/
