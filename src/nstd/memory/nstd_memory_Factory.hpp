/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_Factory.hpp                                  */
/* Description:     template factory for objects                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MEMORY_FACTORY_HPP_
#define NSTD_MEMORY_FACTORY_HPP_

namespace nstd {
namespace memory {

template<class T, class A>
class Factory : public storage :: Scalar<T, A> {
public :
	typedef T Type_;
	typedef A Allocator_;
	typedef
		typename storage :: Scalar<Type_, Allocator_>
		Storage_;

	static Type_* create ();
	template<class A_1>
	static Type_* create (A_1);
	template<class A_1, class A_2>
	static Type_* create (A_1, A_2);
	template<class A_1, class A_2, class A_3>
	static Type_* create (A_1, A_2, A_3);
	template<class A_1, class A_2, class A_3, class A_4>
	static Type_* create (A_1, A_2, A_3, A_4);
	template<class A_1, class A_2, class A_3, class A_4, class A_5>
	static Type_* create (A_1, A_2, A_3, A_4, A_5);
	template<class A_1, class A_2, class A_3, class A_4, class A_5, class A_6>
	static Type_* create (A_1, A_2, A_3, A_4, A_5, A_6);
};

}
}

#endif /*NSTD_MEMORY_FACTORY_HPP_*/
