/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_continual_Block.hpp                       */
/* Description:     array container for long vector                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONTAINER_CONTINUAL_BLOCK_HPP_
#define NSTD_CONTAINER_CONTINUAL_BLOCK_HPP_

#include "container/continual/nstd_container_continual_Collection.hpp"

namespace nstd {
namespace container {
namespace continual {

template
<
	class T,                 ///< stored type
	template<class> class H, ///< storage policy (by value, by pointer, etc.)
	class A,                 ///< allocator
	Size_t C                 ///< constant capacity
>
class Block :
	public Collection<T, H>,
	public memory :: storage :: Array<Block<T, H, A, C>, H<T>, A> {
private :
	typedef
		Collection<T, H>
		Ancestor_;
public :
	typedef typename Ancestor_:: Index_ Index_;
	typedef typename Ancestor_ :: Type_ Type_;
	typedef typename Ancestor_ :: Storage_ Storage_;
	typedef typename Ancestor_ :: const_Reference_ const_Reference_;
	typedef typename Ancestor_ :: Reference_ Reference_;
	typedef typename Ancestor_ :: Argument_ Argument_;
	typedef A Allocator_;
	enum {
		CAPACITY = C
	};
	typedef
		typename memory :: storage :: Array
		<
			Block,
			Storage_,
			Allocator_
		>
		Memory_;

	Block ();
	Block (const Block&);
	virtual ~Block();

	void init ();
	void operator = (const Block& block);

	void add (Argument_);

	Reference_ pushRaw ();
	Reference_ push ();

	Storage_& pushRawNode ();
	Storage_& pushNode ();
	Index_ getCapacity() const;

	bool isFull () const;

	// nstd :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getRawVolume () const;
	Size_t getSizeOf() const;

protected :
	void undefineBlock();
};

}
}
}

#endif /*NSTD_CONTAINER_CONTINUAL_BLOCK_HPP_*/
