/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_evaluation_Function.hpp                       */
/* Description:     evaluation function for proposition parser               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_EVALUATION_FUNCTION_HPP_
#define MDL_PARSER_EVALUATION_FUNCTION_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/lexer/mdl_lexer.hpp"
#include "mdl/parser/mdl_parser.dpp"

namespace mdl {
namespace parser {
namespace evaluation {

class Function :
	public object :: Object,
	public Scalar<Function> {
public :
	Function();
	virtual ~ Function();

	mdl :: evaluation :: Function* parse (Lexer*, mdl :: Theory*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	// internal part
	parser :: evaluation :: Term* termParser_;

	// external part
	Location location_;
	index :: Arity index_;
	mdl :: evaluation :: Term* term_;
};

}
}
}

#endif /*MDL_PARSER_EVALUATION_FUNCTION_HPP_*/
