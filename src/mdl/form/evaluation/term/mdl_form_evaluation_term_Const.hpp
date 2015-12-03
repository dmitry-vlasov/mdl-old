/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_term_Const.hpp                       */
/* Description:     constant evaluation function                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_EVALUATION_TERM_CONST_HPP_
#define MDL_FORM_EVALUATION_TERM_CONST_HPP_

namespace mdl {
namespace form {
namespace evaluation {
namespace term {

class Const :
	public mdl :: evaluation :: Term,
	public Scalar<Const> {
public :
	typedef
		mdl :: evaluation :: Term
		Term_;
	typedef
		Term_ :: HeapNode_
		HeapNode_;

	Const (const value :: Real);
	Const
	(
		const Location&,
		const value :: Real,
		mdl :: Theory*
	);
	virtual ~ Const();

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
	const value :: Real constant_;
};

}
}
}
}

#endif /*MDL_FORM_EVALUATION_TERM_CONST_HPP_*/
