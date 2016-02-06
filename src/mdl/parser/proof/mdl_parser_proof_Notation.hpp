/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_proof_Notation.hpp                            */
/* Description:     proof notation parser                                    */
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

class Notation :
	public object :: Object,
	public Scalar<Notation> {
public :
	Notation();
	virtual ~ Notation();

	mdl :: proof :: Notation* parse
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
	parser :: header :: Variables* variablesParser_;
	parser :: header :: Line* lineParser_;

	// external part
	Location location_;
	value :: Literal literal_;
	mdl :: Variables* variables_;
	mdl :: proof :: Term* abbreviation_;
	mdl :: proof :: Term* meaning_;
};

}
}
}


