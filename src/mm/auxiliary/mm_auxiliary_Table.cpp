/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_auxiliary_Table.cpp                                   */
/* Description:     static class for metamath tables                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AUXILIARY_TABLE_CPP_
#define MM_AUXILIARY_TABLE_CPP_

namespace mm {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	void
	Table :: release ()
	{
		deleteAggregateObject (files_);
		deleteAggregateObject (literals_);
		deleteAggregateObject (identificators_);
		deleteAggregateObject (assertionLabels_);
		deleteAggregateObject (hypothesisLabels_);
	}

using manipulator :: endLine;
using manipulator :: tab;

	// nstd :: Static implementation
	void
	Table :: initRaw ()
	{
		files_ = new Files_ (INITIAL_FILES_VECTOR_CAPACITY);
		literals_ = new Literals_ (INITIAL_LITERALS_VECTOR_CAPACITY);
		identificators_ = new Identificators_ (INITIAL_IDENTIFICATORS_VECTOR_CAPACITY);
		assertionLabels_ = new AssertionLabels_ (INITIAL_ASSERTION_LABELS_VECTOR_CAPACITY);
		hypothesisLabels_ = new HypothesisLabels_ (INITIAL_HYPOTHESIS_LABELS_VECTOR_CAPACITY);
	}
	void
	Table :: showRaw (nstd :: String<>& string)
	{
		if (isInitialized()) {
			string << "name table:" << endLine;
			string << tab << "files: " << *files_ << endLine;
			string << tab << "literals: " << *literals_ << endLine;
			string << tab << "identifiers: " << *identificators_ << endLine;
			string << tab << "assertion labels: " << *assertionLabels_ << endLine;
			string << tab << "hypothesis labels: " << *hypothesisLabels_<< endLine;
		}
	}
	Size_t
	Table :: getRawVolume()
	{
		Size_t result = 0;
		result += getAggregateVolume (files_);
		result += getAggregateVolume (literals_);
		result += getAggregateVolume (identificators_);
		result += getAggregateVolume (assertionLabels_);
		result += getAggregateVolume (hypothesisLabels_);
		return result;
	}

	/************************************
	 *		Private static attributes
	 ************************************/

	Table :: Files_*
		Table :: files_ = NULL;
	Table :: Literals_*
		Table :: literals_ = NULL;
	Table :: Identificators_*
		Table :: identificators_ = NULL;
	Table :: AssertionLabels_*
		Table :: assertionLabels_ = NULL;
	Table :: HypothesisLabels_*
		Table :: hypothesisLabels_ = NULL;
}
}

#endif /*MM_AUXILIARY_TABLE_CPP_*/
