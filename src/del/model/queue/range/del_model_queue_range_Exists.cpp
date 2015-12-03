/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_queue_range_Exists.cpp                        */
/* Description:     exists range element                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_MODEL_QUEUE_RANGE_EXISTS_CPP_
#define DEL_MODEL_QUEUE_RANGE_EXISTS_CPP_

#include "del/auxiliary/del_auxiliary.hpp"
#include "del/source/del_source.hpp"
#include "del/model/del_model.hpp"

namespace del {
namespace model {
namespace queue {
namespace range {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Exists<A> :: Exists
	(
		const del :: Formula* formula,
		const value :: Relation relation,
		const value :: Variable concept
	) :
	formula_ (formula),
	relation_ (relation),
	concept_ (concept) {
	}
	template<class A>
	inline
	Exists<A> :: Exists (const Exists& exists) :
	formula_ (exists.formula_),
	relation_ (exists.relation_),
	concept_ (exists.concept_) {
	}
	template<class A>
	Exists<A> :: ~ Exists() {
	}

	// del :: Model implementation
	template<class A>
	typename Exists<A> :: Type
	Exists<A> :: getType() const {
		return EXISTS;
	}
	template<class A>
	value :: Integer
	Exists<A> :: getSize() const {
		return 1;
	}
	template<class A>
	value :: Variable
	Exists<A> :: getConcept (const value :: Integer) const {
		return concept_;
	}
	template<class A>
	value :: Relation
	Exists<A> :: getRelation() const {
		return relation_;
	}

	// queue :: Element implementation
	template<class A>
	const del :: Formula*
	Exists<A> :: getFormula() const {
		return formula_;
	}

using manipulator :: space;
using manipulator :: iterate;
using manipulator :: tab;

	// Object implementation
	template<class A>
	void
	Exists<A> :: commitSuicide() {
		delete this;
	}
	template<>
	void
	Exists<allocator :: Stack> :: commitSuicide() {
	}
	template<class A>
	Size_t
	Exists<A> :: getVolume() const
	{
		Size_t volume = 0;
		return volume;
	}
	template<class A>
	Size_t
	Exists<A> :: getSizeOf() const {
		return sizeof (Exists);
	}
	template<class A>
	void
	Exists<A> :: show (String& string) const
	{
		string << "E" << Table :: relations()->get (relation_);
		string << "." << Table :: variables()->get (concept_);
	}
}
}
}
}

#endif /*DEL_MODEL_QUEUE_RANGE_EXISTS_CPP_*/
