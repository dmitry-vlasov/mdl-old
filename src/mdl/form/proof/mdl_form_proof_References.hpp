/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_References.hpp                            */
/* Description:     vector of references to the proof nodes                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"

namespace mdl {
namespace form {
namespace proof {

class References :
	public mdl :: proof :: References,
	public Scalar<References> {
private :
	enum { INITIAL_REFERENCES_CAPACITY = 8 };
public :
	References (const index :: Arity = INITIAL_REFERENCES_CAPACITY);
	References
	(
		const vector :: parser :: Reference&,
		mdl :: Theory*
	);
	virtual ~ References();

	// proof :: References interface
	virtual void build (mdl :: proof :: Scope*);
	virtual void add (mdl :: proof :: Reference*);
	virtual index :: Arity find (const mdl :: proof :: Node*) const;
	virtual index :: Arity getArity() const;
	virtual mdl :: proof :: Reference* get (const index :: Arity);
	virtual const mdl :: proof :: Reference* get (const index :: Arity) const;

	// object :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;
	virtual bool lookup() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	friend class refactor :: redundant :: Hypotheses;
	friend class refactor :: redundant :: Steps;

	vector :: proof :: Reference referenceVector_;
};

}
}
}


