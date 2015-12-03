/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_exp_Substirator_DIR.hpp             */
/* Description:     directed substituting iterator                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_UNIFY_EXP_SUBSTIRATOR_DIR_HPP_
#define MDL_EXPRESSION_UNIFY_EXP_SUBSTIRATOR_DIR_HPP_

namespace mdl {
namespace expression {
namespace unify {
namespace exp {

template<class ST, class TT, int P>
class Substirator : public ST :: const_Iterator_ {
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
		typename TargetTerm_ :: Substitution_
		Substitution_;

	Substirator (const Source_&, const Substitution_* const = NULL);
	Substirator (const Substirator&);
	Substirator ();

	void operator = (const Source_&);
	void operator = (const Substirator&);

	template<class A>
	void cloneSubstitution();

	Target_ follow (const Target_, bool&) const;

	Substitution_*& substitution();
	const Substitution_* getSubstitution() const;
	const Substitution_* newSubstitution (const TargetTerm_*);

	void show (String&) const;
	void show () const;

private :
	const Substitution_* substitution_;
};

}
}
}
}

#endif /*MDL_EXPRESSION_UNIFY_EXP_SUBSTIRATOR_DIR_HPP_*/
