/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_Bit.cpp                                   */
/* Description:     bit container                                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONTAINER_BIT_CPP_
#define NSTD_CONTAINER_BIT_CPP_

namespace nstd {
namespace container {

	/****************************
	 *		Public members
	 ****************************/

	template<int D, class T>
	inline
	Bit<D, T> :: Bit () :
	bits_ (0) {
	}
	template<int D, class T>
	inline
	Bit<D, T> :: Bit (const Type_ bits) :
	bits_ (bits) {
	}
	template<int D, class T>
	inline
	Bit<D, T> :: Bit (const Bit& bit) :
	bits_ (bit.bits_) {
	}
	template<int D, class T>
	inline
	Bit<D, T> :: ~ Bit() {
	}

	template<int D, class T>
	inline bool
	Bit<D, T> :: getValue (const char index) const
	{
		if (index < DIMENSION) {
			return (((bits_ >> index) % 2) > 0);
		} else {
			return false;
		}
	}
	template<int D, class T>
	inline void
	Bit<D, T> :: setValue (const char index, const bool value)
	{
		Type_ bit = 1;
		bit = bit << index;
		if (value) {
			bits_ = (bits_ | bit);
		} else {
			bits_ = (bits_ & ~bit);
		}
	}
	template<int D, class T>
	inline void
	Bit<D, T> :: set (const Type_ bits) {
		bits_ = bits;
	}
	template<int D, class T>
	inline typename Bit<D, T> :: Type_
	Bit<D, T> :: get () const {
		return bits_;
	}

	template<int D, class T>
	inline void
	Bit<D, T> :: operator = (const Bit& bit) {
		bits_ = bit.bits_;
	}

	template<int D, class T>
	inline bool
	Bit<D, T> :: operator == (const Bit& bit) const {
		return (bits_ == bit.bits_);
	}
	template<int D, class T>
	inline bool
	Bit<D, T> :: operator != (const Bit& bit) const {
		return !(operator == (bit));
	}

	// nstd :: Object implementation
	template<int D, class T>
	inline void
	Bit<D, T> :: commitSuicide() {
		delete this;
	}
	template<int D, class T>
	inline Size_t
	Bit<D, T> :: getVolume() const {
		return 0;
	}
	template<int D, class T>
	inline Size_t
	Bit<D, T> :: getSizeOf() const {
		return sizeof (Bit);
	}
	template<int D, class T>
	template<class S>
	void
	Bit<D, T> :: show (S& s) const
	{
		for (int i = 0; i < DIMENSION; ++ i) {
			s << (getValue (i) ? 1 : 0);
		}
	}
}
}

#endif /*NSTD_CONTAINER_BIT_CPP_*/
