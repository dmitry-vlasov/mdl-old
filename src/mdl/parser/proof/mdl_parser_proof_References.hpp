/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_proof_References.hpp                          */
/* Description:     proof reference vector parser                            */
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

class References :
	public object :: Object,
	public Scalar<References> {
public :
	References();
	virtual ~ References();

	mdl :: proof :: References* parse (Lexer*, mdl :: Theory*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	// internal part
	parser :: proof :: Reference* referenceParser_;

	// external part
	vector :: parser :: Reference referenceVector_;
	enum {
		INITIAL_REFERENCE_VECTOR_CAPACITY = 8
	};
};

}
}
}


