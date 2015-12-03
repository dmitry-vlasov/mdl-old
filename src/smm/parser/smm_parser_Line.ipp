/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_parser_Line.ipp                                      */
/* Description:     assertion line parser                                    */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_PARSER_LINE_IPP_
#define SMM_PARSER_LINE_IPP_

#include "smm/lexer/smm_lexer.hpp"
#include "smm/parser/smm_parser.hpp"

namespace smm {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	template<Token :: Type B, bool f, bool i, Token :: Type E>
	inline
	Line<B, f, i, E> :: Line () :
	location_ (),
	index_ (value :: undefined :: INDEX),
	vectorParser_ (new VectorParser_()) {
	}
	template<Token :: Type B, bool f, bool i, Token :: Type E>
	Line<B, f, i, E> :: ~ Line () {
		deleteAggregateObject (vectorParser_);
	}

using manipulator :: space;
using manipulator :: endLine;
using manipulator :: tab;

	template<Token :: Type B, bool f, bool i, Token :: Type E>
	inline const Expression*
	Line<B, f, i, E> :: parse (Lexer* const lexer, const value :: Index index)
	{
		location_ = lexer->getLocation();
		index_ = f ?
			(
				(i || Config :: noLabels()) ?
				lexer->scanIndex() :
				lexer->scanLabel()
			):
			value :: undefined :: INDEX;
		if (f && i && (index_ != index)) {
			Error* error = new Error (location_, Error :: PARSER);
			error->message() << "expected" << space << index << space << "index" << endLine;
			error->message() << "scanned" << space << index_ << space << "index" << endLine;
			throw error;
		}
		const vector :: Literal&
			literalVector = vectorParser_->parse (lexer);
		return new Expression (location_, literalVector);
	}
	template<Token :: Type B, bool f, bool i, Token :: Type E>
	inline value :: Index
	Line<B, f, i, E> :: getIndex() const {
		return index_;
	}

	// object :: Object implementation
	template<Token :: Type B, bool f, bool i, Token :: Type E>
	void
	Line<B, f, i, E> :: commitSuicide() {
		delete this;
	}
	template<Token :: Type B, bool f, bool i, Token :: Type E>
	Size_t
	Line<B, f, i, E> :: getVolume() const {
		return getAggregateVolume (vectorParser_);
	}
	template<Token :: Type B, bool f, bool i, Token :: Type E>
	Size_t
	Line<B, f, i, E> :: getSizeOf() const {
		return sizeof (Line);
	}
	template<Token :: Type B, bool f, bool i, Token :: Type E>
	void
	Line<B, f, i, E> :: show (String&) const {
	}
}
}

#endif /*SMM_PARSER_LINE_IPP_*/
