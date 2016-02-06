/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_Forest.ipp                                */
/* Description:     forest expression set class                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/expression/direction/mdl_expression_direction.hpp"

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
	Forest<V, H, S, A> :: Forest () :
	Ancestor_ (),
	level_ (0) {
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline
	Forest<V, H, S, A> :: ~ Forest() {
	}

	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	template<class E>
	inline typename Forest<V, H, S, A> :: Iterator_
	Forest<V, H, S, A> :: addBranch
	(
		const E* const expression,
		const Value_ value,
		const index :: Step level
	)
	{
		if (level == index :: undefined :: STEP) {
			++ level_;
		} else {
			level_ = level;
		}
		return Ancestor_ :: addBranch (expression, value);
	}

	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline index :: Step
	Forest<V, H, S, A> :: getLevel() const {
		return level_;
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
	Forest<V, H, S, A> :: copyNode (Iterator_& target, const I& source) const
	{
		Ancestor_ :: copyNode (target, source);
		const index :: Step level = source->getLevel();
		target->setLevel (level);

		Iterator_ iterator (target);
		while (true) {
			if (iterator->getLevel() > level) {
				iterator->setLevel (level);
			}
			if (iterator.template isTerminal<direction :: LEFT>()) {
				break;
			}
			-- iterator;
		}
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
	Forest<V, H, S, A> :: findNode (Iterator_& target, const I& source) const {
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
	Forest<V, H, S, A> :: addFindNode (Iterator_& target, const I& source) const
	{
		Ancestor_ :: addFindNode (target, source);
		Iterator_ iterator (target);
		while (true) {
			if (iterator->getLevel() > level_) {
				iterator->setLevel (level_);
			}
			if (iterator.template isTerminal<direction :: LEFT>()) {
				break;
			}
			-- iterator;
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
	Forest<V, H, S, A> :: commitSuicide() {
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
	Forest<V, H, S, A> :: getVolume() const {
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
	Forest<V, H, S, A> :: getSizeOf() const {
		return sizeof (Forest);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	void
	Forest<V, H, S, A> :: show (String& string) const
	{
		string << "forest:" << endLine;
		if (Ancestor_ :: root_ != NULL) {
			Ancestor_ :: root_->showForest (string);
		} else {
			string << tab << "NULL" << endLine;
		}
		string << endLine;
	}
}
}


