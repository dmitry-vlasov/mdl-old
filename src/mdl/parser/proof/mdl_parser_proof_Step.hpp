/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_proof_Step.hpp                                */
/* Description:     proof step parser                                        */
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

class Step :
	public object :: Object,
	public Scalar<Step> {
public :
	Step();
	virtual ~ Step();

	mdl :: proof :: Step* parse
	(
		Lexer*,
		mdl :: Theory*,
		mdl :: proof :: Line*
	);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	mdl :: proof :: Step* parseAssertion
	(
		Lexer*,
		mdl :: Theory*,
		mdl :: proof :: Line*,
		const bool
	);
	mdl :: proof :: Step* parseClaim
	(
		Lexer*,
		mdl :: Theory*,
		mdl :: proof :: Line*,
		const bool
	);
	mdl :: proof :: Step* parseQuestion
	(
		Lexer*,
		mdl :: Theory*,
		mdl :: proof :: Line*,
		const bool
	);

	// internal part
	parser :: Identificator* identificatorParser_;
	parser :: proof :: Link* linkParser_;
	parser :: Expression* expressionParser_;
	parser :: Proof* proofParser_;

	// external part
	Location location_;
	mdl :: Comments* comments_;
	index :: Step index_;
	mdl :: Identificator* type_;
	mdl :: proof :: Link* link_;
	array :: Expression* expression_;
	mdl :: Proof* proof_;
};

}
}
}


