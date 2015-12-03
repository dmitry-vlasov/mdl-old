/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_header_Variable.hpp                           */
/* Description:     variable declaration parser                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_HEADER_VARIABLE_HPP_
#define MDL_PARSER_HEADER_VARIABLE_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/lexer/mdl_lexer.hpp"
#include "mdl/parser/mdl_parser.dpp"

namespace mdl {
namespace parser {
namespace header {

class Variable :
	public object :: Object,
	public Scalar<Variable> {
public :
	Variable();
	virtual ~ Variable();

	template<class I>
	 mdl :: header :: Variable* parse (Lexer*, mdl :: Theory*, const bool = true);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	// internal part
	Location location_;
	parser :: Identificator* identificatorParser_;

	// external part
	value :: Literal literal_;
	mdl :: Identificator* type_;
};

}
}
}

#endif /*MDL_PARSER_HEADER_VARIABLES_HPP_*/