/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_term_SubCplx.hpp                     */
/* Description:     substitution complexity evaluation function              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_EVALUATION_TERM_SUB_CPLX_HPP_
#define MDL_FORM_EVALUATION_TERM_SUB_CPLX_HPP_

namespace mdl {
namespace form {
namespace evaluation {
namespace term {

class SubCplx :
	public mdl :: evaluation :: Term,
	public Scalar<SubCplx> {
public :
	typedef
		mdl :: evaluation :: Term
		Term_;
	typedef
		Term_ :: HeapNode_
		HeapNode_;

	SubCplx ();
	SubCplx (const Location&, mdl :: Theory*);
	virtual ~ SubCplx();

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

#endif /*MDL_FORM_EVALUATION_TERM_SUB_CPLX_HPP_*/
