/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_Pair.cpp                                  */
/* Description:     simple pair container                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {
namespace container {

	/****************************
	 *		Public members
	 ****************************/

	template<class T_1, class T_2>
	inline
	Pair<T_1, T_2> :: Pair () :
	value_1_ (),
	value_2_ () {
	}
	template<class T_1, class T_2>
	inline
	Pair<T_1, T_2> :: Pair (const Type_1_ value_1, const Type_2_ value_2) :
	value_1_ (value_1),
	value_2_ (value_2) {
	}
	template<class T_1, class T_2>
	inline
	Pair<T_1, T_2> :: Pair (const Pair& pair) :
	value_1_ (pair.value_1_),
	value_2_ (pair.value_2_) {
	}
	template<class T_1, class T_2>
	inline
	Pair<T_1, T_2> :: ~ Pair() {
	}

	template<class T_1, class T_2>
	inline typename Pair<T_1, T_2> :: Type_1_
	Pair<T_1, T_2> :: getFirstValue () const {
		return value_1_;
	}
	template<class T_1, class T_2>
	inline typename Pair<T_1, T_2> :: Type_2_
	Pair<T_1, T_2> :: getSecondValue () const {
		return value_2_;
	}
	template<class T_1, class T_2>
	inline void
	Pair<T_1, T_2> :: setFirstValue (const Type_1_ value_1) {
		value_1_ = value_1;
	}
	template<class T_1, class T_2>
	inline void
	Pair<T_1, T_2> :: setSecondValue (const Type_2_ value_2) {
		value_2_ = value_2;
	}

	template<class T_1, class T_2>
	inline void
	Pair<T_1, T_2> :: operator = (const Pair& pair)
	{
		value_1_ = pair.value_1_;
		value_2_ = pair.value_2_;
	}
	template<class T_1, class T_2>
	inline bool
	Pair<T_1, T_2> :: operator == (const Pair& pair) const
	{
		return
			(value_1_ == pair.value_1_) &&
			(value_2_ == pair.value_2_);
	}
	template<class T_1, class T_2>
	inline bool
	Pair<T_1, T_2> :: operator != (const Pair& pair) const {
		return !(operator == (pair));
	}

	// nstd :: Object implementation
	template<class T_1, class T_2>
	inline void
	Pair<T_1, T_2> :: commitSuicide() {
		delete this;
	}
	template<class T_1, class T_2>
	inline Size_t
	Pair<T_1, T_2> :: getVolume() const {
		return 0;
	}
	template<class T_1, class T_2>
	inline Size_t
	Pair<T_1, T_2> :: getSizeOf() const {
		return sizeof (Pair);
	}
	template<class T_1, class T_2>
	template<class S>
	void
	Pair<T_1, T_2> :: show (S& s) const {
		s << value_1_ << ", " << value_2_;
	}
}
}


