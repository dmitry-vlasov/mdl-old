/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_proof_Proof.hpp                               */
/* Description:     proof parser                                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_PROOF_PROOF_HPP_
#define MDL_PARSER_PROOF_PROOF_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/lexer/mdl_lexer.hpp"
#include "mdl/parser/mdl_parser.dpp"

namespace mdl {
namespace parser {
namespace proof {

class Proof :
	public object :: Object,
	public Scalar<Proof> {
public :
	Proof();
	virtual ~ Proof();

	form :: proof :: Proof* parse (Lexer*, mdl :: Theory*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	mdl :: proof :: Line* parseLine (Lexer*, mdl :: Theory*, const bool = true);

	// internal part
	parser :: proof :: Step* stepParser_;
	parser :: proof :: Qed* qedParser_;
	parser :: proof :: Variable* variableParser_;
	parser :: proof :: Notation* notationParser_;

	// external part
	Location location_;
	mdl :: Comments* comments_;
	vector :: parser :: Step stepVector_;
	mdl :: proof :: Line* firstLine_;
	mdl :: proof :: Line* line_;
	enum {
		INITIAL_STEP_VECTOR_CAPACITY = 1024 * 4
	};
};

}
}
}

#endif /*MDL_PARSER_PROOF_PROOF_HPP_*/
