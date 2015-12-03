/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_block_Evaluation.cpp                          */
/* Description:     assertion evaluation parser                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_BLOCK_EVALUATION_CPP_
#define MDL_PARSER_BLOCK_EVALUATION_CPP_

#include "mdl/lexer/mdl_lexer.hpp"
#include "mdl/form/mdl_form.hpp"
#include "mdl/parser/mdl_parser.hpp"

namespace mdl {
namespace parser {
namespace block {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Evaluation :: Evaluation() :
	identificatorParser_ (new parser :: Identificator()),
	functionParser_ (new parser :: evaluation :: Function()),
	location_ (),
	comments_ (NULL),
	name_ (value :: undefined :: NAME),
	identificator_ (NULL),
	functionVector_ (INITIAL_FUNCTION_VECTOR_CAPACITY) {
	}
	Evaluation :: ~ Evaluation()
	{
		deleteAggregateObject (identificatorParser_);
		deleteAggregateObject (functionParser_);
	}

	mdl :: Evaluation*
	Evaluation :: parse (Lexer* lexer, mdl :: Theory* theory)
	{
		/* Example:
		 *
		evaluation evalNew of xxx.yyy.a1i {
		prop 1 =
		  sum [0.0]
		  (
		      mult [0.2] (sub_cplx ()),
		      mult [0.4] (exp_cplx ()),
		      mult [0.2] (forking [12] ()),
		      mult [1.0],
		      fris
				[
				  + theorem xxx.yyy proof 1 step (15.6.6)
				  + theorem xxx.yyy proof 2 step (28.4)
				  - theorem yyy.xxx proof 1 step 12,
				  - theorem yyy.xxx proof 3 step 22
				] ()
			  )
			prop 2 =
			  sum [0.2]
			  (
				  mult [0.2] (sub_cplx ()),
				  mult [0.4] (exp_cplx ()),
				  mult [0.2] (forking [15] ()),
				  mult [1.0] (const [0] ()) // trivial FRiS - NO
			  )
			}
		 */
		location_ = lexer->getLocation();
		if (lexer->scan<Token :: NAME, Token :: OF>() == Token :: NAME) {
			name_ = Table :: names()->add (lexer->getToken());
			lexer->scan <Token :: OF>();
		} else {
			name_ = Table :: defaultName();
		}
		identificator_ = identificatorParser_->parse (lexer);
		comments_ =
			lexer->comments().isEmpty() ?
			NULL :
			new form :: Comments (lexer->comments());
		lexer->comments().clear();
		functionVector_.clear();
		lexer->scan <Token :: OPEN_BRACE>();

		while (true) {
			mdl :: evaluation :: Function*
				function = functionParser_->parse (lexer, theory);
			if (function != NULL) {
				functionVector_.add (function);
			} else {
				break;
			}
		}
		return new form :: Evaluation
		(
			location_,
			comments_,
			name_,
			identificator_,
			functionVector_,
			theory
		);
	}

	// object :: Object implementation
	void
	Evaluation :: commitSuicide() {
		delete this;
	}
	Size_t
	Evaluation :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (identificatorParser_);
		volume += getAggregateVolume (functionParser_);
		volume += functionVector_.getVolume();
		return volume;
	}
	Size_t
	Evaluation :: getSizeOf() const {
		return sizeof (Evaluation);
	}
	void
	Evaluation :: show (String&) const {
	}
}
}
}

#endif /*MDL_PARSER_BLOCK_EVALUATION_CPP_*/
