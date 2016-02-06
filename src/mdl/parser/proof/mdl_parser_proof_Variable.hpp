/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_proof_Variable.hpp                            */
/* Description:     proof variable declaration parser                        */
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

class Variable :
	public object :: Object,
	public Scalar<Variable> {
public :
	Variable();
	virtual ~ Variable();

	mdl :: proof :: Variable* parse
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
	// internal part
	parser :: header :: Variable* variableParser_;

	// external part
	Location location_;
	mdl :: Comments* comments_;
	mdl :: header :: Variable* variable_;
};

}
}
}


