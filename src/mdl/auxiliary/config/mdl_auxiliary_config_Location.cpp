/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_Location.cpp                        */
/* Description:     location in mdl source tree                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_CONFIG_LOCATION_CPP_
#define MDL_AUXILIARY_CONFIG_LOCATION_CPP_

namespace mdl {
namespace auxiliary {
namespace config {

	/****************************
	 *		Public members
	 ****************************/

	inline const lexer :: Position&
	Location :: getPosition() {
		static lexer :: Position position;
		position.setup (line_->getValue(), column_->getValue());
		return position;
	}
	inline bool
	Location :: locationIsSet() {
		return line_->isScaned() && column_->isScaned();
	}
	inline value :: Integer
	Location :: line() {
		return line_->getValue();
	}
	inline value :: Integer
	Location :: column() {
		return column_->getValue();
	}
	inline const Location :: Path_&
	Location :: file() {
		return file_->getValue();
	}

	template<class S>
	void
	Location :: showUsageMessage (S& os, const List& groupList)
	{
		if (groupList.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			line_->showUsageMessage (os);
			column_->showUsageMessage (os);
			file_->showUsageMessage (os);
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	void
	Location :: showOptionValues (S& os, const List& groupList)
	{
		if (groupList.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			line_->showOptionValues (os);
			column_->showOptionValues (os);
			file_->showOptionValues (os);
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	inline void
	Location :: showGroupName (S& os) {
		os << "\t" << optionGroupName_ << chars :: NEW_LINE;
	}

	/****************************
	 *		Protected members
	 ****************************/

	bool
	Location :: proceedStringOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		if (line_->proceedStringOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (column_->proceedStringOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (file_->proceedStringOption (opt, argCount, argValues, i)) {
			return true;
		}
		return false;
	}
	bool
	Location :: proceedOneCharOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		if (line_->proceedOneCharOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (column_->proceedOneCharOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (file_->proceedOneCharOption (opt, argCount, argValues, i)) {
			return true;
		}
		return false;
	}

	bool
	Location :: isCorrect()
	{
		if (!line_->isCorrect()) {
			return false;
		}
		if (!column_->isCorrect()) {
			return false;
		}
		if (!file_->isCorrect()) {
			return false;
		}
		/*if (line_->isScaned() && column_->isScaned()) {
			Lexer :: lookup() = lexer :: Position(line_->getValue(), column_->getValue());
		}*/
		return true;
	}

	inline bool
	Location :: isConsistent() {
		return true;
	}

	inline void
	Location :: init ()
	{
		line_   = new option :: Integer (value :: undefined :: INTEGER, "line",   "the line of an object is being looked up.");
		column_ = new option :: Integer (value :: undefined :: INTEGER, "column", "the column of an object is being looked up.");
		file_   = new option :: Path ("file", "the file, where an object is being looked up.");
	}
	inline void
	Location :: release()
	{
		if (line_ != NULL)   { delete line_;   line_ = NULL;   }
		if (column_ != NULL) { delete column_; column_ = NULL; }
		if (file_ != NULL)   { delete file_;   file_ = NULL;   }
	}
	inline Size_t
	Location :: getVolume()
	{
		Size_t volume = 0;
		volume += object :: Object :: getAggregateVolume (line_);
		volume += object :: Object :: getAggregateVolume (column_);
		volume += object :: Object :: getAggregateVolume (file_);
		return volume;
	}

	/*************************************
	 *		Private static attributes
	 *************************************/

	option :: Integer* Location :: line_   = NULL;
	option :: Integer* Location :: column_ = NULL;
	option :: Path*    Location :: file_   = NULL;

	const char* Location :: optionGroupName_ = "location";
}
}
}

#endif /*MDL_AUXILIARY_CONFIG_LOCATION_CPP_*/
