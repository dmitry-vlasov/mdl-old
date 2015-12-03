/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_config_option_Option.hpp                            */
/* Description:     class for config options                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONFIG_OPTION_OPTION_HPP_
#define NSTD_CONFIG_OPTION_OPTION_HPP_

namespace nstd {
namespace config {
namespace option {

template<class T>
class Option : public memory :: storage :: Scalar<Option<T>, memory :: allocator :: Standard> {
public :

	enum {
		DEFAULT_SMALL_INDENT = 7, // characters for 1 char cmd parameter
		DEFAULT_LARGE_INDENT = 36 // characters for multychar cmd parameter
	};

	typedef T Type_;
	typedef
		nstd :: String<>
		String_;

	Option();
	Option
	(
		const Type_ defaultValue,
		const char* cmdString,
		const char* usageMessage,
		const char  cmdChar = chars :: NULL_CHAR,
		const int   indent = DEFAULT_LARGE_INDENT
	);
	~ Option();

	Type_& value();
	String_& name();
	const Type_& getValue() const;

	bool isScaned() const;
	bool isCorrect() const;
	bool isDefault() const;

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
	friend class Time;
	friend class Size;

	template<class S>
	void showMainUsageMessage (S&) const;
	template<class S>
	void showMainOptionValues (S&) const;
	template<class S>
	void showDefaultUsageMessage (S&) const;
	template<class S>
	void showDefaultOptionValues (S&) const;


	Type_   value_;
	String_ name_;
	String_ option_;

	enum {
		INITIAL_NAME_CAPACITY   = 32,
		INITIAL_OPTION_CAPACITY = 32,
		INITIAL_STRING_CAPACITY = 32,

		LONG_OPTION_SIZE = 32
	};

	const Type_ defaultValue_;
	const char* cmdString_;
	const char* usageMessage_;
	const char  cmdChar_;
	const int   largeIndent_;
	const bool  isNameless_;

	const char* sscanfParam_;
	const char* typeName_;
	bool isScaned_;
	bool isCorrect_;
};

}
}
}

#endif /*NSTD_CONFIG_OPTION_OPTION_HPP_*/
