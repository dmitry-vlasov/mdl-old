/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_block_Definition.hpp                          */
/* Description:     definition parser                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_BLOCK_DEFINITION_HPP_
#define MDL_PARSER_BLOCK_DEFINITION_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/lexer/mdl_lexer.hpp"
#include "mdl/parser/mdl_parser.dpp"

namespace mdl {
namespace parser {
namespace block {

class Definition :
	public Assertion<vector :: parser :: Definition>,
	public Scalar<Definition> {
public :
	Definition();
	virtual ~ Definition();

	mdl :: Definition* parse (Lexer*, mdl :: Theory*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	typedef
		Assertion<vector :: parser :: Definition>
		Ancestor_;

	// internal part
	parser :: header :: Line* lineParser_;

	// external part
	mdl :: term :: Definition* defiendum_;
	mdl :: term :: Definition* definiens_;
};

}
}
}

#endif /*MDL_PARSER_BLOCK_DEFINITION_HPP_*/
