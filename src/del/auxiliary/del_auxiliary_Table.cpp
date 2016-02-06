/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File name:       del_auxiliary_Table.cpp                                  */
/* Description:     identificator table class                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/auxiliary/del_auxiliary_Table.hpp"

namespace del {
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
	inline Table :: Relations_*
	Table :: relations() {
		return relations_;
	}
	inline Table :: Theories_*
	Table :: theories() {
		return theories_;
	}
	inline Table :: Variables_*
	Table :: variables() {
		return variables_;
	}
	inline Table :: Signatures_*
	Table :: signatures() {
		return signatures_;
	}
	inline void
	Table :: release()
	{
		deleteAggregateObject (files_);
		deleteAggregateObject (relations_);
		deleteAggregateObject (theories_);
		deleteAggregateObject (variables_);
		deleteAggregateObject (signatures_);
		deleteAggregateObject (variablesStack_);
	}

	void
	Table :: pushVariables()
	{
		//Variables_* newVariables = variablesStack_->push();
		//newVariables->copy (variables_);
	}
	void
	Table :: popVariables()
	{
		//Variables_* oldVariables = variablesStack_->pop();
		//variables_->copy (oldVariables);
	}

	// nstd :: Static implementation
	void
	Table :: initRaw ()
	{
		files_  = new Files_ (INITIAL_FILES_CAPACITY);
		relations_  = new Relations_ (INITIAL_RELATIONS_CAPACITY);
		theories_  = new Theories_ (INITIAL_THEORIES_CAPACITY);
		variables_ = new Variables_ (INITIAL_VARIABLES_CAPACITY);
		signatures_ = new Signatures_ (INITIAL_SIGNATURES_CAPACITY);
		variablesStack_ = new VariablesStack_ (INITIAL_VARIABLES_STACK_CAPACITY);

		// !!! temporary
		Variables_* newVariables = variablesStack_->push();
		newVariables->copy (variables_);
	}
	void
	Table :: showRaw (String& string)
	{
		if (isInitialized()) {
			string << "identifier tables:" << endLine;
			string << "-------------------------" << endLine;
			string << tab << "files:    " << *files_ << endLine;
			string << tab << "relations: " << *relations_ << endLine;
			string << tab << "theories: " << *theories_ << endLine;
			string << tab << "variables: " << *variables_ << endLine;
			string << tab << "signatures: " << *signatures_ << endLine;
		}
	}
	Size_t
	Table :: getRawVolume()
	{
		Size_t result = 0;
		result += getAggregateVolume (files_);
		result += getAggregateVolume (relations_);
		result += getAggregateVolume (theories_);
		result += getAggregateVolume (variables_);
		result += getAggregateVolume (signatures_);
		result += getAggregateVolume (variablesStack_);
		return result;
	}

	/************************************
	 *		Private static attributes
	 ************************************/

	Table :: Files_*
		Table :: files_ = NULL;
	Table :: Relations_*
		Table :: relations_ = NULL;
	Table :: Theories_*
		Table :: theories_ = NULL;
	Table :: Variables_*
		Table :: variables_ = NULL;
	Table :: Signatures_*
		Table :: signatures_ = NULL;
	Table :: VariablesStack_*
		Table :: variablesStack_ = NULL;
}
}


