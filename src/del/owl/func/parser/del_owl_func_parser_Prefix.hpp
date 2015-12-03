/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_parser_Prefix.hpp                           */
/* Description:     functional OWL2 prefix parser                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_FUNC_PARSER_PREFIX_HPP_
#define DEL_OWL_FUNC_PARSER_PREFIX_HPP_

#include "del/owl/func/lexer/del_owl_func_lexer.hpp"
#include "del/owl/func/parser/del_owl_func_parser.dpp"
#include "del/owl/func/source/del_owl_func_source.dpp"

namespace del {
namespace owl {
namespace func {
namespace parser {

class Prefix :
	public Object,
	public Scalar<Prefix> {
public :
	Prefix();
	virtual ~ Prefix();

	const source :: Prefix* parse (Lexer*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	// external part
	Location location_;
	source :: Prefix* annotation_;

	// internal part
	String string_;
	enum {
		INITIAL_STRING_CAPACITY = 32
	};
};

}
}
}
}

#endif /*DEL_OWL_FUNC_PARSER_PREFIX_HPP_*/
