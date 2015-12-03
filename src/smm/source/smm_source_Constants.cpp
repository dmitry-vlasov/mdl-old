/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File Name:       smm_source_Constants.cpp                                 */
/* Description:     smm constants                                            */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_SOURCE_CONSTANTS_CPP_
#define SMM_SOURCE_CONSTANTS_CPP_

#include "smm/auxiliary/smm_auxiliary.hpp"
#include "smm/lexer/smm_lexer.hpp"
#include "smm/math/smm_math.hpp"
#include "smm/source/smm_source.hpp"

namespace smm {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Constants :: Constants
	(
		const Location& location,
		const Expression* literals
	) :
	location_ (location),
	literals_ (literals) {
		Math :: constants()->add (this);
	}
	Constants :: ~ Constants() {
		delete literals_;
	}

	// smm :: Constants implementation
	void
	Constants :: addTo (vector :: Literal& literalVector) const
	{
		for (index :: Literal i = 0; i < literals_->getSize(); ++ i ) {
			const value :: Literal
				constant = literals_->getSymbol (i).getLiteral();
			if (literalVector.contains (constant)) {
				throw new Error (location_, Error :: SEMANTIC, "duplicate constant declaration.");
			}
			literalVector.add (constant);
		}
	}

	// object :: Verifiable implementation
	void
	Constants :: verify() const {
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Object implementation
	void
	Constants :: commitSuicide() {
		delete this;
	}
	Size_t
	Constants :: getVolume() const
	{
		Size_t volume = 0;
		volume += location_.getVolume();
		volume += getAggregateVolume (literals_);
		return volume;
	}
	Size_t
	Constants :: getSizeOf() const {
		return sizeof (Constants);
	}
	void
	Constants :: show (String& string) const
	{
		string << tab << Token :: constant_ << space;
		string << *literals_ << space;
		string << Token :: end_ << endLine;
		string << endLine;
	}

}
}

#endif /*SMM_SOURCE_CONSTANTS_CPP_*/
