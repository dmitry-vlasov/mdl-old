/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_block_Proof.hpp                               */
/* Description:     proof parser                                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_BLOCK_PROOF_HPP_
#define MDL_PARSER_BLOCK_PROOF_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/lexer/mdl_lexer.hpp"
#include "mdl/parser/mdl_parser.dpp"

namespace mdl {
namespace parser {
namespace block {

class Proof :
	public object :: Object,
	public Scalar<Proof> {
public :
	Proof (const bool local = false);
	virtual ~ Proof();

	mdl :: Proof* parse (Lexer*, mdl :: Theory*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	//mdl :: proof :: Line* parseLine (Lexer*, const bool = true);

	// internal part
	const bool local_;
	parser :: Identificator*  identificatorParser_;
	parser :: proof :: Proof* proofParser_;

	// external part
	Location location_;
	mdl :: Comments* comments_;
	value :: Name name_;
	mdl :: Identificator* theorem_;
	form :: proof :: Proof* proof_;
};

}
}
}

#endif /*MDL_PARSER_BLOCK_PROOF_HPP_*/
