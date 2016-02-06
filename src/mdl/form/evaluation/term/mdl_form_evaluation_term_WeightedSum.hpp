/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_term_WeightedSum.hpp                 */
/* Description:     weighted sum evaluation function for proposition         */
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

class WeightedSum :
	public mdl :: evaluation :: Term,
	public Scalar<WeightedSum> {
public :
	typedef
		mdl :: evaluation :: Term
		Term_;
	typedef
		Term_ :: HeapNode_
		HeapNode_;

	WeightedSum
	(
		const index :: Arity dimension,
		const value :: Real weights[],
		Term_* terms[]
	);
	WeightedSum
	(
		const Location&,
		const vector :: value :: Real&,
		const mdl :: evaluation :: parser :: vector :: Term&,
		mdl :: Theory* theory
	);
	virtual ~ WeightedSum();

	vector :: value :: Real& weightVector();
	void addTerm (Term_*);

	// evaluation :: Term interface
	virtual index :: Arity getArity() const;
	virtual value :: Real eval (const HeapNode_*) const;
	virtual value :: Real eval (const value :: Real [] = NULL) const;
	virtual Term_* getSubTerm (const index :: Arity);
	virtual const Term_* getSubTerm (const index :: Arity) const;

	// object :: Buildable interface
	virtual void build();

	// object :: Writable interface
	virtual void replicate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	const Location location_;
	vector :: value :: Real weightVector_;
	mdl :: evaluation :: vector :: Term termVector_;
};

}
}
}
}


