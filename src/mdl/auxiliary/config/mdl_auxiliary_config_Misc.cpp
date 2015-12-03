/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_Misc.cpp                            */
/* Description:     static class for mdl misc parameters                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_CONFIG_MISC_CPP_
#define MDL_AUXILIARY_CONFIG_MISC_CPP_

namespace mdl {
namespace auxiliary {
namespace config {

	/****************************
	 *		Public members
	 ****************************/

	inline option :: Bool&
	Misc :: miscOption (MiscOption_ option) {
		return *miscOptions_ [option];
	}

	inline bool
	Misc :: removeComments() {
		return miscOptions_ [REMOVE_COMMENTS]->getValue();
	}
	inline bool
	Misc :: hideComments() {
		return miscOptions_ [HIDE_COMMENTS]->getValue();
	}
	inline bool
	Misc :: checkUnambiguity() {
		return miscOptions_ [CHECK_UNAMBIGUITY]->getValue();
	}
	inline bool
	Misc :: noLabels() {
		return miscOptions_ [NO_LABELS]->getValue();
	}
	inline bool
	Misc :: deepWrite() {
		return miscOptions_ [DEEP_WRITE]->getValue();
	}
	inline bool
	Misc :: insertPostfix() {
		return miscOptions_ [INSERT_POSTFIX]->getValue();
	}
	inline bool
	Misc :: expressionsMultyline() {
		return miscOptions_ [EXPR_MULTYLINE]->getValue();
	}
	inline bool
	Misc :: expressionsWithTypes() {
		return miscOptions_ [EXPR_WITH_TYPES]->getValue();
	}
	inline bool
	Misc :: showDisjointeds() {
		return miscOptions_ [SHOW_DISJOINTEDS]->getValue();
	}

	inline value :: Integer
	Misc :: multylineMinWidth() {
		return multylineOptions_ [MULTYLINE_MIN_WIDTH]->getValue();
	}
	inline value :: Integer
	Misc :: multylineMaxWidth() {
		return multylineOptions_ [MULTYLINE_MAX_WIDTH]->getValue();
	}
	inline value :: Integer
	Misc :: multylineTabWidth() {
		return multylineOptions_ [MULTYLINE_TAB_WIDTH]->getValue();
	}

	template<class S>
	void
	Misc :: showUsageMessage (S& os, const List& groupList)
	{
		if (groupList.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int i = 0; i < MISC_OPTIONS_NUM; ++ i) {
				miscOptions_ [i]->showUsageMessage (os);
			}
			for (int i = 0; i < MULTYLINE_FORMAT_NUM; ++ i) {
				multylineOptions_ [i]->showUsageMessage (os);
			}
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	void
	Misc :: showOptionValues (S& os, const List& groupList)
	{
		if (groupList.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int i = 0; i < MISC_OPTIONS_NUM; ++ i) {
				miscOptions_ [i]->showOptionValues (os);
			}
			for (int i = 0; i < MULTYLINE_FORMAT_NUM; ++ i) {
				multylineOptions_ [i]->showOptionValues (os);
			}
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	inline void
	Misc :: showGroupName (S& os) {
		os << "\t" << optionGroupName_ << chars :: NEW_LINE;
	}

	/****************************
	 *		Protected members
	 ****************************/

	bool
	Misc :: proceedStringOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		for (int j = 0; j < MISC_OPTIONS_NUM; ++ j) {
			if (miscOptions_[j]->proceedStringOption (opt, argCount, argValues, i)) {
				return true;
			}
		}
		for (int j = 0; j < MULTYLINE_FORMAT_NUM; ++ j) {
			if (multylineOptions_[j]->proceedStringOption (opt, argCount, argValues, i)) {
				return true;
			}
		}
		return false;
	}
	bool
	Misc :: proceedOneCharOption (const char* opt, const int argCount, const char* argValues[], int& i) {
		return false;
	}

	bool
	Misc :: isCorrect()
	{
		for (int i = 0; i < MISC_OPTIONS_NUM; ++ i) {
			if (!miscOptions_ [i]->isCorrect()) {
				return false;
			}
		}
		for (int i = 0; i < MULTYLINE_FORMAT_NUM; ++ i) {
			if (!multylineOptions_ [i]->isCorrect()) {
				return false;
			}
		}
		return true;
	}

	inline void
	Misc :: init ()
	{
		miscOptions_ [REMOVE_COMMENTS]   = new option :: Bool (false, "remove-comments",   "remove comments at translation.");
		miscOptions_ [HIDE_COMMENTS]     = new option :: Bool (false, "hide-comments",     "do not show comments.");
		miscOptions_ [CHECK_UNAMBIGUITY] = new option :: Bool (false, "check-unambiguity", "check unambiguity of expressions in grammar (time consuming option).");
		miscOptions_ [NO_LABELS]         = new option :: Bool (false, "no-labels",         "use indexes as labels for assertions in output.");
		miscOptions_ [DEEP_WRITE]        = new option :: Bool (false, "deep-write",        "write all included source files.");
		miscOptions_ [INSERT_POSTFIX]    = new option :: Bool (false, "insert-postfix",    "instert postfix to the name of the translated file.");
		miscOptions_ [EXPR_MULTYLINE]    = new option :: Bool (false, "expr-multyline",    "show/write expressions in a multiline mode.");
		miscOptions_ [EXPR_WITH_TYPES]   = new option :: Bool (false, "expr-with-types",   "show/write types of all terms in expressions. DEBUG ONLY mode (!!)");
		miscOptions_ [SHOW_DISJOINTEDS]  = new option :: Bool (false, "show-disjointeds",  "explicitly show disjointed variable restrictions in theorems. DEBUG ONLY mode (!!)");

		multylineOptions_ [MULTYLINE_MIN_WIDTH] = new option :: Integer (DEFAULT_MULTYLINE_MIN_WIDTH, "multyline-min-width", "the length of an expression, at which the expression may be multilined.");
		multylineOptions_ [MULTYLINE_MAX_WIDTH] = new option :: Integer (DEFAULT_MULTYLINE_MAX_WIDTH, "multyline-max-width", "the length of an expression, at which the expression will be definitely multilined.");
		multylineOptions_ [MULTYLINE_TAB_WIDTH] = new option :: Integer (DEFAULT_MULTYLINE_TAB_WIDTH, "multyline-tab-width", "the length of 'tab', used for formatting calculations");
	}
	inline void
	Misc :: release()
	{
		for (int i = 0; i < MISC_OPTIONS_NUM; ++ i) {
			delete miscOptions_ [i];
			miscOptions_ [i] = NULL;
		}
		for (int i = 0; i < MULTYLINE_FORMAT_NUM; ++ i) {
			delete multylineOptions_ [i];
			multylineOptions_ [i] = NULL;
		}
	}
	inline Size_t
	Misc :: getVolume()
	{
		Size_t volume = 0;
		for (int i = 0; i < MISC_OPTIONS_NUM; ++ i) {
			volume += object :: Object :: getAggregateVolume (miscOptions_ [i]);
		}
		for (int i = 0; i < MULTYLINE_FORMAT_NUM; ++ i) {
			volume += object :: Object :: getAggregateVolume (multylineOptions_ [i]);
		}
		return volume;
	}

	/*************************************
	 *		Private static attributes
	 *************************************/

	option :: Bool*    Misc :: miscOptions_      [MISC_OPTIONS_NUM];
	option :: Integer* Misc :: multylineOptions_ [MULTYLINE_FORMAT_NUM];
	const char* Misc :: optionGroupName_ = "misc";
}
}
}

#endif /*MDL_AUXILIARY_CONFIG_MISC_CPP_*/
