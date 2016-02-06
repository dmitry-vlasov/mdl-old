/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_interpolation_Approximation_1.cpp                   */
/* Description:     the 1 var. polynomial approximation to the given data    */
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
	Approximation<1, A> :: Approximation
	(
		const Integer degreeX,
		const Sample_& sample
	) :
	polynomial_ (degreeX),
	sample_ (sample) {
	}
	template<class A>
	Approximation<1, A> :: Approximation (const Approximation& approximation) :
	polynomial_ (approximation.polynomial_),
	sample_ (approximation.sample_) {
	}
	template<class A>
	Approximation<1, A> :: ~ Approximation() {
	}

	template<class A>
	inline typename Approximation<1, A> :: Polynomial_&
	Approximation<1, A> :: polynomial() {
		return polynomial_;
	}
	template<class A>
	Real
	Approximation<1, A> :: evalSSE() const
	{
		Real sum = 0;
		for (Integer i = 0; i < sample_.getSize(); ++ i) {
			const Real x_i = sample_.getX (i);
			const Real y_i = sample_.getY (i);
			const Real p_i = polynomial_.eval (x_i);
			sum += (p_i - y_i) * (p_i - y_i);
		}
		return sum;
	}
	template<class A>
	Real
	Approximation<1, A> :: evalMSE() const
	{
		const Real sse = evalSSE();
		return sse / sample_.getSize();
	}

	template<class A>
	Real
	Approximation<1, A> :: evalDerivativeSSE (const Integer k) const
	{
		Real sum = 0;
		for (Integer i = 0; i < sample_.getSize(); ++ i) {
			const Real x_i = sample_.getX (i);
			const Real y_i = sample_.getY (i);
			const Real p_i = polynomial_.eval (x_i);
			sum += 2 * pow (x_i , k) * (p_i - y_i);
		}
		return sum;
	}

	template<class A>
	inline Integer
	Approximation<1, A> :: getDegreeX() const {
		return polynomial_.getDegreeX();
	}
	template<class A>
	inline Real
	Approximation<1, A> :: getCoefficient (const Integer i) const {
		return polynomial_.getCoefficient (i);
	}
	template<class A>
	inline Real&
	Approximation<1, A> :: coefficient (const Integer i) {
		return polynomial_.coefficient (i);
	}

	template<class A>
	bool
	Approximation<1, A> :: allCoefficientsArePositive() const
	{
		for (int i = 1; i < polynomial_.getDegreeX(); ++ i) {
			if (polynomial_.getCoefficient (i) < 0) {
				return false;
			}
		}
		return true;
	}
	template<class A>
	bool
	Approximation<1, A> :: allDerivativesArePositive (const Integer precision) const
	{
		Integer degree = getDegreeX();
		if (degree == 0) {
			return true;
		} else {
		}
		Polynomial<1, Allocator_>* derivative [degree];
		derivative [0] = polynomial_.derivateX();
		for (int i = 0; i + 1 < degree; ++ i) {
			derivative [i + 1] = derivative [i]->derivateX();
		}
		bool result = true;
		for (Integer i = 0; i < sample_.getSize(); ++ i) {
			const Real x_i = sample_.getX (i);
			for (int j = 0; j < degree; ++ j) {
				const Real d_i_j = derivative [j]->eval (x_i);
				if (d_i_j < -precision) {
					result = false;
					break;
				}
			}
			if (!result) {
				break;
			}
		}
		for (int i = 0; i < degree; ++ i) {
			derivative [i]->commitSuicide();
		}
		return result;
	}

	template<class A>
	inline void
	Approximation<1, A> :: operator = (const Approximation& approximation) {
		polynomial_ = approximation.polynomial_;
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: iterate;
using manipulator :: tab;

	template<class A>
	template<class S>
	void
	Approximation<1, A> :: show (S& string) const
	{
		string << "p(x) = " << polynomial_ << endLine;
		string << "SSE = " << evalSSE() << endLine;
		string << "MSE = " << evalMSE() << endLine;
		string << "----------------" << endLine;
		for (Integer i = 0; i < sample_.getSize(); ++ i) {
			const Real x = sample_.getX (i);
			const Real y = sample_.getY (i);
			string << tab;
			string << "x = " << x << ", ";
			string << "y = " << y << ", ";
			string << "p(x) = " << polynomial_.eval (x) << ", ";
			string << endLine;
		}
		string << endLine;
		string << endLine;
	}

	// nstd :: Object implementation
	template<class A>
	void
	Approximation<1, A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Approximation<1, A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += polynomial_.getVolume();
		return volume;
	}
	template<class A>
	Size_t
	Approximation<1, A> :: getSizeOf() const {
		return sizeof (Approximation);
	}
	template<class A>
	void
	Approximation<1, A> :: show (String<>& string) const {
		show<String<> >(string);
	}

	/****************************
	 *		Private members
	 ****************************/
}
}


