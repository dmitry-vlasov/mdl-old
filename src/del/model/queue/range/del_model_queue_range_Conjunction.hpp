/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_queue_range_Conjunction.hpp                   */
/* Description:     conjunction range element                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_MODEL_QUEUE_RANGE_CONJUNCTION_HPP_
#define DEL_MODEL_QUEUE_RANGE_CONJUNCTION_HPP_

#include "del/interface/del_interface.hpp"

namespace del {
namespace model {
namespace queue {
namespace range {

template<class A = allocator :: Heap>
class Conjunction :
	public Range,
	public Scalar<Conjunction<A>, A> {
public :
	typedef A Allocator_;

	Conjunction
	(
		const del :: Formula* formula,
		const value :: Variable concepts[],
		const value :: Integer size,
		const value :: Variable concept
	);
	Conjunction (const Conjunction&);
	virtual ~ Conjunction();

	// queue :: Domain interface
	virtual Type getType() const;

	// queue :: Element interface
	virtual const del :: Formula* getFormula() const;
	virtual value :: Integer getSize() const;
	virtual value :: Variable getConcept (const value :: Integer = 0) const;
	virtual value :: Relation getRelation() const;

	// del :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	template<class>
	friend class Conjunction;

	typedef
		del :: vector :: Vector
		<
			value :: Variable,
			storage :: ByValue,
			Allocator_
		>
		ConceptVector_;

	const del :: Formula* formula_;
	ConceptVector_        concepts_;
	value :: Variable     concept_;
};

}
}
}
}

#endif /*DEL_MODEL_QUEUE_RANGE_CONJUNCTION_HPP_*/
