/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_interpolation_Gradient_1.cpp                        */
/* Description:     the gradient method of 1 var interpolation evaluation    */
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
	Gradient<1, A>:: Gradient
	(
		const Integer degree,
		const Sample_& sample,
		const bool keepPositive
	) :
	keepPositive_ (keepPositive),
	degreeX_ (degree),
	dim_ (degreeX_ + 1),
	sample_ (sample),
	a_zero_ (dim_, sample_),
	a_plus_ (dim_, sample_),
	a_minus_ (dim_, sample_),
	a_prime_ (dim_, sample_),
	epsilon_ (0.0001),
	count_0_ (0),
	count_1_ (0),
	count_2_ (0),
	stepGradient_ (1),
	stepRavine_ (1) {
	}
	template<class A>
	Gradient<1, A>:: ~ Gradient() {
	}

	template<class A>
	typename Gradient<1, A> :: Polynomial_&
	Gradient<1, A>:: evaluate (const Real epsilon)
	{
		if (epsilon != 0) {
			epsilon_ = epsilon;
		}
		//ravineMethod();
		gradientMethod (epsilon);
		return a_zero_.polynomial();
	}
	template<class A>
	inline const typename Gradient<1, A> :: Approximation_&
	Gradient<1, A>:: getApproximation() const {
		return a_zero_;
	}

	template<class A>
	inline Integer
	Gradient<1, A>:: iterationsRavine() const {
		return count_0_;
	}
	template<class A>
	inline Integer
	Gradient<1, A>:: iterationsFirst() const {
		return count_1_;
	}
	template<class A>
	inline Integer
	Gradient<1, A>:: iterationsSecond() const {
		return count_2_;
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: iterate;
using manipulator :: tab;

	template<class A>
	template<class S>
	inline void
	Gradient<1, A>:: show (S& string) const {
		a_zero_.show (string);
	}

	// nstd :: Object implementation
	template<class A>
	void
	Gradient<1, A>:: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Gradient<1, A>:: getVolume() const
	{
		Size_t volume = 0;
		volume += a_zero_.getVolume();
		volume += a_plus_.getVolume();
		volume += a_minus_.getVolume();
		volume += a_prime_.getVolume();
		return volume;
	}
	template<class A>
	Size_t
	Gradient<1, A>:: getSizeOf() const {
		return sizeof (Gradient);
	}
	template<class A>
	void
	Gradient<1, A>:: show (String<>& string) const {
		show<String<> > (string);
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	Real
	Gradient<1, A>:: ravineMethod()
	{
		const Real delta = 0.1;
		Approximation_ a_0 (a_zero_);
		Approximation_ a_1 (a_zero_);
		Approximation_ a_2 (a_zero_);

		for (int i = 0; i < dim_; ++ i) {
			a_1.polynomial().coefficient (i) += 1;
		}
		while (true) {
			a_zero_ = a_0;
			const Real m_0 = gradientMethod (delta);
			Approximation_ r_0 (a_zero_);

			a_zero_ = a_1;
			const Real m_1 = gradientMethod (delta);
			Approximation_ r_1 (a_zero_);

			Real vector [dim_];
			for (int i = 0; i < dim_; ++ i) {
				vector [i] = (r_1.coefficient (i) - r_0.coefficient (i)) * stepRavine_;
			}

			if (m_0 > m_1) {
				a_2 = a_1;
				a_2.polynomial().addVector (vector, keepPositive_);
				if (a_2.evalSSE() > m_1) {
					a_zero_ = a_1;
					return m_1;
				}
			} else {
				a_2 = a_0;
				a_2.polynomial().subVector (vector, keepPositive_);
				if (a_2.evalSSE() > m_0) {
					a_zero_ = a_0;
					return m_0;
				}
			}
			++ count_0_;
		}
		return a_zero_.evalSSE();
	}

	template<class A>
	Real
	Gradient<1, A>:: gradientMethod (const Real epsilon)
	{
		if (epsilon != 0) {
			epsilon_ = epsilon;
		}
		Real m_0 = 0;
		Real m_1 = a_zero_.evalSSE();

		while (fabs (m_0 - m_1) > epsilon_) {

			Real gradient [dim_];
			for (int i = 0; i < dim_; ++ i) {
				const Real grad = a_zero_.evalDerivativeSSE (i);
				gradient [i] = grad;
			}
			quickestDescent (gradient);

			//constShift (gradient);
			//splittingShift (gradient);

			m_0 = m_1;
			m_1 = a_zero_.evalSSE();
			++ count_1_;
		}
		return m_1;
	}

	template<class A>
	void
	Gradient<1, A>:: quickestDescent (const Real gradient[])
	{
		const Real factor = 0.7;
		Real c = 1;
		Real m_0 = 0;
		Real m_1 = a_zero_.evalSSE();

		while (fabs (m_0 - m_1) > epsilon_) {
			a_plus_ = a_zero_;
			a_minus_ = a_zero_;

			Real vector [dim_];
			for (int i = 0; i < dim_; ++ i) {
				vector [i] = gradient [i] * c;
			}
			a_plus_.polynomial().addVector (vector, keepPositive_);
			a_minus_.polynomial().subVector (vector, keepPositive_);

			const Real m_plus  = a_plus_.evalSSE();
			const Real m_zero  = a_zero_.evalSSE();
			const Real m_minus = a_minus_.evalSSE();

			if (m_zero < m_plus) {
				if (m_minus < m_zero) {
					a_zero_ = a_minus_;
				} else if (m_plus < m_minus) {
					c *= factor;
				} else {
					c *= factor;
				}
			} else {
				if (m_minus < m_plus) {
					a_zero_ = a_minus_;
				} else if (m_zero < m_minus) {
					a_zero_ = a_plus_;
				} else {
					a_zero_ = a_plus_;
				}
			}
			m_0 = m_1;
			m_1 = std :: max (m_zero, std :: max (m_plus, m_minus));
			++ count_2_;
		}
	}
	template<class A>
	void
	Gradient<1, A>:: constShift (const Real gradient[])
	{
		Real vector [dim_];
		for (int i = 0; i < dim_; ++ i) {
			vector [i] = gradient [i] * stepGradient_;
		}
		a_zero_.polynomial().subVector (vector, keepPositive_);
	}
	template<class A>
	void
	Gradient<1, A>:: splittingShift (const Real gradient[])
	{
		const Real factor = 0.7;
		const Real m_0 = a_zero_.evalSSE();

		while (true) {
			a_prime_ = a_zero_;

			Real vector [dim_];
			for (int i = 0; i < dim_; ++ i) {
				vector [i] = gradient [i] * stepGradient_;
			}
			a_prime_.polynomial().subVector (vector, keepPositive_);
			const Real m_1 = a_prime_.evalSSE();
			if (m_1 < m_0) {
				a_zero_ = a_prime_;
				break;
			}
			stepGradient_ *= factor;
			++ count_2_;
		}
	}
}
}


