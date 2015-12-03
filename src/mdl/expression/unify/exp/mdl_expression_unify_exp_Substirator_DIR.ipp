/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_exp_Substirator_DIR.ipp             */
/* Description:     directed substituting iterator                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_UNIFY_EXP_SUBSTIRATOR_DIR_IPP_
#define MDL_EXPRESSION_UNIFY_EXP_SUBSTIRATOR_DIR_IPP_

namespace mdl {
namespace expression {
namespace unify {
namespace exp {

	template<class ST,  class TT, int P>
	inline
	Substirator<ST, TT, P> :: Substirator
	(
		const Source_& source,
		const Substitution_* const substitution
	) :
	Source_ (source),
	substitution_ (substitution) {
	}
	template<class ST,  class TT, int P>
	inline
	Substirator<ST, TT, P> :: Substirator (const Substirator& substirator) :
	Source_ (static_cast<const Source_&>(substirator)),
	substitution_ (substirator.substitution_) {
	}
	template<class ST,  class TT, int P>
	inline
	Substirator<ST, TT, P> :: Substirator () :
	Source_ (),
	substitution_ (NULL) {
	}

	template<class ST,  class TT, int P>
	inline void
	Substirator<ST, TT, P> :: operator = (const Source_& iterator) {
		Source_  :: operator = (iterator);
	}
	template<class ST,  class TT, int P>
	inline void
	Substirator<ST, TT, P> :: operator = (const Substirator& substirator) {
		Source_  :: operator = (substirator);
		substitution_ = substirator.substitution_;
	}

	template<class ST,  class TT, int P>
	template<class A>
	inline void
	Substirator<ST, TT, P> :: cloneSubstitution()
	{
		typedef A Allocator;
		if (substitution_ != NULL) {
			substitution_ = substitution_->template clone<Allocator>();
		}
	}

	template<class ST,  class TT, int P>
	inline typename Substirator<ST, TT, P> :: Target_
	Substirator<ST, TT, P> :: follow (const Target_ iterator, bool& substituted) const
	{
		if (substitution_ == NULL) {
			substituted = false;
			return iterator;
		}
		const Symbol&
			variable = **this;
		const Substitution_*
			substitution = substitution_->find (variable);
		if (substitution == NULL) {
			substituted = false;
			return iterator;
		}
		substituted = true;
		return substitution->follow(iterator);
	}
	template<class ST,  class TT, int P>
	inline typename Substirator<ST, TT, P> :: Substitution_*&
	Substirator<ST, TT, P> :: substitution() {
		return const_cast<Substitution_*&>(substitution_);
	}
	template<class ST,  class TT, int P>
	inline const typename Substirator<ST, TT, P> :: Substitution_*
	Substirator<ST, TT, P> :: getSubstitution() const {
		return substitution_;
	}
	template<class ST, class TT, int P>
	inline const typename Substirator<ST, TT, P> :: Substitution_*
	Substirator<ST, TT, P> :: newSubstitution (const TargetTerm_* const term)
	{
		const Symbol&
			variable = **this;
		substitution_ = Substitution_ :: template create<allocator :: Stack> (variable, term);
		return substitution_;
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	template<class ST,  class TT, int P>
	void
	Substirator<ST, TT, P> :: show (String& string) const
	{
		string << "symbol: ";
		(*this)->show (string);
		string << endLine;
		string << "substitution: " << endLine;
		if (substitution_ !=  NULL) {
			string << tab;
			substitution_->show (string);
			string << endLine;
		} else {
			string << tab << "NULL" << endLine;
		}
	}
	template<class ST,  class TT, int P>
	void
	Substirator<ST, TT, P> :: show () const
	{
		String string (1000);
		show (string);
		std :: cout << string << std :: endl;
	}
}
}
}
}

#endif /*MDL_EXPRESSION_UNIFY_EXP_SUBSTIRATOR_DIR_IPP_*/
