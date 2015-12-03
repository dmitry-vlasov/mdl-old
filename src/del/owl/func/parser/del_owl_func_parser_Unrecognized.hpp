/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_parser_Unrecognized.hpp                     */
/* Description:     functional OWL2 parser for unrecognized objects          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_FUNC_PARSER_UNRECOGNIZED_HPP_
#define DEL_OWL_FUNC_PARSER_UNRECOGNIZED_HPP_

#include "del/owl/func/lexer/del_owl_func_lexer.hpp"
#include "del/owl/func/parser/del_owl_func_parser.dpp"
#include "del/owl/func/source/del_owl_func_source.dpp"

namespace del {
namespace owl {
namespace func {
namespace parser {

class Unrecognized :
	public Object,
	public Scalar<Unrecognized> {
public :
	Unrecognized();
	virtual ~ Unrecognized();

	const source :: Unrecognized* parse (const String&, Lexer*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	// external part
	Location location_;
	source :: Unrecognized* unrecognized_;

	// internal part
	vector :: String stringVector_;
	enum {
		INITIAL_STRING_VECTOR_CAPACITY = 4,
		INITIAL_STRING_CAPACITY = 32
	};
};

}
}
}
}

#endif /*DEL_OWL_FUNC_PARSER_UNRECOGNIZED_HPP_*/
