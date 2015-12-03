/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_Bush.ipp                                  */
/* Description:     bush expression set class                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_BUSH_IPP_
#define MDL_EXPRESSION_BUSH_IPP_

namespace mdl {
namespace expression {

	/****************************
	 *		Public members
	 ****************************/

	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline
	Bush<V, H, S, A> :: Bush () :
	Ancestor_ (),
	isAccessible_ (false) {
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline
	Bush<V, H, S, A> :: ~ Bush() {
	}

	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	template<class E>
	inline typename Bush<V, H, S, A> :: Iterator_
	Bush<V, H, S, A> :: addBranch
	(
		const E* const expression,
		const Value_ value,
		const bool isAccessible
	)
	{
		isAccessible_ = isAccessible;
		return Ancestor_ :: addBranch (expression, value);
	}

	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline void
	Bush<V, H, S, A> :: copyNode (Iterator_& target, const Iterator_& source) const
	{
		Ancestor_ :: copyNode (target, source);
		target->setAccessible (source->isAccessible());
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	template<class I>
	inline void
	Bush<V, H, S, A> :: copyNode (Iterator_& target, const I& source) const
	{
		Ancestor_ :: copyNode (target, source);
		target->setAccessible (true);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	template<class I>
	inline bool
	Bush<V, H, S, A> :: findNode (Iterator_& target, const I& source) const {
		return Ancestor_ :: findNode (target, source);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	template<class I>
	inline void
	Bush<V, H, S, A> :: addFindNode (Iterator_& target, const I& source) const
	{
		Ancestor_ :: addFindNode (target, source);
		if (!target->isAccessible()) {
			target->setAccessible (isAccessible_);
		}
	}

using manipulator :: endLine;

	// object :: Object interface
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	void
	Bush<V, H, S, A> :: commitSuicide() {
		delete this;
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	Size_t
	Bush<V, H, S, A> :: getVolume() const {
		return Ancestor_ :: getVolume();
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	Size_t
	Bush<V, H, S, A> :: getSizeOf() const {
		return sizeof (Bush);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	void
	Bush<V, H, S, A> :: show (String& string) const
	{
		string << "bush:" << endLine;
		if (Ancestor_ :: root_ != NULL) {
			Ancestor_ :: root_->showBush (string);
		} else {
			string << tab << "NULL" << endLine;
		}
		string << endLine;
	}
}
}

#endif /*MDL_EXPRESSION_BUSH_HPP_*/
