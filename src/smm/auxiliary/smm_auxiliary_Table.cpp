/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_auxiliary_Table.cpp                                  */
/* Description:     identificator table class                                */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "smm/auxiliary/smm_auxiliary_Table.hpp"

namespace smm {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	inline Table :: Files_*
	Table :: files() {
		return files_;
	}
	inline Table :: Literals_*
	Table :: literals() {
		return literals_;
	}
	inline Table :: Labels_*
	Table :: labels() {
		return labels_;
	}
	inline void
	Table :: release()
	{
		deleteAggregateObject (files_);
		deleteAggregateObject (literals_);
		deleteAggregateObject (labels_);
	}

using manipulator :: tab;
using manipulator :: endLine;

	// nstd :: Static implementation
	void
	Table :: initRaw ()
	{
		files_  = new Literals_ (INITIAL_FILES_CAPACITY);
		literals_  = new Literals_ (INITIAL_LITERALS_CAPACITY);
		labels_  = new Labels_ (INITIAL_LABELS_CAPACITY);
	}
	void
	Table :: showRaw (String& string)
	{
		if (isInitialized()) {
			string << "identifier tables:" << endLine;
			string << "-------------------------" << endLine;
			string << tab << "files:    " << *files_ << endLine;
			string << tab << "literals: " << *literals_ << endLine;
			string << tab << "labels:   " << *labels_ << endLine;
		}
	}
	Size_t
	Table :: getRawVolume()
	{
		Size_t volume = 0;
		volume += getAggregateVolume (files_);
		volume += getAggregateVolume (literals_);
		volume += getAggregateVolume (labels_);
		return volume;
	}

	/************************************
	 *		Private static attributes
	 ************************************/

	Table :: Files_*
		Table :: files_ = NULL;
	Table :: Literals_*
		Table :: literals_ = NULL;
	Table :: Labels_*
		Table :: labels_ = NULL;
}
}


