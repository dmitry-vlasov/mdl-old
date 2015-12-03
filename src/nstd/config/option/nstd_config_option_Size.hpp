/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_config_option_Size.hpp                              */
/* Description:     config option for size (bytes)                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONFIG_OPTION_SIZE_HPP_
#define NSTD_CONFIG_OPTION_SIZE_HPP_

namespace nstd {
namespace config {
namespace option {

class Size : public memory :: storage :: Scalar<Size, memory :: allocator :: Standard> {
public :
	typedef String :: String_ String_;

	Size();
	Size
	(
		const nstd :: Size_t defaultSize,
		const char* cmdString,
		const char* usageMessage,
		const char  cmdChar = chars :: NULL_CHAR,
		const int   indent = String :: DEFAULT_LARGE_INDENT
	);
	~ Size();

	nstd :: Size_t getSize() const;
	void setSize (const nstd :: Size_t);

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
	void parse (char* string, int* numbers, char* chars, const int length);
	nstd :: Size_t initSize (const int* numbers, const char* chars, const int length);
	void writeString();
	void showParseError (std :: ostream&) const;

	String stringOption_;
	nstd :: Size_t size_;
	bool isCorrect_;
};

}
}
}

#endif /*NSTD_CONFIG_OPTION_SIZE_HPP_*/
