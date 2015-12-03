/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_block_Axiom.hpp                               */
/* Description:     axiom parser                                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_BLOCK_AXIOM_HPP_
#define MDL_PARSER_BLOCK_AXIOM_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/lexer/mdl_lexer.hpp"
#include "mdl/parser/mdl_parser.dpp"
#include "mdl/parser/block/mdl_parser_block_Assertion.hpp"

namespace mdl {
namespace parser {
namespace block {

class Axiom :
	public Assertion<vector :: parser :: Axiomatic>,
	public Scalar<Axiom> {
public :
	Axiom();
	virtual ~ Axiom();

	mdl :: Assertion* parse (Lexer*, mdl :: Theory*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	typedef
		Assertion<vector :: parser :: Axiomatic>
		Ancestor_;
};

}
}
}

#endif /*MDL_PARSER_BLOCK_AXIOM_HPP_*/
