/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_Set.hpp                                   */
/* Description:     set container                                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "container/continual/nstd_container_continual_Resizable.hpp"

namespace nstd {
namespace container {

/* Mutable in size Set class. */
template
<
	class T,                 ///< stored type
	template<class> class H, ///< storage policy (by value, by pointer, etc.)
	class A                  ///< allocator
>
class Set : public continual :: Resizable<T, H, A> {
	typedef typename continual :: Resizable<T, H, A> Ancestor_;
public :
	typedef typename Ancestor_ :: Index_ Index_;
	typedef typename Ancestor_ :: Type_ Type_;
	typedef typename Ancestor_ :: Value_ Value_;
	typedef typename Ancestor_ :: Argument_ Argument_;
	typedef typename Ancestor_ :: Storage_ Storage_;

	Set ();
	Set (const Index_);
	Set (const Set&);
	template<class T1, template<class> class H1>
	Set (const typename continual :: Collection<T1, H1>&);
	Set (const Type_* const, const Index_);
	virtual ~ Set();

	Index_ add (Argument_);
	Index_ find (Argument_) const;
	Index_ findPlace (Argument_) const;
	bool contains (Argument_) const;
	Index_ addValue (Argument_);
	void removeValue (Argument_);
	void sort();
	void qSort();
	void qSort (int (*compare) (Type_, Type_));
	void combSort();

	template<class T1, template<class> class H1>
	void unite (const typename continual :: Collection<T1, H1>&);
	void unite (const Type_* const, const Index_);

	template<class T1, template<class> class H1>
	void intersect (const typename continual :: Collection<T1, H1>&);
	void intersect (const Type_* const, const Index_);
	void intersect (const Set&);

	template<class T1, template<class> class H1>
	void subtract (const typename continual :: Collection<T1, H1>&);
	void subtract (const Type_* const, const Index_);
	void subtract (const Set&);

	void insert (Argument_, const Index_);
	bool isDisjointed (const Set&) const;

	bool verify (const bool strict = true) const;

	// nstd :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getRawVolume () const;
	Size_t getSizeOf() const;

private :
	enum {
		LINEAR_SEARCH_THRESHOLD = 32,
		INTERSECT_THRESHOLD = 32,
		INTERSECT_FACTOR = 3
	};
	template<class T1, template<class> class H1, bool>
	void intersectDirected (const typename continual :: Collection<T1, H1>&);
	template<bool>
	void intersectDirected (const Type_* const, const Index_);
	template<bool>
	void intersectDirected (const Set&);

	template<class T1, template<class> class H1>
	bool isDisjointedDirected (const typename continual :: Collection<T1, H1>&) const;
	bool isDisjointedDirected (const Type_* const, const Index_) const;
	bool isDisjointedDirected (const Set&) const;

	void quickSort (const int low, const int high);
	void quickSort (const int low, const int high, int (*compare) (Type_, Type_));
};

}
}


