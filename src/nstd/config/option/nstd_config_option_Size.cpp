/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_config_option_Size.cpp                              */
/* Description:     config option for size                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {
namespace config {
namespace option {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Size :: Size
	(
		const nstd :: Size_t defaultSize,
		const char* cmdString,
		const char* usageMessage,
		const char  cmdChar,
		const int   largeIndent
	) :
	stringOption_ ("", cmdString, usageMessage, cmdChar,largeIndent),
	size_ (defaultSize),
	isCorrect_ (true) {
	}
	inline
	Size :: ~ Size() {
	}

	inline nstd :: Size_t
	Size :: getSize() const {
		return size_;
	}
	inline void
	Size :: setSize (const nstd :: Size_t size) {
		size_ = size;
	}

	inline bool
	Size :: isScaned() const {
		return stringOption_.isScaned();
	}
	bool
	Size :: isCorrect() const {
		return isCorrect_;
	}

	inline const char*
	Size :: getName() const {
		return stringOption_.getName();
	}
	inline const char*
	Size :: getString() const {
		return stringOption_.getString();
	}
	inline const char*
	Size :: getUsageMessage() const {
		return stringOption_.getUsageMessage();
	}

	bool
	Size :: proceedStringOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		if (stringOption_.proceedStringOption (opt, argCount, argValues, i)) {
			parseString();
			return true;
		} else {
			return false;
		}
	}
	bool
	Size :: proceedOneCharOption (const char* opt, const int argCount, const char* argValues[], int& i)
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
	Size :: showUsageMessage (S& os) const {
		stringOption_.showUsageMessage(os);
	}
	template<class S>
	inline void
	Size :: showOptionValues (S& os) const {
		stringOption_.showOptionValues(os);
	}

	void
	Size :: commitSuicide() {
		delete this;
	}
	inline Size_t
	Size :: getVolume() const
	{
		Size_t volume = 0;
		volume += stringOption_.getVolume();
		return volume;
	}
	inline Size_t
	Size :: getSizeOf() const {
		return sizeof (Size);
	}
	template<class S>
	inline void
	Size :: show (S& string) const {
		stringOption_.show<S> (string);
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Size :: parseString()
	{
		const int length = strlen (stringOption_.value().c_str());
		char string [length + 1];
		for (int i = 0; i < length; ++ i) {
			string [i] = stringOption_.value() [i];
		}
		string [length] = chars :: NULL_CHAR;
		enum {
			MAX_LENTGH = 4
		};
		int numbers [MAX_LENTGH];
		char chars  [MAX_LENTGH];
		parse (string, numbers, chars, MAX_LENTGH);
		size_ = initSize (numbers, chars, MAX_LENTGH);
	}
	void
	Size :: parse
	(
		char* string,
		int* numbers,
		char* chars,
		const int length
	)
	{
		// format of size string:
		// 1g_5m__45k_10b

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
			} else if ((ch == 'g') || (ch == 'm') ||
						(ch == 'k') || (ch == 'b')) {
				*end = chars :: NULL_CHAR;
				sscanf (beg, "%d", numbers + c);
				beg = end;
				chars [c] = ch;
				++ c;
				inNumber = false;
				if (c == length) {
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
	nstd :: Size_t
	Size :: initSize (const int* numbers, const char* chars, const int length)
	{
		nstd :: Size_t size = 0;
		for (int i = 0; i < length; ++ i) {
			const int n = numbers [i];
			const char ch = chars [i];
			switch (ch) {
			case 'b' : size += n * size :: BYTE;     break;
			case 'k' : size += n * size :: KILOBYTE; break;
			case 'm' : size += n * size :: MEGABYTE; break;
			case 'g' : size += n * size :: GIGABYTE; break;
			default  : break;
			}
		}
		return size;
	}
	void
	Size :: writeString()
	{
		stringOption_.value().clear();
		nstd :: Size_t size = size_;
		const int gigabytes = floor (size / size :: GIGABYTE);
		size -= gigabytes * size :: GIGABYTE;
		const int megabytes = floor (size / size :: MEGABYTE);
		size -= megabytes * size :: MEGABYTE;
		const int kilobytes = floor (size / size :: KILOBYTE);
		size -= kilobytes * size :: KILOBYTE;
		const int bytes = floor (size / size :: BYTE);

		if (gigabytes > 0) {
			stringOption_.value() << gigabytes << "g";
			if ((megabytes > 0) || (kilobytes > 0) || (bytes > 0)) {
				stringOption_.value() << "_";
			}
		}
		if (megabytes > 0) {
			stringOption_.value() << megabytes << "m";
			if ((kilobytes > 0) || (bytes > 0)) {
				stringOption_.value() << "_";
			}
		}
		if (kilobytes > 0) {
			stringOption_.value() << kilobytes << "k";
			if (bytes > 0) {
				stringOption_.value() << "_";
			}
		}
		if (bytes > 0) {
			stringOption_.value() << bytes << "b";
		}
	}
	void
	Size :: showParseError (std :: ostream& os) const
	{
		os << "incorrect size format: " << stringOption_.getValue() << std :: endl;
		os << "size should look like:" << std :: endl;
		os << "\t2g_250m_400k_380b" << std :: endl;
		os << "\t1g500m" << std :: endl;
		os << "\t1g__300m" << std :: endl;
	}
}
}
}


