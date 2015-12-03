/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_continual_Resizable.hpp                   */
/* Description:     base class for resizable array-based containers          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONTAINER_CONTINUAL_RESIZABLE_HPP_
#define NSTD_CONTAINER_CONTINUAL_RESIZABLE_HPP_

#include "container/continual/nstd_container_continual_Collection.hpp"

namespace nstd {
namespace container {
namespace continual {

/// Mutable in size continual storage.
template
<
	class T,                 ///< stored type
	template<class> class H, ///< storage policy (by value, by pointer, etc.)
	class A                  ///< allocator
>
class Resizable :
	public Collection<T, H>,
	public memory :: storage :: Vector<Resizable<T, H, A>, H<T>, A> {
protected :
	typedef Collection<T, H> Ancestor_;
public :
	typedef typename Ancestor_:: Index_ Index_;
	typedef typename Ancestor_ :: Type_ Type_;
	typedef typename Ancestor_ :: Argument_ Argument_;
	typedef typename Ancestor_ :: Storage_ Storage_;
	typedef A Allocator_;
	typedef
		typename memory :: storage :: Vector
		<
			Resizable,
			Storage_,
			Allocator_
		>
		Memory_;

	Resizable ();
	Resizable (const Index_);
	Resizable (const Resizable&);
	template<class T1, template<class> class H1>
	Resizable (const Collection<T1, H1>&);
	Resizable (const Type_* const, const Index_);
	virtual ~ Resizable();

	void init (const Index_ = 2);

	template<class T1, template<class> class H1>
	void copy (const Collection<T1, H1>&);
	void copy (const Type_* const, const Index_);

	Index_ getCapacity() const;
	void remove (const Index_);
	void insert (Argument_, const Index_);
	void removeLast();
	void removeFirst();

	bool ensureSize (const Index_, const bool = true);
	bool ensureCapacity (const Index_, const bool = true);
	bool ensureCapacityNotLess (const Index_, const bool = true);
	bool ensureOneMoreElement (const bool = true);

	// nstd :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getRawVolume() const;
	Size_t getSizeOf() const;

protected :
	void undefineTail();

private :
	Index_ capacity_;

	enum {
		LINEAR_GROWTH_POLICY_THRESHOLD = 1024 * 32
	};
};

}
}
}

#endif /*NSTD_CONTAINER_CONTINUAL_RESIZABLE_HPP_*/
