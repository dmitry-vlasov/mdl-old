/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File Name:       smm_source_Assertion.hpp                                 */
/* Description:     smm assertion                                            */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "smm/interface/smm_interface.hpp"
#include "smm/source/smm_source.dpp"

namespace smm {
namespace source {

class Assertion :
	public smm :: Assertion,
	public Scalar<Assertion> {
public :
	Assertion
	(
		const Location&,
		const vector :: Expression*,
		const vector :: Expression*,
		const vector :: Expression*,
		const vector :: Expression*,
		const vector :: Expression*,
		const Expression*,
		const smm :: Proof*
	);
	virtual ~ Assertion();

	// smm :: Assertion interface
	virtual const Expression* getDisjointed (const index :: Arity) const;
	virtual const Expression* getEssential (const index :: Arity) const;
	virtual const Expression* getFloating (const index :: Arity) const;
	virtual const Expression* getInner (const index :: Arity) const;

	virtual index :: Arity getDisjointedArity() const;
	virtual index :: Arity getEssentialArity() const;
	virtual index :: Arity getFloatingArity() const;
	virtual index :: Arity getInnerArity() const;

	virtual const Expression* getProposition() const;
	virtual const smm :: Proof* getProof() const;
	virtual bool areDisjointed (const value :: Literal, const value :: Literal) const;

	virtual index :: Assertion getIndex() const;
	virtual void showHeader (String&) const;
	virtual void showName (String&) const;

	// object :: Verifiable interface
	virtual void verify() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	void showBody (String&) const;
	void checkCorrectness();
	void checkVariablesCorrectness() const;
	bool isVariable (const value :: Literal) const;
	void checkDisjointedCorrectness() const;
	void checkFloatingCorrectness() const;
	void checkInnerCorrectness() const;
	void checkExpressionCorrectness (const Expression*) const;
	void checkVectorCorrectness (const vector :: Expression*) const;

	const Location location_;
	const vector :: Expression* variablesVector_;
	const vector :: Expression* disjointedVector_;
	const vector :: Expression* essentialVector_;
	const vector :: Expression* floatingVector_;
	const vector :: Expression* innerVector_;
	const Expression* proposition_;
	const smm :: Proof* proof_;
	const index :: Assertion index_;
};

}
}


