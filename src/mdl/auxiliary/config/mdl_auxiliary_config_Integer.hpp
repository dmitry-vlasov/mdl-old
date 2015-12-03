/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_Integer.hpp                         */
/* Description:     static class for integer mdl prover factors              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_CONFIG_INTEGER_HPP_
#define MDL_AUXILIARY_CONFIG_INTEGER_HPP_

#include "mdl/types/mdl_types.hpp"
#include "mdl/auxiliary/config/mdl_auxiliary_config.dpp"

namespace mdl {
namespace auxiliary {
namespace config {

class Integer {
public :
	enum IntegerOption_ {
		PRECISION    = 0,
		GROUPING     = 1,
		THRESHOLD    = 2,
		SAMPLE_SIZE  = 3,
		INDEX        = 4,
		INTEGER_OPTIONS_NUM = 5
	};

	static option :: Integer& getIntegerOption (const IntegerOption_);
	static value :: Integer getInteger (const IntegerOption_);

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
	static option :: Integer* integerOptions_ [INTEGER_OPTIONS_NUM];
	static const char* optionGroupName_;
};

}
}
}

#endif /*MDL_AUXILIARY_CONFIG_INTEGER_HPP_*/
