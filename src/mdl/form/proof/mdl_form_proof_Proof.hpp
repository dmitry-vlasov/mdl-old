/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_Proof.hpp                                 */
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
namespace proof {

class Proof :
	public mdl :: Proof,
	public virtual form :: Identifiable,
	public Scalar<Proof> {
public :
	Proof();
	Proof
	(
		const Location&,
		const mdl :: Comments*,
		mdl :: proof :: Line*,
		const vector :: parser :: Step&,
		mdl :: Theory*
	);
	Proof
	(
		mdl :: proof :: Step*,
		index :: Step
	);
	// automatically generated proof stub
	Proof (const mdl :: Assertion*);

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
	class Timing;
	class Refiner;
	friend class Timing;
	friend class Refiner;
	friend class refactor :: redundant :: Steps;
	friend class refactor :: redundant :: Variables;

	enum {
		DEFAULT_STEP_VECTOR_CAPACITY = 8,
		DEFAULT_QED_VECTOR_CAPACITY = 1
	};

	void compressExact();
	void compressMass();

	void deriveExperience() const;
	void addLine (mdl :: proof :: Line*);
	void addVariableFirst (mdl :: proof :: Variable*);
	void replaceLine (mdl :: proof :: Line*, mdl :: proof :: Line*);
	void insertLine (mdl :: proof :: Line*, mdl :: proof :: Line*);
	mdl :: proof :: Line* removeLine (mdl :: proof :: Line*);

	void questionSelf();
	bool compressRest (mdl :: proof :: Line*, const Time timeLimit);
	void confirmCompression (mdl :: proof :: Line*);
	void rejectCompression (mdl :: proof :: Line*);
	void compressStep (mdl :: proof :: Line*, const Time timeLimit);

	static void writeMassCompressionLog (const mdl :: Assertion*);
	static void writeExactCompressionLog
	(
		const mdl :: Assertion*,
		const index :: Step,
		const index :: Step,
		const Timing&
	);
	static void writeProvingLog (const mdl :: Assertion*, const Timing&);

	mdl :: proof :: Line* firstLine_;
	mdl :: proof :: Line* lastLine_;
	vector :: proof :: Step stepVector_;
	vector :: proof :: Qed  qedVector_;
	mdl :: proof :: Scope* scope_;
	mdl :: proof :: Scope* scopeUp_;
	bool isVerified_;
	bool isCompressed_;

	static Proof* owner_;
};

}
}
}


