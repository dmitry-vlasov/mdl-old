/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_storage_ByInheritance.hpp                 */
/* Description:     inheritance storage policy for containers                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONTAINER_STORAGE_BY_INHERITANCE_HPP_
#define NSTD_CONTAINER_STORAGE_BY_INHERITANCE_HPP_

namespace nstd {
namespace container {
namespace storage {

template
<
	class T	// value type
>
class ByInheritance : public T {
public :
	typedef T Ancestor_;
	typedef T Type_;
	typedef const T& Argument_;
	typedef T Value_;
	typedef T& Reference_;
	typedef const T& const_Reference_;

	ByInheritance();
    ByInheritance (Argument_);
    ByInheritance (const ByInheritance&);

	Value_ getValue() const;
	Reference_ getReference();
	const_Reference_ getReference() const;

	void undefine();
	void clear();
	void erase();
	void init();

	// nstd :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	template<class S>
	void show (S&) const;
};

	template<class T, class S>
	S&
	operator << (S&, const ByInheritance<T>&);
}
}
}

#endif /*NSTD_CONTAINER_STORAGE_BY_INHERITANCE_HPP_*/
