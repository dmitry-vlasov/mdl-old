/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_evaluation_Term.hpp                           */
/* Description:     evaluation term parser                                   */
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
namespace evaluation {

class Term :
	public object :: Object,
	public Scalar<Term> {
public :
	Term();
	virtual ~ Term();

	mdl :: evaluation :: Term* parse (Lexer*, mdl :: Theory*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	enum {
		INITIAL_NAME_CAPACITY = 32,
		INITIAL_PARAMETER_VECTOR_CAPACITY = 8,
		INITIAL_TERM_VECTOR_CAPACITY = 8
	};

	mdl :: evaluation :: Term* parseSimpleOperation (const Token :: Type, Lexer*, mdl :: Theory*);
	mdl :: evaluation :: Term* parseComplexOperation (const Token :: Type, Lexer*, mdl :: Theory*);
	mdl :: evaluation :: Term* parseLexpOperation (const Token :: Type, Lexer*, mdl :: Theory*);
	mdl :: evaluation :: Term* parseConstOperation (const Token :: Type, Lexer*, mdl :: Theory*);

	// internal part
	parser :: evaluation :: Term* termParser_;
	parser :: evaluation :: Case* caseParser_;

	// external part
	Location location_;
	value :: Real parameter_;
	vector :: value :: Real parameterVector_;
	mdl :: evaluation :: parser :: vector :: Term subtermVector_;
};

}
}
}


