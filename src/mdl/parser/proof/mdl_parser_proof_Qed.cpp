/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_proof_Qed.cpp                                 */
/* Description:     proof q.e.d. parser                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_PROOF_QED_CPP_
#define MDL_PARSER_PROOF_QED_CPP_

namespace mdl {
namespace parser {
namespace proof {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Qed :: Qed() :
	location_ (),
	comments_ (NULL),
	kind_ (value :: undefined :: KIND),
	prop_ (index :: undefined :: ARITY),
	step_ (index :: undefined :: STEP) {
	}
	Qed :: ~ Qed() {
	}

	mdl :: proof :: Qed*
	Qed :: parse
	(
		Lexer* lexer,
		mdl :: Theory* theory,
		mdl :: proof :: Line* line
	)
	{
		const bool create = (!Config :: shallowParsing() || lexer->isTop());
		location_ = lexer->getLocation();
		prop_ = index :: undefined :: ARITY;
		lexer->scan<Token :: PROP, Token :: CLAIM>();
		kind_ = lexer->getTokenType();

		if (kind_ == Token :: PROP) {
			if (lexer->scan<Token :: EQUALITY, Token :: NUMBER>() == Token :: NUMBER) {
				prop_  = lexer->getToken().getIntegerValue<index :: Arity>() - 1;
				lexer->scan<Token :: EQUALITY>();
			} else {
				prop_ = 0;
			}
		} else {
			lexer->scan<Token :: EQUALITY>();
		}
		lexer->scan <Token :: STEP>();
		step_ = lexer->scanNumber<index :: Step>() - 1;
		lexer->scan <Token :: SEMICOLON>();

		comments_ =
			(lexer->comments().isEmpty() || !create) ?
			NULL :
			new form :: Comments (lexer->comments());
		lexer->comments().clear();
		if (create) {
			return new form :: proof :: Qed
			(
				line,
				location_,
				comments_,
				kind_,
				prop_,
				step_,
				theory
			);
		} else {
			return NULL;
		}
	}

	// object :: Object implementation
	void
	Qed :: commitSuicide() {
		delete this;
	}
	Size_t
	Qed :: getVolume() const {
		return 0;
	}
	Size_t
	Qed :: getSizeOf() const {
		return sizeof (Qed);
	}
	void
	Qed :: show (String&) const {
	}
}
}
}

#endif /*MDL_PARSER_PROOF_QED_CPP_*/
