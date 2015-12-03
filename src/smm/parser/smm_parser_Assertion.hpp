/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_parser_Assertion.hpp                                 */
/* Description:     smm assertion parser                                     */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_PARSER_ASSERTION_HPP_
#define SMM_PARSER_ASSERTION_HPP_

#include "smm/interface/smm_interface.hpp"
#include "smm/parser/smm_parser_Line.hpp"
#include "smm/lexer/smm_lexer.hpp"

namespace smm {
namespace parser {

class Assertion :
	public object :: Object,
	public Scalar<Assertion> {
public :
	Assertion();
	virtual ~ Assertion();

	const smm :: Assertion* parse (Lexer* const);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	void createComponents();
	const smm :: Assertion* createResult ();

	Location location_;

	typedef
		Line<Token :: VARIABLE, false>
		VariablesParser_;
	typedef
		Line<Token :: DISJOINTED, false>
		DisjointedParser_;
	typedef
		Line<Token :: ESSENTIAL>
		EssentialParser_;
	typedef
		Line<Token :: FLOATING>
		FloatingParser_;
	typedef
		Line<Token :: FLOATING>
		InnerParser_;
	typedef
		Line<Token :: AXIOMATIC, true, false>
		AxiomaticParser_;
	typedef
		Line<Token :: PROVABLE, true, false, Token :: EQUALITY>
		ProvableParser_;

	// internal part
	VariablesParser_ variablesParser_;
	DisjointedParser_ disjointedParser_;
	EssentialParser_ essentialParser_;
	FloatingParser_ floatingParser_;
	InnerParser_ innerParser_;
	AxiomaticParser_ axiomaticParser_;
	ProvableParser_ provableParser_;
	parser :: Proof* proofParser_;

	// external part
	vector :: Expression* variablesVector_;
	vector :: Expression* disjointedVector_;
	vector :: Expression* essentialVector_;
	vector :: Expression* floatingVector_;
	vector :: Expression* innerVector_;
	const smm :: Expression* proposition_;
	const smm :: Proof* proof_;

	//counters
	index :: Arity essentialCounter_;
	index :: Arity floatingCounter_;
	index :: Arity innerCounter_;
	static index :: Assertion propositionCounter_;
};

}
}

#endif /*SMM_PARSER_ASSERTION_HPP_*/
