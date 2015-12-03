/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_types_pair.cpp                                       */
/* Description:     basic template for pairs of values                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_TYPES_PAIR_CPP_
#define DEL_TYPES_PAIR_CPP_

namespace del {
namespace pair {

	/****************************
	 *		Public members
	 ****************************/

	template<class T, class A>
	inline
	Pair<T, A> :: Pair() :
	first_ (Undefined<Type_> :: getValue()),
	second_ (Undefined<Type_> :: getValue()) {
	}
	template<class T, class A>
	inline
	Pair<T, A> :: Pair (const Type_ first, const Type_ second) :
	first_ (first),
	second_ (second) {
	}
	template<class T, class A>
	template<class T1, class A1>
	inline
	Pair<T, A> :: Pair (const Pair<T1, A1>& pair) :
	first_ (pair.first_),
	second_ (pair.second_) {
	}
	template<class T, class A>
	inline
	Pair<T, A> :: ~ Pair() {
	}

	template<class T, class A>
	template<class T1, class A1>
	inline void
	Pair<T, A> :: operator = (const Pair<T1, A1>& pair)
	{
		first_ = pair.first_;
		second_ = pair.second_;
	}
	template<class T, class A>
	template<class T1, class A1>
	inline bool
	Pair<T, A> :: operator == (const Pair<T1, A1>& pair) const
	{
		return
			(first_ == pair.first_) &&
			(second_ == pair.second_);
	}
	template<class T, class A>
	template<class T1, class A1>
	inline bool
	Pair<T, A> :: operator != (const Pair<T1, A1>& pair) const {
		return !operator == (pair);
	}
}
}

#endif /*DEL_TYPES_PAIR_CPP_*/
