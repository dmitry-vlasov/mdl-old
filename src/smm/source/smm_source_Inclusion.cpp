/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File Name:       smm_source_Inclusion.cpp                                 */
/* Description:     smm file inclusion                                       */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_SOURCE_INCLUSION_CPP_
#define SMM_SOURCE_INCLUSION_CPP_

#include "smm/auxiliary/smm_auxiliary.hpp"
#include "smm/lexer/smm_lexer.hpp"
#include "smm/source/smm_source.hpp"

namespace smm {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Inclusion :: Inclusion (const Location& location, const String& path) :
	location_ (location),
	path_ (path) {
	}
	Inclusion :: ~ Inclusion() {
	}

	// smm :: Inclusion implementation
	const String&
	Inclusion :: getPath() const {
		return path_;
	}

	// object :: Verifiable implementation
	void
	Inclusion :: verify() const {
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Object implementation
	void
	Inclusion :: commitSuicide() {
		delete this;
	}
	Size_t
	Inclusion :: getVolume() const
	{
		Size_t volume = 0;
		volume += location_.getVolume();
		volume += path_.getVolume();
		return volume;
	}
	Size_t
	Inclusion :: getSizeOf() const {
		return sizeof (Inclusion);
	}
	void
	Inclusion :: show (String& string) const
	{
		string << tab << smm :: Token :: inclusionBegin_ << space;
		string << getPath() << space << smm :: Token :: inclusionEnd_ << endLine;
		string << endLine;
	}
}
}

#endif /*SMM_SOURCE_INCLUSION_CPP_*/
