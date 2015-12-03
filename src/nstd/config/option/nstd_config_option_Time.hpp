/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_config_option_Time.hpp                              */
/* Description:     config option for time                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONFIG_OPTION_TIME_HPP_
#define NSTD_CONFIG_OPTION_TIME_HPP_

namespace nstd {
namespace config {
namespace option {

class Time : public memory :: storage :: Scalar<Time, memory :: allocator :: Standard> {
public :
	Time();
	Time
	(
		const nstd :: Time defaultTime,
		const char* cmdString,
		const char* usageMessage,
		const char  cmdChar = chars :: NULL_CHAR,
		const int   indent = String :: DEFAULT_LARGE_INDENT
	);
	~ Time();

	nstd :: Time getTime() const;
	void setTime (const nstd :: Time);

	bool isScaned() const;
	bool isCorrect() const;

	const char* getName() const;
	const char* getString() const;
	const char* getUsageMessage() const;

	bool proceedStringOption (const char*, const int, const char* [], int&);
	bool proceedOneCharOption (const char*, const int, const char* [], int&);

	template<class S>
	void showUsageMessage (S&) const;
	template<class S>
	void showOptionValues (S&) const;

	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	template<class S>
	void show (S&) const;

private :
	void parseString();
	void parse (char* string, int* numbers, char* chars, const int size);
	nstd :: Time initTime (const int* numbers, const char* chars, const int size);
	void writeString();
	void showParseError (std :: ostream&, const char* message = "") const;

	String stringOption_;
	nstd :: Time time_;
	bool isCorrect_;
};

}
}
}

#endif /*NSTD_CONFIG_OPTION_TIME_HPP_*/
