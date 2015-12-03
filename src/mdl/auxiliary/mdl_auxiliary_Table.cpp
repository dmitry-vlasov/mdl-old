/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_Table.cpp                                  */
/* Description:     identificator table class                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_TABLE_CPP_
#define MDL_AUXILIARY_TABLE_CPP_

#include "mdl/auxiliary/mdl_auxiliary_Table.hpp"

namespace mdl {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

using manipulator :: tab;
using manipulator :: endLine;

	inline Table :: Files_*
	Table :: files() {
		return files_;
	}
	inline Table :: Literals_*
	Table :: literals() {
		return literals_;
	}
	inline Table :: Names_*
	Table :: names() {
		return names_;
	}

	void
	Table :: clear()
	{
		release();
		init();
	}

	inline value :: Name
	Table :: defaultName() {
		return defaultName_;
	}
	void
	Table :: dumpLiteral (value :: Literal literal) {
		literals_->dumpLiteral (literal);
	}
	void
	Table :: dumpName (value :: Name name) {
		names_->dumpName (name);
	}

	// nstd :: Static implementation
	void
	Table :: init()
	{
		if (files_ != NULL) {
			return;
		}
		files_  = new Files_ (INITIAL_FILES_CAPACITY);
		literals_  = new Literals_ (INITIAL_LITERALS_CAPACITY);
		names_ = new Names_ (INITIAL_NAMES_CAPACITY);
		if (defaultName_ == value :: undefined :: NAME) {
			defaultName_ = names_->add ("_default_Name_");
		}
	}
	void
	Table :: release()
	{
		deleteAggregateObject (files_);
		deleteAggregateObject (literals_);
		deleteAggregateObject (names_);
	}
	void
	Table :: show (String& string)
	{
		if (isInitialized()) {
			string << "identifier tables:" << endLine;
			string << "-------------------------" << endLine;
			string << tab << "files:    " << *files_ << endLine;
			string << tab << "literals: " << *literals_ << endLine;
			string << tab << "names:    " << *names_ << endLine;
		}
	}
	Size_t
	Table :: getVolume()
	{
		Size_t result = 0;
		result += getAggregateVolume (files_);
		result += getAggregateVolume (literals_);
		result += getAggregateVolume (names_);
		return result;
	}

	/************************************
	 *		Private static attributes
	 ************************************/

	Table :: Files_*
		Table :: files_ = NULL;
	Table :: Literals_*
		Table :: literals_ = NULL;
	Table :: Names_*
		Table :: names_ = NULL;
	value :: Name
		Table :: defaultName_ = value :: undefined :: NAME;
}
}

#endif /*MDL_AUXILIARY_TABLE_CPP_*/
