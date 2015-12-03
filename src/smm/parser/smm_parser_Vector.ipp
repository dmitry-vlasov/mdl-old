/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_parser_Vector.ipp                                    */
/* Description:     literal vector parser                                    */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_PARSER_VECTOR_IPP_
#define SMM_PARSER_VECTOR_IPP_

#include "smm/lexer/smm_lexer.hpp"
#include "smm/auxiliary/smm_auxiliary.hpp"
#include "smm/parser/smm_parser.hpp"

namespace smm {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	template<Token :: Type B, bool f, Token :: Type E>
	inline
	Vector<B, f, E> :: Vector() :
	literalVector_ (INITIAL_LITERAL_VECTOR_CAPACITY) {
	}
	template<Token :: Type B, bool f, Token :: Type E>
	Vector<B, f, E> :: ~ Vector() {
	}

	template<Token :: Type B, bool f, Token :: Type E>
	const vector :: Literal&
	Vector<B, f, E> :: parse (Lexer* const lexer)
	{
		if (f) {
			lexer->scan<B>();
		}
		literalVector_.clear();
		while (lexer->scan<Token :: LITERAL, E> () == Token :: LITERAL) {
			const String&
				token = lexer->getToken();
			if (token.getSize() == 0) {
				Error* error = new Error (Error :: INPUT, "illegal token - empty");
				throw error;
			}
			const value :: Literal
				literal = Table :: literals()->add (token);
			literalVector_.add (literal);
		}
		return literalVector_;
	}

	// object :: Object implementation
	template<Token :: Type B, bool f, Token :: Type E>
	void
	Vector<B, f, E> :: commitSuicide() {
		delete this;
	}
	template<Token :: Type B, bool f, Token :: Type E>
	Size_t
	Vector<B, f, E> :: getVolume() const {
		return literalVector_.getVolume();
	}
	template<Token :: Type B, bool f, Token :: Type E>
	Size_t
	Vector<B, f, E> :: getSizeOf () const {
		return sizeof (Vector);
	}
	template<Token :: Type B, bool f, Token :: Type E>
	void
	Vector<B, f, E> :: show (String&) const {
	}
}
}

#endif /*SMM_PARSER_VECTOR_IPP_*/
