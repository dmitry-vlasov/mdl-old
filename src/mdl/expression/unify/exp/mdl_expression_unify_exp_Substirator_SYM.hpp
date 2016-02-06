/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_exp_Substirator_SYM.hpp             */
/* Description:     symmetric substituting iterator                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace expression {
namespace unify {
namespace exp {

template<class ST, class TT>
class Substirator<ST, TT, policy :: SYMMETRIC> : public ST :: const_Iterator_ {
public :
	typedef ST SourceTerm_;
	typedef TT TargetTerm_;
	typedef
		typename SourceTerm_ :: const_Iterator_
		Source_;
	typedef
		typename TargetTerm_ :: const_Iterator_
		Target_;
	typedef
		List<allocator :: Stack>
		List_;
	typedef
		typename List_ :: Term_
		ListTerm_;
	typedef
		typename ListTerm_ :: Substitution_
		Substitution_;

	Substirator (const Source_&, const Substitution_* const = NULL);
	Substirator (const Substirator&);
	Substirator ();

	void operator = (const Source_&);
	void operator = (const Substirator&);

	template<class A>
	void cloneSubstitution();

	Substitution_*& substitution();
	const Substitution_* getSubstitution() const;

	void show (String&) const;
	void show () const;

private :
	const Substitution_* substitution_;
};

}
}
}
}


