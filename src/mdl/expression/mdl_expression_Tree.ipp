/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_Tree.ipp                                  */
/* Description:     tree expression set class                                */
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
	Tree<V, H, S, A> :: Tree () :
	Ancestor_ () {
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline
	Tree<V, H, S, A> :: ~ Tree() {
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
	Tree<V, H, S, A> :: copyNode (typename Ancestor_ :: Iterator_& target, const I& source) const {
		Ancestor_ :: copyNode (target, source);
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
	Tree<V, H, S, A> :: findNode (typename Ancestor_ :: Iterator_& target, const I& source) const {
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
	Tree<V, H, S, A> :: addFindNode (typename Ancestor_ :: Iterator_& target, const I& source) const {
		Ancestor_ :: addFindNode (target, source);
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
	Tree<V, H, S, A> :: commitSuicide() {
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
	Tree<V, H, S, A> :: getVolume() const {
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
	Tree<V, H, S, A> :: getSizeOf() const {
		return sizeof (Tree);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	void
	Tree<V, H, S, A> :: show (String& string) const
	{
		string << "tree:" << endLine;
		if (Ancestor_ :: root_ != NULL) {
			Ancestor_ :: root_->showTree (string);
		} else {
			string << tab << "NULL" << endLine;
		}
		string << endLine;
	}
}
}


