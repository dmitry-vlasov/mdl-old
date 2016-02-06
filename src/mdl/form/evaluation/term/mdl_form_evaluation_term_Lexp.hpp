/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_term_Lexp.hpp                        */
/* Description:     FRiS evaluation function                                 */
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

class Lexp :
	public mdl :: evaluation :: Term,
	public Scalar<Lexp> {
public :
	typedef
		lexp :: Fris<allocator :: Heap>
		Fris_;
	typedef
		mdl :: evaluation :: Term
		Term_;
	typedef
		Term_ :: HeapNode_
		HeapNode_;

	Lexp ();
	Lexp (const bool);
	Lexp (const Location&, mdl :: Theory*);
	virtual ~ Lexp();

	void addCase (mdl :: evaluation :: Case*);
	void setConst (const bool);
	void setFris (Fris_*);

	// evaluation :: Term interface
	virtual value :: Real eval (const HeapNode_*) const;

	// object :: Buildable interface
	virtual void build();

	// object :: Writable interface
	virtual void replicate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	void clearCaseVector();
	void initCaseVector();

	enum {
		INITIAL_CASE_VECTOR_CAPACITY = 32
	};

	const Location location_;
	mdl :: Theory* theory_;
	mdl :: evaluation :: vector :: Case caseVector_;
	mutable Fris_* fris_;
};

}
}
}
}


