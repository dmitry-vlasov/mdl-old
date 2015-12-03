/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_parser_Term.hpp                              */
/* Description:     mancehster OWL term parser                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_MAN_PARSER_TERM_HPP_
#define DEL_OWL_MAN_PARSER_TERM_HPP_

#include "del/owl/man/lexer/del_owl_man_lexer.hpp"
#include "del/owl/man/parser/del_owl_man_parser.dpp"
#include "del/owl/man/source/del_owl_man_source.dpp"

namespace del {
namespace owl {
namespace man {
namespace parser {

class Term :
	public Object,
	public Scalar<Term> {
public :
	Term();
	virtual ~ Term();

	const del :: Term* parse (Lexer*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	// external part
	Location location_;

	// internal part
	struct Token_ : Scalar<Token_, allocator :: Heap> {
		Token_ () :
		string_ (INITIAL_TOKEN_STRING_CAPACITY),
		type_ (Token :: UNKNOWN),
		term_ (NULL),
		location_ () {
		}
		Token_ (const Token_& token) :
		string_ (token.string_),
		type_ (token.type_),
		term_ (token.term_),
		location_ (token.location_) {
		}
		~ Token_() { }
		String string_;
		Token :: Type type_;
		const del :: Term* term_;
		Location location_;
		enum {
			INITIAL_TOKEN_STRING_CAPACITY = 32
		};

		void operator = (const Token_& token)
		{
			string_.copy (token.string_);
			type_ = token.type_;
			term_ = token.term_;
			location_ = token.location_;
		}

		void init() { }
		void commitSuicide() {
			delete this;
		}
		Size_t getVolume() const {
			return string_.getVolume();
		}
		Size_t getSizeOf() const {
			return sizeof (Token_);
		}
		void show (String&) const { }
	};
	typedef
		vector :: Vector
		<
			Token_*,
			storage :: ByValue,
			allocator :: Heap
		>
		TokenVector_;

	void parseTerm();
	void parseVariables();
	bool tryToGetUp();
	bool parseSomeOnce();
	bool parseSome();
	bool parseBracketsOnce();
	bool parseBrackets();
	bool parseAndOnce();
	bool parseAnd();

	void showTokenStack() const;

	TokenVector_ tokenVector_;
	enum {
		INITIAL_TOKEN_VECTOR_CAPACITY = 32
	};
};

}
}
}
}

#endif /*DEL_OWL_MAN_PARSER_TERM_HPP_*/
