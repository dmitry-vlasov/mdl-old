/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_Location.hpp                        */
/* Description:     location in mdl source tree                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_CONFIG_LOCATION_HPP_
#define MDL_AUXILIARY_CONFIG_LOCATION_HPP_

#include "mdl/types/mdl_types.hpp"
#include "mdl/auxiliary/config/mdl_auxiliary_config.dpp"

namespace mdl {
namespace auxiliary {
namespace config {

class Location {
public :
	typedef nstd :: Path<> Path_;

	static const lexer :: Position& getPosition();
	static bool locationIsSet();
	static value :: Integer line();
	static value :: Integer column();
	static const Path_&     file();

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
	static bool isConsistent();

	static void init();
	static void release();
	static Size_t getVolume();
	static bool initTimes();

private :
	static option :: Integer* line_;
	static option :: Integer* column_;
	static option :: Path*    file_;

	static const char* optionGroupName_;
};

}
}
}

#endif /*MDL_AUXILIARY_CONFIG_LOCATION_HPP_*/
