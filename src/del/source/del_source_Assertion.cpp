/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_Assertion.cpp                                 */
/* Description:     test assertion class                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/auxiliary/del_auxiliary.hpp"
#include "del/source/del_source.hpp"

namespace del {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Assertion :: Assertion
	(
		const Location& location,
		const del :: Comments* comments,
		const value :: Theory theoryName,
		const value :: Signature signatureName,
		const vector :: value :: Symbol& components,
		const bool isStrong
	) :
	location_ (location),
	comments_ (comments),
	decompose_ (new source :: Decompose (Location(), NULL, theoryName, signatureName, isStrong)),
	decomposition_ (new source :: Decomposition (Location(), NULL, theoryName, signatureName, components, isStrong)) {
	}
	Assertion :: ~ Assertion()
	{
		deleteAggregateObject (comments_);
		deleteAggregateObject (decompose_);
		deleteAggregateObject (decomposition_);
	}

using manipulator :: endLine;

	// del :: Assertion implementation
	void
	Assertion :: verify() const
	{
		const del :: Decomposition* const
			decomposition = decompose_->decompose();
		if (decomposition == NULL) {
			return;
		}
		if (!decomposition_->isEqual (decomposition)) {
			Del :: log()->message() << "****** ERROR ******" << endLine;
			Del :: log()->message() << "assertion verification failed" << endLine;
			Del :: log()->message() << "requested decomposition:" << endLine;
			//Del :: log()->message() << *decomposition_ << endLine;
			decomposition_->replicateCompletely (Del :: log()->message());
			Del :: log()->message() << "decomposition obtained:" << endLine;
			//Del :: log()->message() << *decomposition << endLine;
			decomposition->replicateCompletely (Del :: log()->message());
			Del :: log()->message() << endLine;
			Del :: log()->message() << endLine;

			String string (1024);

			std :: cout  << "assertion verification failed" << std :: endl;
			std :: cout  << "requested decomposition:" << std :: endl;
			decomposition_->replicateCompletely (string);
			std :: cout << string << std :: endl;
			string.clear();
			std :: cout << "decomposition obtained:" << std :: endl;
			decomposition->replicateCompletely (string);
			std :: cout << string << std :: endl;
			std :: cout  << std :: endl;

			/*Error* error = new Error (location_, Error :: SEMANTIC);
			error->message() << "assertion verification failed" << endLine;
			error->message() << "requested decomposition:" << endLine;
			error->message() << *decomposition_;
			error->message() << "decomposition obtained:" << endLine;
			error->message() << *decomposition;
			throw error;*/
		}
		const_cast<del :: Decomposition*>(decomposition)->commitSuicide();
	}
	del :: Decompose*
	Assertion :: decompose() {
		return decompose_;
	}
	del :: Decomposition*
	Assertion :: decomposition() {
		return decomposition_;
	}

using manipulator :: space;
using manipulator :: underline;
using manipulator :: endLine;

	// object :: Writable implementation
	void
	Assertion :: replicate (String& string) const
	{
		return;
		if (comments_ != NULL) {
			comments_->translate (string);
		}
		string << location_.getIndent();
		string << Token :: assert_ << space;
		decomposition_->replicate (string);
	}
	void
	Assertion :: translate (String& string) const {
		replicate (string);
	}

	// object :: Object implementation
	void
	Assertion :: commitSuicide() {
		delete this;
	}
	Size_t
	Assertion :: getSizeOf() const {
		return sizeof (Assertion);
	}
	Size_t
	Assertion :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (comments_);
		volume += getAggregateVolume (decompose_);
		volume += getAggregateVolume (decomposition_);
		return volume;
	}
}
}


