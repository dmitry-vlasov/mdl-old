/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_term_Case.hpp                        */
/* Description:     elementary case of proposition usage                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace form {
namespace evaluation {
namespace term {

class Case :
	public mdl :: evaluation :: Case,
	public Scalar<Case, allocator :: Heap> {
public :
	Case
	(
		mdl :: proof :: Step*,
		bool sign
	);
	Case
	(
		const Location&,
		bool sign,
		mdl :: Identificator* id,
		value :: Name name,
		const vector :: value :: Integer& path,
		mdl :: Theory* theory
	);
	virtual ~ Case();

	// evaluation :: Case interface
	virtual bool getSign() const;
	virtual mdl :: proof :: Step* getStep();
	virtual const mdl :: proof :: Step* getStep() const;

	// object :: Buildable interface
	virtual void build();

	// object :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	enum {
		INITIAL_PATH_CAPACITY = 8
	};

	void findProof();
	void findStep();
	void initPath (const mdl :: proof :: Step*);

	const Location location_;
	mdl :: Theory* theory_;
	bool sign_;
	mdl :: Identificator* id_;
	value :: Name         name_;
	vector :: value :: Integer  path_;

	mdl :: Proof* proof_;
	mdl :: proof :: Step* step_;
};

}
}
}
}


