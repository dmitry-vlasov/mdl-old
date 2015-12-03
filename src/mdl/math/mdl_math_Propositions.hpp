/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_math_Propositions.hpp                                */
/* Description:     global container for propositions                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_MATH_PROPOSITIONS_HPP_
#define MDL_MATH_PROPOSITIONS_HPP_

#include "mdl/math/mdl_math_Container.hpp"

namespace mdl {
namespace math {

class Propositions :
	public object :: Object,
	public Scalar<Propositions> {
public :
	Propositions ();
	virtual ~ Propositions();
	
	forest :: Proposition* getTree();
	void addToSet (mdl :: Proposition*);
	void addToTree (mdl :: Proposition*);

	void sort();
	void sortByRate();
	void sortByExpSize();
	index :: Assertion getSize() const;
	mdl :: Proposition* get (const index :: Assertion);
	mdl :: Proposition* getIncreasing (const index :: Assertion);
	mdl :: Proposition* getDescending (const index :: Assertion);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;
	
private :
	typedef
		set :: Set
		<
			Proposition,
			storage :: ByWeakPointer,
			allocator :: Heap
		>
		Set_;

	enum {
		INITIAL_SET_CAPACITY = size :: KILOBYTE * 64
	};

	Set_ set_;
	forest :: Proposition* tree_;
	pthread_mutex_t mutex_;
};

}
}

#endif /*MDL_MATH_PROPOSITIONS_HPP_*/
