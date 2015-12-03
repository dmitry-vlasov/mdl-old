/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_parser_Term.hpp                                      */
/* Description:     EL term parser                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_PARSER_TERM_HPP_
#define DEL_PARSER_TERM_HPP_

#include "del/interface/del_interface.hpp"
#include "del/lexer/del_lexer.hpp"
#include "del/parser/del_parser.dpp"

namespace del {
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
	// internal part
	parser :: Term* termParser_;

	// external part
	Location location_;
	value :: Variable variable_;
	value :: Relation relation_;
	value :: Signature signature_;
	const del :: Term* term_;
	const del :: Term* term_1_;
	const del :: Term* term_2_;

	vector :: Term terms_;
	enum {
		INITIAL_TERM_VECTOR_CAPACITY = 8
	};
};

}
}

#endif /*DEL_PARSER_TERM_HPP_*/
