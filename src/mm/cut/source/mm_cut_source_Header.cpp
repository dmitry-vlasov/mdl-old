/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_cut_source_Header.cpp                                 */
/* Description:     mm cutting block header                                  */
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
	Header :: Header
	(
		const Location& location,
		const String& string
	) :
	location_ (location),
	string_ (string) {
		nomalize();
	}
	Header :: ~ Header() {
	}

	inline const String&
	Header :: getString() const {
		return string_;
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Object implementation
	void
	Header :: commitSuicide() {
		delete this;
	}
	Size_t
	Header :: getVolume() const
	{
		Size_t volume = 0;
		volume += location_.getVolume();
		volume += string_.getVolume();
		return volume;
	}
	Size_t
	Header :: getSizeOf() const {
		return sizeof (Header);
	}
	void
	Header :: show (String& string) const {
		string << string_ << endLine;
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Header :: nomalize()
	{
		typedef String :: Index_ Index;
		for (Index i = 0; i < string_.getSize(); ++ i) {
			char& ch = string_.getReference (i);
			for (Index j = 0; j < REPLACE_ARRAY_SIZE; ++ j) {
				if (ch == range_ [j]) {
					ch = image_ [j];
				}
			}
		}
		while (true) {
			if (Table :: files()->contains (string_)) {
				string_ << "_";
			} else {
				break;
			}
		}
		Table :: files()->add (string_);
	}

	/************************************
	 *		Static private attributes
	 ************************************/

	const char Header :: range_[REPLACE_ARRAY_SIZE] =
		{ ' ', '/', '\'', '\t', '$', '.', '\"', ';', ',', ':', '^', '(', ')', '+', '=', '&'};
	const char Header :: image_[REPLACE_ARRAY_SIZE] =
		{ '_', '_', '_',   '_', '_', '_', '_',  '_', '_', '_', '_', '_', '_', '-', '-', '-'};
}
}
}



