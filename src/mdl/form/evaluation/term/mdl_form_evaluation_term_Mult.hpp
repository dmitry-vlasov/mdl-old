/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_term_Mult.hpp                        */
/* Description:     multiplication evaluation function                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_EVALUATION_TERM_MULT_HPP_
#define MDL_FORM_EVALUATION_TERM_MULT_HPP_

namespace mdl {
namespace form {
namespace evaluation {
namespace term {

class Mult :
	public mdl :: evaluation :: Term,
	public Scalar<Mult> {
public :
	typedef
		mdl :: evaluation :: Term
		Term_;
	typedef
		Term_ :: HeapNode_
		HeapNode_;

	Mult (const value :: Real);
	Mult (Term_*, const value :: Real = 1);
	Mult (Term_*, Term_*, const value :: Real = 1);
	Mult
	(
		const Location&,
		const value :: Real,
		const mdl :: evaluation :: parser :: vector :: Term&,
		mdl :: Theory*
	);
	virtual ~ Mult();

	void addTerm (Term_*);

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
	enum {
		INITIAL_TERM_VECTOR_CAPACITY = 1
	};
	const Location location_;
	const value :: Real constant_;
	mdl :: evaluation :: vector :: Term termVector_;
};

}
}
}
}

#endif /*MDL_FORM_EVALUATION_TERM_MULT_HPP_*/
