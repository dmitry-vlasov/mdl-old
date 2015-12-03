/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_Contents.hpp                                  */
/* Description:     theory contents parser                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_CONTENTS_HPP_
#define MDL_PARSER_CONTENTS_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/lexer/mdl_lexer.hpp"
#include "mdl/parser/mdl_parser.dpp"

namespace mdl {
namespace parser {

class Contents :
	public object :: Object,
	public Scalar<Contents> {
public :
	Contents();
	virtual ~ Contents();

	mdl :: Contents* parse (Lexer*, mdl :: Theory*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	// internal part
	parser :: Constant* constantParser_;
	parser :: Type* typeParser_;
	parser :: Rule* ruleParser_;
	parser :: Axiom* axiomParser_;
	parser :: Definition* definitionParser_;
	parser :: Theorem* theoremParser_;
	parser :: Proof* proofParser_;
	parser :: Problem* problemParser_;
	parser :: Theory* theoryParser_;
	parser :: Evaluation* evaluationParser_;
	parser :: Contents* contentsParser_;

	// external part
	Location location_;
	mdl :: Comments* comments_;
	value :: Name name_;
	form :: Contents* contents_;
	mdl :: Theory* downTheory_;
};

}
}

#endif /*MDL_PARSER_CONTENTS_HPP_*/
