/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_interpolation_Tuner_2.cpp                           */
/* Description:     the tuner for 2 dim. interpolator class                  */
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
	Tuner<2, A> :: Tuner
	(
		const bool diagonalCoefficientsArePositive,
		const bool allCoefficientsArePositive,
		const bool allDerivativesArePositive
	) :
	diagonalCoefficientsArePositive_ (diagonalCoefficientsArePositive),
	allCoefficientsArePositive_ (allCoefficientsArePositive),
	allDerivativesArePositive_ (allDerivativesArePositive),
	xVector_ (INITIAL_VECTOR_CAPACITY),
	yVector_ (INITIAL_VECTOR_CAPACITY),
	zVector_ (INITIAL_VECTOR_CAPACITY),
	deviation_ (),
	posDerivatives_ (),
	mse_ (0) {
	}
	template<class A>
	Tuner<2, A> :: Tuner
	(
		const RealVector_& xVector,
		const RealVector_& yVector,
		const RealVector_& zVector,
		const bool diagonalCoefficientsArePositive,
		const bool allCoefficientsArePositive,
		const bool allDerivativesArePositive
	) :
	diagonalCoefficientsArePositive_ (diagonalCoefficientsArePositive),
	allCoefficientsArePositive_ (allCoefficientsArePositive),
	allDerivativesArePositive_ (allDerivativesArePositive),
	xVector_ (xVector),
	yVector_ (yVector),
	zVector_ (zVector),
	deviation_ (),
	posDerivatives_ (),
	posCoefficients_ (),
	mse_ (0) {
	}
	template<class A>
	Tuner<2, A> :: ~ Tuner() {
	}

	template<class A>
	typename Tuner<2, A> :: Polynomial_*
	Tuner<2, A> :: evalOptimalPolynomial()
	{
		crossValidation();
		Integer optimalDegreeX = 0;
		Integer optimalDegreeY = 0;
		findOptimalDegree (optimalDegreeX, optimalDegreeY);
		Sample_ sample (xVector_, yVector_, zVector_);
		Linear_ interpolator (optimalDegreeX, optimalDegreeY, sample);
		const Polynomial_& result = interpolator.evaluate();
		Polynomial_* polynomial = new Polynomial_ (result);
		mse_ = interpolator.getApproximation().evalMSE();
		return polynomial;
	}
	template<class A>
	typename Tuner<2, A> :: Polynomial_*
	Tuner<2, A> :: evalPolynomialOfDegree
	(
		const Integer degreeX,
		const Integer degreeY
	)
	{
		Sample_ sample (xVector_, yVector_, zVector_);
		Linear_ interpolator (degreeX, degreeY, sample);
		const Polynomial_& result = interpolator.evaluate();
		Polynomial_* polynomial = new Polynomial_ (result);
		mse_ = interpolator.getApproximation().evalMSE();
		return polynomial;
	}
	template<class A>
	inline Real
	Tuner<2, A> :: getMse() const {
		return mse_;
	}
	template<class A>
	void
	Tuner<2, A> :: setData
	(
		const RealVector_& xVector,
		const RealVector_& yVector,
		const RealVector_& zVector
	)
	{
		xVector_.copy (xVector);
		yVector_.copy (yVector);
		zVector_.copy (zVector);
		mse_ = 0;
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: iterate;
using manipulator :: tab;

	template<class A>
	template<class S>
	void
	Tuner<2, A> :: show (S& string) const
	{
		Integer optimalDegreeX = 0;
		Integer optimalDegreeY = 0;
		findOptimalDegree (optimalDegreeX, optimalDegreeY);
		string << "optimal degreeX = " << optimalDegreeX << endLine;
		string << "optimal degreeY = " << optimalDegreeY << endLine;
		string << "MSE / degree dependency: " << endLine;
		string << "----------------" << endLine;
		for (Integer degreeX = 0; degreeX < MAX_DEGREE; ++ degreeX) {
			for (Integer degreeY = 0; degreeY < MAX_DEGREE; ++ degreeY) {
				const Real mse = deviation_[degreeX][degreeY];
				string << tab;
				string << "dX = " << degreeX << ", ";
				string << "dY = " << degreeY << ", ";
				string << "mse = " << mse << ", ";
				if (posDerivatives_ [degreeX][degreeY]) {
					string << "sign = (+), ";
				} else {
					string << "sign = (+/-), ";
				}
				string << endLine;
			}
		}
		string << endLine;
		string << endLine;
	}


	// nstd :: Object implementation
	template<class A>
	void
	Tuner<2, A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Tuner<2, A> :: getVolume() const
	{
		Size_t volume = 0;
		return volume;
	}
	template<class A>
	Size_t
	Tuner<2, A> :: getSizeOf() const {
		return sizeof (Tuner);
	}
	template<class A>
	void
	Tuner<2, A> :: show (String<>& string) const {
		show<String<> >(string);
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	Real
	Tuner<2, A> :: findOptimalDegree (Integer& optimalDegreeX, Integer& optimalDegreeY) const
	{
		Real minDeviation = 0;
		bool initial = true;

		for (Integer degreeX = 0; degreeX < MAX_DEGREE; ++ degreeX) {
			for (Integer degreeY = 0; degreeY < MAX_DEGREE; ++ degreeY) {
				if (((degreeX > 0) || (degreeY > 0))&&
					diagonalCoefficientsArePositive_ &&
					!posDiagonalCoefficients_ [degreeX][degreeY]) {
					continue;
				}
				if (((degreeX > 0) || (degreeY > 0))&&
					allCoefficientsArePositive_ &&
					!posCoefficients_ [degreeX][degreeY]) {
					continue;
				}
				if (((degreeX > 0) || (degreeY > 0))&&
					allDerivativesArePositive_ &&
					!posDerivatives_ [degreeX][degreeY]) {
					continue;
				}
				const Real mse = deviation_[degreeX][degreeY];
				if (initial || (minDeviation > mse)) {
					minDeviation = mse;
					optimalDegreeX = degreeX;
					optimalDegreeY = degreeY;
					initial = false;
				}
			}
		}
		return minDeviation;
	}

	template<class A>
	void
	Tuner<2, A> :: crossValidation()
	{
		typedef
			nstd :: Timer
			Timer;

		Sample_ sample (xVector_, yVector_, zVector_);
		Sampler_ sampler (xVector_.getSize());

		for (Integer degreeX = 0; degreeX < MAX_DEGREE; ++ degreeX) {
			for (Integer degreeY = 0; degreeY < MAX_DEGREE; ++ degreeY) {
				Real averageMse = 0;
				sampler.reset();
				while (sampler.generate()) {
					sample.set (sampler.getSample());
					sample.setMode (Sampler_ :: Sample_ :: LEARNING);
					Linear_ interpolator (degreeX, degreeY, sample);
					interpolator.evaluate();
					sample.setMode (Sampler_ :: Sample_ :: CONTROL);
					const Approximation_& approximation = interpolator.getApproximation();

					const Real approxMse = approximation.evalMSE();

					averageMse += approxMse;
					sample.setMode (Sampler_ :: Sample_ :: SAMPLE);
				}
				averageMse /= sampler.getCount();
				deviation_ [degreeX][degreeY] = averageMse;

				sample.setMode (Sampler_ :: Sample_ :: SAMPLE);
				Linear_ interpolator (degreeX, degreeY, sample);
				interpolator.evaluate();
				posDiagonalCoefficients_[degreeX][degreeY] =
					interpolator.getApproximation().diagonalCoefficientsArePositive();
				posCoefficients_[degreeX][degreeY] =
					interpolator.getApproximation().allCoefficientsArePositive();
				posDerivatives_[degreeX][degreeY] =
					interpolator.getApproximation().allDerivativesArePositive();
			}
		}
	}
}
}


