/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_queue_impl_Predicate.cpp                       */
/* Description:     predicates in queue model                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_MODEL_QUEUE_IMPL_PREDICATE_CPP_
#define DEL_MODEL_QUEUE_IMPL_PREDICATE_CPP_

#include "del/interface/del_interface.hpp"

namespace del {
namespace model {
namespace queue {
namespace impl {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	Predicate<A> :: Predicate() :
	conceptSet_ (INITIAL_CONCEPT_SET_CAPACITY) {
	}
	template<class A>
	Predicate<A> :: ~ Predicate() {
	}

	// queue :: Predicate implementation
	template<class A>
	value :: Integer
	Predicate<A> :: getSize() const {
		return conceptSet_.getSize();
	}
	template<class A>
	value :: Variable
	Predicate<A> :: getConcept (const value :: Integer i) const {
		return conceptSet_.getValue (i);
	}
	template<class A>
	bool
	Predicate<A> :: addConcept (const value :: Variable concept) {
		conceptSet_.add (concept);
	}
	template<class A>
	bool
	Predicate<A> :: isTrue (const value :: Variable concept) const {
		return conceptSet_.contains (concept);
	}
	template<class A>
	void
	Predicate<A> :: unite (const queue :: Predicate* predicate)
	{
		for (value :: Integer i = 0; i < predicate->getSize(); ++ i) {
			const value :: Variable concept = predicate->getConcept (i);
			conceptSet_.add (concept);
		}
	}

	// del :: Object implementaion
	template<class A>
	void
	Predicate<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Predicate<A> :: getVolume() const {
		return conceptSet_.getVolume();
	}
	template<class A>
	Size_t
	Predicate<A> :: getSizeOf() const {
		return sizeof
				(Predicate);
	}
	template<class A>
	void
	Predicate<A> :: show (String& string) const
	{
		for (value :: Integer i = 0; i < conceptSet_.getSize(); ++ i) {
			const value :: Variable
				concept = conceptSet_.getValue (i);
			if (concept == value :: TOP) {
				string << Token :: top_;
			} else {
				string << Table :: variables()->get (concept);
			}
			if (i + 1 < conceptSet_.getSize()) {
				string << ", ";
			}
		}
	}
}
}
}
}

#endif /*DEL_MODEL_QUEUE_IMPL_PREDICATE_CPP_*/
