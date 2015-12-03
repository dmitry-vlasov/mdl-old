/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_parser_SubClasses.hpp                       */
/* Description:     functional OWL2 sub classes parser                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_FUNC_PARSER_SUB_CLASSES_HPP_
#define DEL_OWL_FUNC_PARSER_SUB_CLASSES_HPP_

#include "del/interface/del_interface.hpp"
#include "del/owl/func/lexer/del_owl_func_lexer.hpp"
#include "del/owl/func/parser/del_owl_func_parser.dpp"

namespace del {
namespace owl {
namespace func {
namespace parser {

class SubClasses :
	public Object,
	public Scalar<SubClasses> {
public :
	SubClasses();
	virtual ~ SubClasses();

	const del :: Formula* parse (Lexer*);

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

#endif /*DEL_OWL_FUNC_PARSER_SUB_CLASSES_HPP_*/
