/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_term_Barrier.hpp                     */
/* Description:     barrier function                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_EVALUATION_TERM_BARRIER_HPP_
#define MDL_FORM_EVALUATION_TERM_BARRIER_HPP_

namespace mdl {
namespace form {
namespace evaluation {
namespace term {

class Barrier :
	public mdl :: evaluation :: Term,
	public Scalar<Barrier> {
public :
	typedef
		mdl :: evaluation :: Term
		Term_;
	typedef
		Term_ :: HeapNode_
		HeapNode_;

	Barrier (Term_*, Term_*, Term_*);
	Barrier
	(
		const Location& location,
		const vector :: value :: Real& parameters,
		const mdl :: evaluation :: parser :: vector :: Term& termVector,
		mdl :: Theory*
	);
	virtual ~ Barrier();

	// evaluation :: Term interface
	virtual index :: Arity getArity() const;
	virtual value :: Real eval (const HeapNode_*) const;
	virtual value :: Real eval (const value :: Real values[]) const;
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
	mdl :: evaluation :: Term* termA_;
	mdl :: evaluation :: Term* termB_;
	mdl :: evaluation :: Term* termX_;
};

}
}
}
}

#endif /*MDL_FORM_EVALUATION_TERM_BARRIER_HPP_*/
