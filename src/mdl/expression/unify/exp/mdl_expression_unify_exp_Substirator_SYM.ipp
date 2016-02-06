/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_exp_Substirator_SYM.ipp             */
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

	template<class ST,  class TT>
	inline
	Substirator<ST, TT, policy :: SYMMETRIC> :: Substirator
	(
		const Source_& source,
		const Substitution_* const substitution
	) :
	Source_ (source),
	substitution_ (substitution) {
	}
	template<class ST,  class TT>
	inline
	Substirator<ST, TT, policy :: SYMMETRIC> :: Substirator (const Substirator& substirator) :
	Source_ (static_cast<const Source_&>(substirator)),
	substitution_ (substirator.substitution_) {
	}
	template<class ST,  class TT>
	inline
	Substirator<ST, TT, policy :: SYMMETRIC> :: Substirator () :
	Source_ (),
	substitution_ (NULL) {
	}

	template<class ST,  class TT>
	inline void
	Substirator<ST, TT, policy :: SYMMETRIC> :: operator = (const Source_& iterator) {
		Source_  :: operator = (iterator);
	}
	template<class ST,  class TT>
	inline void
	Substirator<ST, TT, policy :: SYMMETRIC> :: operator = (const Substirator& substirator) {
		Source_  :: operator = (substirator);
		substitution_ = substirator.substitution_;
	}

	template<class ST,  class TT>
	template<class A>
	inline void
	Substirator<ST, TT, policy :: SYMMETRIC> :: cloneSubstitution()
	{
		typedef A Allocator;
		if (substitution_ != NULL) {
			substitution_ = substitution_->template clone<Allocator>();
		}
	}

	template<class ST,  class TT>
	inline typename Substirator<ST, TT, policy :: SYMMETRIC> :: Substitution_*&
	Substirator<ST, TT, policy :: SYMMETRIC> :: substitution() {
		return const_cast<Substitution_*&>(substitution_);
	}
	template<class ST,  class TT>
	inline const typename Substirator<ST, TT, policy :: SYMMETRIC> :: Substitution_*
	Substirator<ST, TT, policy :: SYMMETRIC> :: getSubstitution() const {
		return substitution_;
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	template<class ST,  class TT>
	void
	Substirator<ST, TT, policy :: SYMMETRIC> :: show (String& string) const
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
	template<class ST,  class TT>
	void
	Substirator<ST, TT, policy :: SYMMETRIC> :: show () const
	{
		String string (1000);
		show (string);
		std :: cout << string << std :: endl;
	}
}
}
}
}


