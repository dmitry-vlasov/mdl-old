/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_parser_DisjointWith.hpp                      */
/* Description:     owl disjoint with class substrusture parser              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_MAN_PARSER_DISJOINT_WITH_HPP_
#define DEL_OWL_MAN_PARSER_DISJOINT_WITH_HPP_

#include "del/owl/man/lexer/del_owl_man_lexer.hpp"
#include "del/owl/man/parser/del_owl_man_parser.dpp"
#include "del/owl/man/source/del_owl_man_source.dpp"

namespace del {
namespace owl {
namespace man {
namespace parser {

class DisjointWith :
	public Object,
	public Scalar<DisjointWith> {
public :
	DisjointWith();
	virtual ~ DisjointWith();

	void parse (Lexer*, const source :: Class*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	// external part
	Location location_;

	// internal part
	parser :: Term* termParser_;
};

}
}
}
}

#endif /*DEL_OWL_MAN_PARSER_DISJOINT_WITH_HPP_*/
