/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_interpolation_Linear_1.cpp                          */
/* Description:     Linear method of 1 variable interpolation evaluation     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_INTERPOLATION_LINEAR_1_CPP_
#define NSTD_INTERPOLATION_LINEAR_1_CPP_

namespace nstd {
namespace interpolation {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	Linear<1, A> :: Linear
	(
		const Integer degree,
		const Sample_& sample,
		const Real precision
	) :
	sample_ (sample),
	a_ (degree, sample_),
	solver_ (degree + 1, precision) {
	}
	template<class A>
	Linear<1, A> :: ~ Linear() {
	}

	template<class A>
	const typename Linear<1, A> :: Polynomial_&
	Linear<1, A> :: evaluate ()
	{
		initMatrix();
		initRightSide();
		solver_.solve();
		for (int i = 0; i < solver_.getDimension(); ++ i) {
			a_.polynomial().coefficient (i) = solver_.getSolution() [i];
		}
		return a_.polynomial();
	}
	template<class A>
	inline const typename Linear<1, A> :: Approximation_&
	Linear<1, A> :: getApproximation() const {
		return a_;
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: iterate;
using manipulator :: tab;

	template<class A>
	template<class S>
	inline void
	Linear<1, A> :: show (S& string) const {
		solver_.show (string);
	}

	// nstd :: Object implementation
	template<class A>
	void
	Linear<1, A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Linear<1, A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += a_.getVolume();
		volume += solver_.getVolume();
		return volume;
	}
	template<class A>
	Size_t
	Linear<1, A> :: getSizeOf() const {
		return sizeof (Linear);
	}
	template<class A>
	void
	Linear<1, A> :: show (String<>& string) const {
		show<String<> > (string);
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	void
	Linear<1, A> :: initMatrix()
	{
		for (int i = 0; i < solver_.getDimension(); ++ i) {
			typename Solver_ :: Vector_* row = solver_.matrix().push();
			for (int j = 0; j < solver_.getDimension(); ++ j) {
				Real& a_i_j = row->push();
				a_i_j = 0;
				const Real deg = i + j;
				for (int k = 0; k < sample_.getSize(); ++ k) {
					const Real v = pow (sample_.getX (k), deg);
					a_i_j += v;
				}
			}
		}
	}
	template<class A>
	void
	Linear<1, A> :: initRightSide()
	{
		for (int i = 0; i < solver_.getDimension(); ++ i) {
			Real& b_i = solver_.rightSide().push();
			b_i = 0;
			for (int k = 0; k < sample_.getSize(); ++ k) {
				const Real v = sample_.getY (k) * pow (sample_.getX (k), i);
				b_i += v;
			}
		}
	}
}
}

#endif /*NSTD_INTERPOLATION_LINEAR_1_CPP_*/
