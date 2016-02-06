/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File Name:       smm_source_Proof.hpp                                     */
/* Description:     smm proof                                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "smm/interface/smm_interface.hpp"
#include "smm/source/smm_source_Reference.hpp"

namespace smm {
namespace source {

class Proof :
	public smm :: Proof,
	public Scalar<Proof> {
public :
	Proof (const Location&, const vector :: Reference*);
	virtual ~ Proof();

	// source :: Proof interface
	virtual void setTheorem (const smm :: Assertion* const);

	// object :: Verifiable interface
	virtual void verify() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	void initStatic() const;
	void showStack (Error*) const;
	void showStack (String&) const;

	void verifyStep (const Reference&) const;
	void apply (const smm :: Assertion*) const;
	void applyFloating (const smm :: Assertion*) const;
	void applyEssential (const smm :: Assertion*) const;

	const Location location_;
	const smm :: Assertion* theorem_;
	const vector :: Reference* referenceVector_;

	static stack :: Expression* stack_;
	static Substitution* substitution_;
	enum {
		INITIAL_STACK_CAPACITY = 1024,
		INITIAL_SUBSTITUTION_CAPACITY = 64
	};
	friend class auxiliary :: Volume;
};

}
}


