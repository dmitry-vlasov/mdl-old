/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_math_Types.hpp                                       */
/* Description:     global container for types                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/math/mdl_math_Container.hpp"

namespace mdl {
namespace math {

class Types :
	public Container<mdl :: Type, index :: Type>,
	public Scalar<Types> {
public :
	Types ();
	virtual ~ Types();
	
	mdl :: Type* get (const index :: Type);
	index :: Type add (mdl :: Type*);

	void mine() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	typedef 
		Container<mdl :: Type, index :: Type>
		Container_;
	typedef
		vector :: Vector
		<
			mdl :: Type*,
			storage :: ByValue,
			allocator :: Heap
		>
		Types_;

	enum { 
		INITIAL_TYPE_VECTOR_CAPACITY = size :: KILOBYTE,
		INITIAL_ROOT_TYPES_CAPACITY  = 32,
		INITIAL_MINE_OUTPUT_CAPACITY = size :: KILOBYTE
	};

	Types_ rootTypes_;
	pthread_mutex_t mutex_;
};

}
}


