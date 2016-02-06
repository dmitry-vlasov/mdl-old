/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_proof_Link.hpp                                */
/* Description:     proof link parser                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/lexer/mdl_lexer.hpp"
#include "mdl/parser/mdl_parser.dpp"

namespace mdl {
namespace parser {
namespace proof {

class Link :
	public object :: Object,
	public Scalar<Link> {
public :
	Link();
	virtual ~ Link();

	mdl :: proof :: Link* parse (Lexer*, mdl :: Theory*, const bool = true);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	// internal part
	Location location_;
	parser :: Identificator* identificatorParser_;
	parser :: proof :: References* referencesParser_;

	// external part
	Token :: Type kind_;
	mdl :: Identificator* inference_;
	index :: Arity proposition_;
	mdl :: proof :: References* references_;
};

}
}
}


