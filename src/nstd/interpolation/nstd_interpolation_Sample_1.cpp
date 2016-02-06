/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_interpolation_Sample_1.cpp                          */
/* Description:     1 dim. sample for the polynomial interpolation           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {
namespace interpolation {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	Sample<1, A> :: Sample
	(
		const RealVector_& xVector,
		const RealVector_& yVector
	) :
	xVector_ (xVector),
	yVector_ (yVector),
	sample_ (xVector_.getSize()) {
	}
	template<class A>
	Sample<1, A> :: Sample (const Sample& sample) :
	xVector_ (sample.xVector_),
	yVector_ (sample.yVector_),
	sample_ (sample.sample_) {
	}
	template<class A>
	Sample<1, A> :: ~ Sample() {
	}

	template<class A>
	inline Integer
	Sample<1, A> :: getSize() const {
		return sample_.getSize();
	}
	template<class A>
	inline Real
	Sample<1, A> :: getX (const Integer i) const
	{
		const Integer index = sample_.getIndex (i);
		return xVector_.getValue (index);
	}
	template<class A>
	inline Real
	Sample<1, A> :: getY (const Integer i) const
	{
		const Integer index = sample_.getIndex (i);
		return yVector_.getValue (index);
	}

	template<class A>
	inline void
	Sample<1, A> :: clear() {
		sample_.clear();
	}
	template<class A>
	inline void
	Sample<1, A> :: addToControl (const Integer i) {
		sample_.addToControl(i);
	}
	template<class A>
	inline void
	Sample<1, A> :: addToLearning (const Integer i) {
		sample_.addToLearning (i);
	}
	template<class A>
	inline void
	Sample<1, A> :: setMode (const Mode_ mode) {
		sample_.setMode (mode);
	}

	template<class A>
	inline void
	Sample<1, A> :: set (const Sample_& sample) {
		sample_ = sample;
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: iterate;
using manipulator :: tab;

	template<class A>
	template<class S>
	void
	Sample<1, A> :: show (S& string) const
	{
		string << "sample: (" << xVector_.getSize() << ")" << endLine;
		string << "--------------" << endLine;
		showVector (string, xVector_, yVector_);
		string << endLine;
		string << endLine;
		string << sample_;
	}

	// object :: Object implementation
	template<class A>
	void
	Sample<1, A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Sample<1, A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += sample_.getVolume();
		return volume;
	}
	template<class A>
	Size_t
	Sample<1, A> :: getSizeOf() const {
		return sizeof (Sample);
	}
	template<class A>
	void
	Sample<1, A> :: show (String<>& string) const {
		show<String<> >(string);
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	template<class S>
	void
	Sample<1, A> :: showVector
	(
		S& string,
		const RealVector_& xVector,
		const RealVector_& yVector
	) const
	{
		for (Integer i = 0; i < xVector.getSize(); ++ i) {
			const Real x = xVector.getValue (i);
			const Real y = yVector.getValue (i);
			string << tab;
			string << "x = " << x << ", ";
			string << "y = " << y << ", ";
			string << endLine;
		}
	}
}
}


