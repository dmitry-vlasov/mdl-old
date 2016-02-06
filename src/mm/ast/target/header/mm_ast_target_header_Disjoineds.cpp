/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_header_Disjoineds.cpp                      */
/* Description:     mdl disjoined variables restrictions                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/lexer/mdl_lexer_Token.hpp"
#include "auxiliary/mm_auxiliary.hpp"
#include "ast/mm_ast.hpp"

namespace mm {
namespace ast {
namespace target {
namespace header {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Disjoineds :: Disjoineds (const bool axiomatic) :
	disjoineds_ (),
	axiomatic_ (axiomatic){
	}
	Disjoineds :: ~ Disjoineds() {
	}

	// target :: Disjointeds interface
	void
	Disjoineds :: addDisjoined (const mm :: target :: Disjoined* const disjoined) {
		disjoineds_.addLast (disjoined);
	}

	// object :: Targetive implementation
	void
	Disjoineds :: complete (mm :: target :: Block* const) const {
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Writable implementation
	void
	Disjoineds :: write (String& string) const
	{
		if (axiomatic_ && isEmpty()) {
			return;
		}
		string << mdl :: Token :: disjointed_  << space;
		string << mdl :: Token :: openBracket_;
		const Node_*
			node = disjoineds_.getFirst();
		while (node != NULL) {
			if (!node->getValue()->isEmpty()) {
				node->getValue()->write (string);
				if (isLast (node)) {
					break;
				} else {
					string << mdl :: Token :: comma_ << space;
				}
			}
			node = node->getNext();
		}
		string << mdl :: Token :: closeBracket_;
	}

	// object :: Object implementation
	void
	Disjoineds :: commitSuicide() {
		delete this;
	}
	Size_t
	Disjoineds :: getVolume() const {
		return disjoineds_.getVolume();
	}
	Size_t
	Disjoineds :: getSizeOf() const {
		return sizeof (Disjoineds);
	}

	/****************************
	 *		Private members
	 ****************************/

	bool
	Disjoineds :: isEmpty() const
	{
		const Node_*
			node = disjoineds_.getFirst();
		while (node != NULL) {
			if (!node->getValue()->isEmpty()) {
				return false;
			}
			node = node->getNext();
		}
		return true;
	}
	bool
	Disjoineds :: isLast (const Node_* node) const
	{
		if (node->getNext() == NULL) {
			return true;
		}
		node = node->getNext();
		while (node != NULL) {
			if (!node->getValue()->isEmpty()) {
				return false;
			}
			node = node->getNext();
		}
		return true;
	}
}
}
}
}



