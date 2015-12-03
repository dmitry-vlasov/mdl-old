/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_parser_Subclass.hpp                          */
/* Description:     manchester OWL subclass parser                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_MAN_PARSER_SUBCLASS_HPP_
#define DEL_OWL_MAN_PARSER_SUBCLASS_HPP_

#include "del/owl/man/lexer/del_owl_man_lexer.hpp"
#include "del/owl/man/parser/del_owl_man_parser.dpp"
#include "del/owl/man/source/del_owl_man_source.dpp"

namespace del {
namespace owl {
namespace man {
namespace parser {

class Subclass :
	public Object,
	public Scalar<Subclass> {
public :
	Subclass();
	virtual ~ Subclass();

	const source :: Subclass* parse (Lexer*, const source :: Class*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	// external part
	Location location_;
	source :: Subclass* subclass_;

	// internal part
	parser :: Term* termParser_;
};

}
}
}
}

#endif /*DEL_OWL_MAN_PARSER_SUBCLASS_HPP_*/
