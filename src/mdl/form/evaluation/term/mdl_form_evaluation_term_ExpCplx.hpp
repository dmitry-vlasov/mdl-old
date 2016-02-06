/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_term_ExpCplx.hpp                     */
/* Description:     expression complexity evaluation function                */
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

class ExpCplx :
	public mdl :: evaluation :: Term,
	public Scalar<ExpCplx> {
public :
	typedef
		mdl :: evaluation :: Term
		Term_;
	typedef
		Term_ :: HeapNode_
		HeapNode_;

	ExpCplx ();
	ExpCplx (const Location&, mdl :: Theory*);
	virtual ~ ExpCplx();

	// evaluation :: Term interface
	virtual value :: Real eval (const HeapNode_*) const;

	// object :: Writable interface
	virtual void replicate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	const Location location_;
};

}
}
}
}


