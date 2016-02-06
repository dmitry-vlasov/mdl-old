/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_block_Proof.hpp                                 */
/* Description:     proof class                                              */
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
namespace block {

class Proof :
	public mdl :: Proof,
	public Identifiable,
	public Scalar<Proof> {
public :
	Proof
	(
		const Location&,
		const mdl :: Comments* ,
		value :: Name name,
		mdl :: Identificator* id,
		proof :: Proof* proof,
		mdl :: Theory* theory
	);
	Proof (mdl :: Assertion*);
	virtual ~ Proof();

	void verifyStructure() const;

	// mdl :: Proof interface
	virtual bool isCompressed() const;
	virtual index :: Step  getLength() const;
	virtual index :: Arity getQedArity() const;

	virtual void addStep (mdl :: proof :: Step*);
	virtual void addVariable (mdl :: proof :: Variable*);
	virtual void addQed (mdl :: proof :: Qed*);

	virtual mdl :: proof :: Step* getStep (const index :: Step);
	virtual mdl :: proof :: Qed*  getQed (const index :: Arity);
	virtual mdl :: proof :: Line* getFirst();
	virtual mdl :: proof :: Line* getLast();
	virtual const mdl :: proof :: Step* getStep (const index :: Step) const;
	virtual const mdl :: proof :: Qed*  getQed (const index :: Arity) const;
	virtual const mdl :: proof :: Line* getFirst() const;
	virtual const mdl :: proof :: Line* getLast() const;

	// object :: Scoping interface
	virtual mdl :: proof :: Scope* buildScope (mdl :: proof :: Scope*);
	virtual void setScope (mdl :: proof :: Scope*);
	virtual mdl :: proof :: Scope* getScope();
	virtual const mdl :: proof :: Scope* getScope() const;

	// object :: Identifiable interface
	virtual const Location& getLocation() const;
	virtual value :: Name getName() const;

	virtual void translateName (String&, const index :: Arity = 0) const;
	virtual void replicateName (String&) const;

	virtual mdl :: Theory* getTheory();
	virtual mdl :: Identificator* getIdentificator();
	virtual const mdl :: Theory* getTheory() const;
	virtual const mdl :: Identificator* getIdentificator() const;

	// object :: Verifiable interface
	virtual void check();
	virtual void compress();
	virtual void reprove();
	virtual void prove();
	virtual bool isVerified() const;
	virtual void mine (String&) const;

	// object :: Buildable interface
	virtual void build();

	// object :: Writable interface
	virtual void translate (String& string) const;
	virtual void replicate (String& string) const;
	virtual bool lookup() const;
	virtual object :: Writable* find();
	virtual const object :: Writable* find() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getSizeOf() const;
	virtual Size_t getVolume() const;

private :
	friend class refactor :: redundant :: Steps;
	friend class refactor :: redundant :: Variables;

	value :: Integer getTheoryDepth() const;

	mdl :: Identificator* theoremId_;
	mdl :: Theory* theory_;
	mdl :: Assertion* theorem_;

	proof :: Proof* proof_;
	mdl :: proof :: Scope* scope_;
};

}
}
}


