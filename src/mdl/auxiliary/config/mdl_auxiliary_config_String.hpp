/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_String.hpp                          */
/* Description:     static class for string prover options                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace auxiliary {
namespace config {

class String {
public :
	typedef nstd :: String<> String_;

	static option :: String* stringOption (const char*);
	static bool hasStringOption (const char*);
	static const String_* getString (const char*);

	template<class S>
	static void showUsageMessage (S&, const List& groupList = List());
	template<class S>
	static void showOptionValues (S&, const List& groupList = List());
	template<class S>
	static void showGroupName (S&);

protected :
	static bool proceedStringOption (const char*, const int, const char* [], int&);
	static bool proceedOneCharOption (const char*, const int, const char* [], int&);

	static bool isCorrect();

	static void init();
	static void release();
	static Size_t getVolume();

private :
	typedef
		vector :: Vector
		<
			option :: String,
			storage :: ByPointer,
			allocator :: Standard
		>
		OptionVector_;

	enum {
		INITIAL_OPTION_VECTOR_CAPACITY = 32
	};

	static OptionVector_* optionVector_;
	static const char* optionGroupName_;
};

}
}
}


