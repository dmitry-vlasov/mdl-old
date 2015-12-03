/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_source_Include.cpp                                */
/* Description:     metamath file inclusion                                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_SOURCE_INCLUDE_CPP_
#define MM_AST_SOURCE_INCLUDE_CPP_

#include "auxiliary/mm_auxiliary.hpp"
#include "lexer/mm_lexer.hpp"
#include "ast/mm_ast.hpp"

namespace mm {
namespace ast {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Include :: Include (const Path* const path) :
	location_ (),
	path_ (*path) {
	}
	inline
	Include :: Include (const Location& location, const String& path) :
	location_ (location),
	path_ (path) {
	}
	Include :: ~ Include() {
	}

	// source :: Include implementation
	const Path&
	Include :: getPath() const {
		return path_;
	}

	// object :: Verifiable implementation
	void
	Include :: check() const {
	}

	// object :: Translatable implementation
	const object :: Targetive*
	Include :: translate() const {
		return new ast :: target :: Import (this);
	}
	bool
	Include :: isBlock() const {
		return false;
	}
	bool
	Include :: isDisjoined() const {
		return false;
	}
	bool
	Include :: isFloating() const {
		return false;
	}
	bool
	Include :: isEssential() const {
		return false;
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Include :: write (String& string) const {
		string << tab << mm :: Token :: inclusionBegin_;
		string << getPath() << mm :: Token :: inclusionEnd_ << endLine;
	}

	// object :: Object implementation
	void
	Include :: commitSuicide() {
		delete this;
	}
	Size_t
	Include :: getVolume() const
	{
		Size_t volume = 0;
		volume += location_.getVolume();
		volume += path_.getVolume();
		return volume;
	}
	Size_t
	Include :: getSizeOf() const {
		return sizeof (Include);
	}
}
}
}

#endif /* MM_AST_SOURCE_INCLUDE_CPP_ */
