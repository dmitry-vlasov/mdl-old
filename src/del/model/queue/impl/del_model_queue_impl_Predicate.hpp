/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_queue_impl_Predicate.hpp                       */
/* Description:     predicates in queue model                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface.hpp"

namespace del {
namespace model {
namespace queue {
namespace impl {

template<class A>
class Predicate :
	public queue :: Predicate,
	public Scalar<Predicate<A>, A>{
public :
	typedef A Allocator_;

	Predicate();
	virtual ~ Predicate();

	// queue :: Predicate interface
	virtual value :: Integer getSize() const;
	virtual value :: Variable getConcept (const value :: Integer) const;
	virtual bool addConcept (const value :: Variable);
	virtual bool isTrue (const value :: Variable) const;
	virtual void unite (const queue :: Predicate*);

	// del :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	typedef
		del :: set :: Set
		<
			value :: Variable,
			storage :: ByValue,
			Allocator_
		>
		ConceptSet_;

	enum {
		INITIAL_CONCEPT_SET_CAPACITY = 256
	};

	ConceptSet_ conceptSet_;
};

}
}
}
}


