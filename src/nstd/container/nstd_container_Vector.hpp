/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_Vector.hpp                                */
/* Description:     vector (mutable in size) container                       */
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

/// Mutable in size Vector class.
template
<
	class T,                 ///< stored type
	template<class> class H, ///< storage policy (by value, by pointer, etc.)
	class A                  ///< allocator
>
class Vector : public continual :: Resizable<T, H, A> {
private :
	typedef typename continual :: Resizable<T, H, A> Ancestor_;
protected :
	typedef typename Ancestor_ :: Storage_ Storage_;
public :
	typedef typename Ancestor_ :: Index_ Index_;
	typedef typename Ancestor_ :: Type_ Type_;
	typedef typename Ancestor_ :: Argument_ Argument_;
	typedef typename Ancestor_ :: Value_ Value_;
	typedef typename Ancestor_ :: Reference_ Reference_;
	typedef typename Ancestor_ :: const_Reference_ const_Reference_;

	Vector ();
	Vector (const Index_);
	Vector (const Vector&);
	template<class T1, template<class> class H1>
	Vector (const typename continual :: Collection<T1, H1>&);
	Vector (const Type_* const, const Index_);
	virtual ~ Vector();

	Index_ add (Argument_);
	void insert (Argument_, const Index_);
	void insertNextTo (Argument_, const Argument_);
	void insertPreviousTo (Argument_, const Argument_);
	void shiftToEnd (const Index_);

	Reference_ pushRaw ();
	Reference_ push();
	Reference_ pushLast();
	Reference_ pushFirst();
	Value_ popLast();
	Value_ popFirst();

	Reference_ pop ();
	const_Reference_ pop () const;

	void operator = (const Vector&);
	template<class T1, template<class> class H1>
	void operator = (const typename continual :: Collection<T1, H1>&);
	template<class T1, template<class> class H1>
	Vector& operator << (const typename continual :: Collection<T1, H1>&);
	Vector& operator << (Vector& (*manip)(Vector&) );
	template<class T1, template<class> class H1>
	void append (const continual :: Collection<T1, H1>&);
	void append (const Type_* const, const Index_);

	// nstd :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getRawVolume () const;
	Size_t getSizeOf() const;
};

}
}


