/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_Misc.hpp                            */
/* Description:     static class for mdl misc parameters                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_CONFIG_MISC_HPP_
#define MDL_AUXILIARY_CONFIG_MISC_HPP_

#include "mdl/types/mdl_types.hpp"
#include "mdl/auxiliary/config/mdl_auxiliary_config.dpp"

namespace mdl {
namespace auxiliary {
namespace config {

class Misc {
public :
	enum MiscOption_ {
		REMOVE_COMMENTS   = 0,
		HIDE_COMMENTS     = 1,
		CHECK_UNAMBIGUITY = 2,
		NO_LABELS         = 3,
		DEEP_WRITE        = 4,
		INSERT_POSTFIX    = 5,
		EXPR_MULTYLINE    = 6,
		EXPR_WITH_TYPES   = 7,
		SHOW_DISJOINTEDS  = 8,
		MISC_OPTIONS_NUM  = 9
	};

	static option :: Bool& miscOption (MiscOption_);

	// Comments are removed at translation.
	static bool removeComments();
	// Comments are not shown at replication.
	static bool hideComments();
	// check unambiguity of expressions in grammar
	static bool checkUnambiguity();
	// remove labels in smm output
	static bool noLabels();
	// write all included source files
	static bool deepWrite();
	// insert a postfix to the target file name
	static bool insertPostfix();
	// show/write expressions in a multyline mode
	static bool expressionsMultyline();
	// show/write types of terms.
	static bool expressionsWithTypes(); //< NOTE: DEBUG ONLY mode!!
	static bool showDisjointeds(); //< NOTE: DEBUG ONLY mode!!

	enum MultylineFormat_ {
		MULTYLINE_MIN_WIDTH  = 0,
		MULTYLINE_MAX_WIDTH  = 1,
		MULTYLINE_TAB_WIDTH  = 2,
		MULTYLINE_FORMAT_NUM = 3
	};

	static value :: Integer multylineMinWidth();
	static value :: Integer multylineMaxWidth();
	static value :: Integer multylineTabWidth();

	template<class S>
	static void showUsageMessage (S& os, const List& groupList = List());
	template<class S>
	static void showOptionValues (S& os , const List& groupList = List());
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
	enum {
		DEFAULT_MULTYLINE_MIN_WIDTH = 12,
		DEFAULT_MULTYLINE_MAX_WIDTH = 24,
		DEFAULT_MULTYLINE_TAB_WIDTH = 4
	};

	static option :: Bool*    miscOptions_ [MISC_OPTIONS_NUM];
	static option :: Integer* multylineOptions_ [MULTYLINE_FORMAT_NUM];
	static const char* optionGroupName_;
};

}
}
}

#endif /*MDL_AUXILIARY_CONFIG_MISC_HPP_*/
