/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_interpolation_Linear_2.cpp                          */
/* Description:     Linear method of 2 variable interpolation evaluation     */
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
	Linear<2, A> :: Linear
	(
		const Integer degreeX,
		const Integer degreeY,
		const Sample_& sample,
		const Real precision
	) :
	degreeX_ (degreeX),
	degreeY_ (degreeY),
	dimX_ (degreeX_ + 1),
	dimY_ (degreeY_ + 1),
	sample_ (sample),
	a_ (degreeX_, degreeY_, sample_),
	solver_ (dimX_ * dimY_, precision) {
	}
	template<class A>
	Linear<2, A> :: ~ Linear() {
	}

	template<class A>
	const typename Linear<2, A> :: Polynomial_&
	Linear<2, A> :: evaluate ()
	{
		initMatrix();
		initRightSide();
		solver_.solve();
		for (int ij = 0; ij < solver_.getDimension(); ++ ij) {
			const Integer i = convX (ij);
			const Integer j = convY (ij);
			const Real a = solver_.getSolution() [ij];
			a_.polynomial().coefficient (i, j) = a;
		}
		return a_.polynomial();
	}
	template<class A>
	inline const typename Linear<2, A> :: Approximation_&
	Linear<2, A> :: getApproximation() const {
		return a_;
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: iterate;
using manipulator :: tab;

	template<class A>
	template<class S>
	inline void
	Linear<2, A> :: show (S& string) const {
		solver_.show (string);
	}

	// nstd :: Object implementation
	template<class A>
	void
	Linear<2, A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Linear<2, A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += a_.getVolume();
		volume += solver_.getVolume();
		return volume;
	}
	template<class A>
	Size_t
	Linear<2, A> :: getSizeOf() const {
		return sizeof (Linear);
	}
	template<class A>
	void
	Linear<2, A> :: show (String<>& string) const {
		show<String<> > (string);
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	void
	Linear<2, A> :: initMatrix()
	{
		for (int ij = 0; ij < solver_.getDimension(); ++ ij) {
			const Integer i = convX (ij);
			const Integer j = convY (ij);
			typename Solver_ :: Vector_* row = solver_.matrix().push();
			for (int ab = 0; ab < solver_.getDimension(); ++ ab) {

				Real& a_ij_ab = row->push();
				a_ij_ab = 0;

				const Integer a = convX (ab);
				const Integer b = convY (ab);

				const Real degX = i + a;
				const Real degY = j + b;

				for (int k = 0; k < sample_.getSize(); ++ k) {
					const Real v = pow (sample_.getX (k), degX);
					const Real w = pow (sample_.getY (k), degY);
					a_ij_ab += v * w;
				}
			}
		}
	}
	template<class A>
	void
	Linear<2, A> :: initRightSide()
	{
		for (int ij = 0; ij < solver_.getDimension(); ++ ij) {
			const Integer i = convX (ij);
			const Integer j = convY (ij);
			Real& b_ij = solver_.rightSide().push();
			b_ij = 0;
			for (int k = 0; k < sample_.getSize(); ++ k) {
				const Real v = pow (sample_.getX (k), i);
				const Real w = pow (sample_.getY (k), j);
				b_ij += sample_.getZ (k) * v * w;
			}
		}
	}

	template<class A>
	inline Integer
	Linear<2, A> :: convXY (const Integer i, const Integer j) const {
		return i * dimX_ + j;
	}
	template<class A>
	inline Integer
	Linear<2, A> :: convX (const Integer a) const {
		return a / dimX_;
	}
	template<class A>
	inline Integer
	Linear<2, A> :: convY (const Integer a) const {
		return a % dimX_;
	}
}
}


