/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_lexer_Scaner.cpp                                      */
/* Description:     metamath scaner                                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_LEXER_SCANER_CPP_
#define MM_LEXER_SCANER_CPP_

#include "lexer/mm_lexer.hpp"

namespace mm {
namespace lexer {

	/****************************
	 *		Public members
	 ****************************/

	Scaner :: Scaner (Source& source) :
	source_ (source),

	literalScaner_ (source_),
	identificatorScaner_ (source_),
	pathScaner_ (source_),
	whitespaceScaner_ (source_),

	inExpression_ (false),
	inProof_ (false),
	inInclude_ (false) {
	}
	Scaner :: ~ Scaner() {
	}

	Token :: Type
	Scaner :: scan()
	{
		whitespaceScaner_.scan();
		source_.startToken();

		if (source_.getChar().isEOF()) {
			return finalize (Token :: EOF_);
		}

		if (source_.getChar().getValue() != '$') {
			if (inExpression_) {
				return finalize (literalScaner_.scan());
			} else if (inInclude_) {
				return finalize (pathScaner_.scan());
			} else {
				return finalize (identificatorScaner_.scan());
			}
		}
		++ source_;

		return finalize (scanSingleChar());
	}
	inline Scaner :: Comments_&
	Scaner :: comments() {
		return whitespaceScaner_.comments();
	}
	inline void
	Scaner :: scanComments() {
		whitespaceScaner_.scan();
	}

using manipulator :: endLine;

	// nstd :: Object implementation
	void
	Scaner :: commitSuicide() {
		delete this;
	}
	Size_t
	Scaner :: getVolume() const {
		return whitespaceScaner_.getVolume();
	}
	Size_t
	Scaner :: getSizeOf() const {
		return sizeof (Scaner);
	}
	void
	Scaner :: show (nstd :: String<>&) const {
	}

	/****************************
	 *		Private members
	 ****************************/

	Token :: Type
	Scaner :: scanSingleChar()
	{
		switch (source_.getChar().getValue()) {
		case 'c' :
			inExpression_ = true;
			++ source_;
			return Token :: CONSTANT;
		case 'v' :
			inExpression_ = true;
			++ source_;
			return Token :: VARIABLE;
		case 'f' :
			inExpression_ = true;
			++ source_;
			return Token :: FLOATING;
		case 'd' :
			inExpression_ = true;
			++ source_;
			return Token :: DISJOINED;
		case 'e' :
			inExpression_ = true;
			++ source_;
			return Token :: ESSENTIAL;
		case 'a' :
			inExpression_ = true;
			++ source_;
			return Token :: AXIOMATIC;
		case 'p' :
			inExpression_ = true;
			++ source_;
			return Token :: PROVABLE;
		case '.' :
			inProof_ = false;
			inExpression_ = false;
			++ source_;
			return Token :: END;
		case '{' :
			++ source_;
			return Token :: BLOCK_BEGIN;
		case '}' :
			++ source_;
			return Token :: BLOCK_END;
		case '[' :
			++ source_;
			inInclude_ = true;
			return Token :: INCLUSION_BEGIN;
		case ']' :
			++ source_;
			inInclude_ = false;
			return Token :: INCLUSION_END;
		case '=' :
			inExpression_ = false;
			inProof_ = true;
			++ source_;
			return Token :: PROOF;
		default :
			++ source_;
			return Token :: UNKNOWN;
		}
	}
	Token :: Type
	Scaner :: finalize (const Token :: Type type) {
		source_.stopToken();
		return type;
	}
}
}

#endif /*MM_LEXER_SCANER_CPP_*/

