/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_cut_source_Content.cpp                                */
/* Description:     mm cutting block content                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mm/auxiliary/mm_auxiliary.hpp"
#include "mm/cut/lexer/mm_cut_lexer.hpp"
#include "mm/cut/source/mm_cut_source.hpp"

namespace mm {
namespace cut {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Content :: Content
	(
		const Location& location,
		const String& string
	) :
	location_ (location),
	string_ (string) {
	}
	Content :: ~ Content() {
	}

	inline void
	Content :: write (std :: ostream& os) const {
		os << string_;
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Object implementation
	void
	Content :: commitSuicide() {
		delete this;
	}
	Size_t
	Content :: getVolume() const
	{
		Size_t volume = 0;
		volume += location_.getVolume();
		volume += string_.getVolume();
		return volume;
	}
	Size_t
	Content :: getSizeOf() const {
		return sizeof (Content);
	}
	void
	Content :: show (String& string) const {
		string << string_ << endLine;
	}
}
}
}



