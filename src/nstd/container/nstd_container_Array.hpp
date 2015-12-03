/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_Array.hpp                                 */
/* Description:     array (immutable in size) container                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONTAINER_ARRAY_HPP_
#define NSTD_CONTAINER_ARRAY_HPP_

#include "container/continual/nstd_container_continual_Collection.hpp"

namespace nstd {
namespace container {

/// Non-mutable in size Array class.
template
<
	class T,                 ///< stored type
	template<class> class H, ///< storage policy (by value, by pointer, etc.)
	class A                  ///< allocator
>
class Array :
	public continual :: Collection<T, H>,
	public memory :: storage :: Array<Array<T, H, A>, H<T>, A> {
private :
	typedef typename continual :: Collection<T, H> Ancestor_;
public :
	typedef typename Ancestor_:: Index_ Index_;
	typedef typename Ancestor_ :: Type_ Type_;
	typedef typename Ancestor_:: Storage_ Storage_;
	typedef A Allocator_;
	typedef
		typename memory :: storage :: Array
		<
			Array,
			Storage_,
			Allocator_
		>
		Memory_;

	Array (const Index_);
	Array (const Ancestor_&);
	Array (const Array&);
	Array (const Type_ [], const Index_);
	virtual ~ Array();

	void copy (const Array&);

	// nstd :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getRawVolume () const;
	Size_t getSizeOf() const;
};

}
}

#endif /*NSTD_CONTAINER_ARRAY_HPP_*/
