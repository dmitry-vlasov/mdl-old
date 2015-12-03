/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_block_Rule.hpp                                */
/* Description:     grammar rule parser                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_BLOCK_RULE_HPP_
#define MDL_PARSER_BLOCK_RULE_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/lexer/mdl_lexer.hpp"
#include "mdl/parser/mdl_parser.dpp"

namespace mdl {
namespace parser {
namespace block {

class Rule :
	public object :: Object,
	public Scalar<Rule> {
public :
	Rule();
	virtual ~ Rule();

	mdl :: Rule* parse (Lexer*, mdl :: Theory*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	// internal part
	parser :: header :: Variables* variablesParser_;
	parser :: header :: Line* lineParser_;

	// external part
	Location location_;
	mdl :: Comments* comments_;
	value :: Name name_;
	mdl :: Variables* variables_;
	mdl :: term :: Rule* term_;
};

}
}
}

#endif /*MDL_PARSER_BLOCK_RULE_HPP_*/
