/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_parser_AnnotationAssertion.hpp              */
/* Description:     functional OWL2 annotation assertion parser              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_FUNC_PARSER_ANNOTATION_ASSERTION_HPP_
#define DEL_OWL_FUNC_PARSER_ANNOTATION_ASSERTION_HPP_

#include "del/owl/func/lexer/del_owl_func_lexer.hpp"
#include "del/owl/func/parser/del_owl_func_parser.dpp"
#include "del/owl/func/source/del_owl_func_source.dpp"

namespace del {
namespace owl {
namespace func {
namespace parser {

class AnnotationAssertion :
	public Object,
	public Scalar<AnnotationAssertion> {
public :
	AnnotationAssertion();
	virtual ~ AnnotationAssertion();

	const source :: AnnotationAssertion* parse (Lexer*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	// external part
	Location location_;
	source :: AnnotationAssertion* annotationAssertion_;

	// internal part
	String property_;
	String subject_;
	String value_;
	enum {
		INITIAL_STRING_CAPACITY = 64
	};
};

}
}
}
}

#endif /*DEL_OWL_FUNC_PARSER_ANNOTATION_ASSERTION_HPP_*/
