/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_lexer_Scaner.cpp                                     */
/* Description:     smm scaner                                               */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_LEXER_SCANER_CPP_
#define SMM_LEXER_SCANER_CPP_

#include "smm/lexer/smm_lexer.hpp"

namespace smm {
namespace lexer {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Scaner :: Scaner (Source& source) :
	source_ (source),

	literalScaner_ (source_),
	indexScaner_ (source_),
	labelScaner_ (source_),
	pathScaner_ (source_),
	whitespaceScaner_ (source_),

	inExpression_ (false),
	inProof_ (false),
	inInclude_ (false),
	inLabel_ (false),
	inIndex_ (false) {
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
			} else if (inLabel_ ){
				inLabel_ = false;
				return finalize (labelScaner_.scan());
			} else if (inIndex_ ){
				inIndex_ = false;
				return finalize (indexScaner_.scan());
			} else {
				return finalize (scanPrefixChar());
			}
		}
		++ source_;

		return finalize (scanSingleChar());
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
			return Token :: DISJOINTED;
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
			return Token :: EQUALITY;
		default :
			++ source_;
			return Token :: UNKNOWN;
		}
	}
	Token :: Type
	Scaner :: scanPrefixChar()
	{
		const char ch = source_.getChar().getValue();
		++ source_;
		if (Config :: noLabels()) {
			inIndex_ = true;
		} else {
			switch (ch) {
				case 'f' :
				case 'e' :
				case 'i' :
					inIndex_ = true; break;
				case 'a' :
				case 'p' :
					inLabel_ = true; break;
				default : break;
			}
		}
		switch (ch) {
			case 'f' : return finalize (Token :: PREFIX_F);
			case 'e' : return finalize (Token :: PREFIX_E);
			case 'i' : return finalize (Token :: PREFIX_I);
			case 'a' : return finalize (Token :: PREFIX_A);
			case 'p' : return finalize (Token :: PREFIX_P);
			default :  return Token :: UNKNOWN;
		}
	}
	Token :: Type
	Scaner :: finalize (const Token :: Type type) {
		source_.stopToken();
		return type;
	}
}
}

#endif /*SMM_LEXER_SCANER_CPP_*/

