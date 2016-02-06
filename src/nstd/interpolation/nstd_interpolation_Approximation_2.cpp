/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_interpolation_Approximation_2.cpp                   */
/* Description:     the 2 var. polynomial approximation to the given data    */
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
	Approximation<2, A> :: Approximation (const Sample_& sample) :
	polynomial_ (),
	sample_ (sample) {
	}
	template<class A>
	Approximation<2, A> :: Approximation
	(
		const Integer degreeX,
		const Integer degreeY,
		const Sample_& sample
	) :
	polynomial_ (degreeX, degreeY),
	sample_ (sample) {
	}
	template<class A>
	Approximation<2, A> :: Approximation (const Approximation& approximation) :
	polynomial_ (approximation.polynomial_),
	sample_ (approximation.sample_) {
	}
	template<class A>
	Approximation<2, A> :: ~ Approximation() {
	}

	template<class A>
	inline typename Approximation<2, A> :: Polynomial_&
	Approximation<2, A> :: polynomial() {
		return polynomial_;
	}
	template<class A>
	Real
	Approximation<2, A> :: evalSSE() const
	{
		Real sum = 0;
		for (Integer i = 0; i < sample_.getSize(); ++ i) {
			const Real x_i = sample_.getX (i);
			const Real y_i = sample_.getY (i);
			const Real z_i = sample_.getZ (i);
			const Real p_i = polynomial_.eval (x_i, y_i);
			sum += (p_i - z_i) * (p_i - z_i);
		}
		return sum;
	}
	template<class A>
	Real
	Approximation<2, A> :: evalMSE() const
	{
		const Real sse = evalSSE();
		return sse / sample_.getSize();
	}

	template<class A>
	inline Real
	Approximation<2, A> :: evalDerivativeSSE (const Integer ij) const
	{
		const Integer i = polynomial_.convX (ij);
		const Integer j = polynomial_.convY (ij);
		return evalDerivativeSSE (i, j);
	}
	template<class A>
	Real
	Approximation<2, A> :: evalDerivativeSSE (const Integer i, const Integer j) const
	{
		Real sum = 0;
		for (Integer k = 0; k < sample_.getSize(); ++ k) {
			const Real x_k = sample_.getX (k);
			const Real y_k = sample_.getY (k);
			const Real p_k = polynomial_.eval (x_k, y_k);
			sum += 2 * pow (x_k , i) * pow (y_k , j) * (p_k - y_k);
		}
		return sum;
	}


	// 2 dim representation
	template<class A>
	inline Integer
	Approximation<2, A> :: getDegreeX() const {
		return polynomial_.getDegreeX();
	}
	template<class A>
	inline Integer
	Approximation<2, A> :: getDegreeY() const {
		return polynomial_.getDegreeY();
	}
	template<class A>
	inline Real
	Approximation<2, A> :: getCoefficient (const Integer i, const Integer j) const {
		return polynomial_.getCoefficient (i, j);
	}
	template<class A>
	inline Real&
	Approximation<2, A> :: coefficient (const Integer i, const Integer j) {
		return polynomial_.coefficient (i, j);
	}

	// 1 dim representation
	template<class A>
	inline Integer
	Approximation<2, A> :: getDegreeXY() const {
		return polynomial_.getDegreeXY();
	}
	template<class A>
	inline Real
	Approximation<2, A> :: getCoefficient (const Integer ij) const {
		return polynomial_.getCoefficient (ij);
	}
	template<class A>
	inline Real&
	Approximation<2, A> :: coefficient (const Integer ij) {
		return polynomial_.coefficient (ij);
	}

	template<class A>
	bool
	Approximation<2, A> :: diagonalCoefficientsArePositive() const
	{
		const Integer degreeX = polynomial_.getDegreeX();
		const Integer degreeY = polynomial_.getDegreeY();
		for (int i = 1; i < degreeX; ++ i) {
			for (int j = 1; j < degreeY; ++ j) {
				if ((i == j) && (polynomial_.getCoefficient (i,j) < 0)) {
					return false;
				}
				if ((i >= degreeY) && (polynomial_.getCoefficient (i,j) < 0)) {
					return false;
				}
				if ((j >= degreeX) && (polynomial_.getCoefficient (i,j) < 0)) {
					return false;
				}
			}
		}
		return true;
	}
	template<class A>
	bool
	Approximation<2, A> :: allCoefficientsArePositive() const
	{
		for (int i = 1; i < polynomial_.getDegreeX(); ++ i) {
			for (int j = 1; j < polynomial_.getDegreeY(); ++ j) {
				if (polynomial_.getCoefficient (i,j) < 0) {
					return false;
				}
			}
		}
		return true;
	}
	template<class A>
	bool
	Approximation<2, A> :: allDerivativesArePositive (const Integer precision) const
	{
		return
			allDerivativesArePositive ('x', precision) &&
			allDerivativesArePositive ('y', precision);
	}

	template<class A>
	inline void
	Approximation<2, A> :: operator = (const Approximation& approximation) {
		polynomial_ = approximation.polynomial_;
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: iterate;
using manipulator :: tab;

	template<class A>
	template<class S>
	void
	Approximation<2, A> :: show (S& string) const
	{
		string << "p (x, y) = " << polynomial_ << endLine;
		string << "SSE = " << evalSSE() << endLine;
		string << "MSE = " << evalMSE() << endLine;
		string << "----------------" << endLine;
		for (Integer i = 0; i < sample_.getSize(); ++ i) {
			const Real x = sample_.getX (i);
			const Real y = sample_.getY (i);
			const Real z = sample_.getZ (i);
			string << tab;
			string << "x = " << x << ", ";
			string << "y = " << y << ", ";
			string << "z = " << z << ", ";
			string << "p (x, y) = " << polynomial_.eval (x, y) << ", ";
			string << endLine;
		}
		string << endLine;
		string << endLine;
	}

	// nstd :: Object implementation
	template<class A>
	void
	Approximation<2, A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Approximation<2, A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += polynomial_.getVolume();
		return volume;
	}
	template<class A>
	Size_t
	Approximation<2, A> :: getSizeOf() const {
		return sizeof (Approximation);
	}
	template<class A>
	void
	Approximation<2, A> :: show (String<>& string) const {
		show<String<> >(string);
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	bool
	Approximation<2, A> :: allDerivativesArePositive
	(
		const char dir,
		const Integer precision
	) const
	{
		const Integer degree =
			(dir == 'x') ?
			polynomial_.getDegreeX() :
			polynomial_.getDegreeY();
		if (degree == 0) {
			return true;
		}
		Polynomial<2, Allocator_>* derivative [degree];
		derivative [0] =
			(dir == 'x') ?
			polynomial_.derivateX() :
			polynomial_.derivateY();
		for (int i = 0; i + 1 < degree; ++ i) {
			derivative [i + 1] =
				(dir == 'x') ?
				derivative [i]->derivateX() :
				derivative [i]->derivateY();
		}
		bool result = true;
		for (Integer i = 0; i < sample_.getSize(); ++ i) {
			const Real x_i = sample_.getX (i);
			const Real y_i = sample_.getY (i);
			for (int j = 0; j < degree; ++ j) {
				const Real d_i_j = derivative [j]->eval (x_i, y_i);
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
}
}


