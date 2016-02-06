/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_interpolation_Tuner_1.cpp                           */
/* Description:     the tuner for 1 dim. interpolator class                  */
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
	Tuner<1, A> :: Tuner
	(
		const bool allCoefficientsArePositive,
		const bool allDerivativesArePositive
	) :
	allCoefficientsArePositive_ (allCoefficientsArePositive),
	allDerivativesArePositive_ (allDerivativesArePositive),
	xVector_ (INITIAL_VECTOR_CAPACITY),
	yVector_ (INITIAL_VECTOR_CAPACITY),
	deviation_ (),
	posDerivatives_ (),
	posCoefficients_ (),
	mse_ (0) {
	}
	template<class A>
	Tuner<1, A> :: Tuner
	(
		const RealVector_& xVector,
		const RealVector_& yVector,
		const bool allCoefficientsArePositive,
		const bool allDerivativesArePositive
	) :
	allCoefficientsArePositive_ (allCoefficientsArePositive),
	allDerivativesArePositive_ (allDerivativesArePositive),
	xVector_ (xVector),
	yVector_ (yVector),
	deviation_ (),
	posDerivatives_ (),
	posCoefficients_ (),
	mse_ (0) {
	}
	template<class A>
	Tuner<1, A> :: ~ Tuner() {
	}

	template<class A>
	typename Tuner<1, A> :: Polynomial_*
	Tuner<1, A> :: evalOptimalPolynomial()
	{
		crossValidation();
		Integer optimalDegreeX = 0;
		findOptimalDegree (optimalDegreeX);
		Sample_ sample (xVector_, yVector_);
		Linear_ interpolator (optimalDegreeX, sample);
		const Polynomial_& result = interpolator.evaluate();
		Polynomial_* polynomial = new Polynomial<1, Allocator_> (result);
		mse_ = interpolator.getApproximation().evalMSE();
		return polynomial;
	}
	template<class A>
	typename Tuner<1, A> :: Polynomial_*
	Tuner<1, A> :: evalPolynomialOfDegree (const Integer degreeX)
	{
		Sample_ sample (xVector_, yVector_);
		Linear_ interpolator (degreeX, sample);
		const Polynomial_& result = interpolator.evaluate();
		Polynomial_* polynomial = new Polynomial_ (result);
		mse_ = interpolator.getApproximation().evalMSE();
		return polynomial;
	}
	template<class A>
	inline Real
	Tuner<1, A> :: getMse() const {
		return mse_;
	}
	template<class A>
	void
	Tuner<1, A> :: setData
	(
		const RealVector_& xVector,
		const RealVector_& yVector
	)
	{
		xVector_.copy (xVector);
		yVector_.copy (yVector);
		mse_ = 0;
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: iterate;
using manipulator :: tab;

	template<class A>
	template<class S>
	void
	Tuner<1, A> :: show (S& string) const
	{
		Integer optimalDegreeX = 0;
		findOptimalDegree (optimalDegreeX);
		string << "optimal degree = " << optimalDegreeX << endLine;
		string << "MSE / degree dependency: " << endLine;
		string << "----------------" << endLine;
		for (Integer degreeX = 0; degreeX < MAX_DEGREE; ++ degreeX) {
			const Real mse = deviation_ [degreeX];
			string << tab;
			string << "dX = " << degreeX << ", ";
			string << "mse = " << mse << ", ";
			if (posDerivatives_ [degreeX]) {
				string << "sign = (+), ";
			} else {
				string << "sign = (+/-), ";
			}
			if (degreeX > 0) {
				const Real msePrev = deviation_ [degreeX - 1];
				const Real delta = msePrev - mse;
				string << "delta = " << delta << ", ";
				const Real factor = mse / delta;
				string << "factor = " << factor << ", ";
			}
			string << endLine;
		}
		string << endLine;
		string << endLine;
	}


	// nstd :: Object implementation
	template<class A>
	void
	Tuner<1, A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Tuner<1, A> :: getVolume() const
	{
		Size_t volume = 0;
		return volume;
	}
	template<class A>
	Size_t
	Tuner<1, A> :: getSizeOf() const {
		return sizeof (Tuner);
	}
	template<class A>
	void
	Tuner<1, A> :: show (String<>& string) const {
		show<String<> >(string);
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	Real
	Tuner<1, A> :: findOptimalDegree (Integer& optimalDegreeX) const
	{
		Real minDeviation = 0;

		for (Integer degreeX = 0; degreeX < MAX_DEGREE; ++ degreeX) {
			if ((degreeX > 0) &&
				allCoefficientsArePositive_ &&
				!posCoefficients_ [degreeX]) {
				continue;
			}
			if ((degreeX > 0) &&
				allDerivativesArePositive_ &&
				!posDerivatives_ [degreeX]) {
				continue;
			}
			const Real mse = deviation_ [degreeX];
			if ((degreeX == 0) || (minDeviation > mse)) {
				minDeviation = mse;
				optimalDegreeX = degreeX;
			}
		}
		return minDeviation;
	}

	template<class A>
	void
	Tuner<1, A> :: crossValidation()
	{
		Sample_  sample (xVector_, yVector_);
		Sampler_ sampler (xVector_.getSize());

		for (Integer degreeX = 0; degreeX < MAX_DEGREE; ++ degreeX) {
			Real averageMse = 0;
			sampler.reset();
			while (sampler.generate (degreeX + 1)) {
				sample.set (sampler.getSample());
				sample.setMode (Sampler_ :: Sample_ :: LEARNING);
				Linear_ interpolator (degreeX, sample);
				interpolator.evaluate();
				sample.setMode (Sampler_ :: Sample_ :: CONTROL);
				const Approximation_& approximation = interpolator.getApproximation();
				const Real approxMse = approximation.evalMSE();
				averageMse += approxMse;
				sample.setMode (Sampler_ :: Sample_ :: SAMPLE);
			}
			averageMse /= sampler.getCount();
			deviation_ [degreeX] = averageMse;

			sample.setMode (Sampler_ :: Sample_ :: SAMPLE);
			Linear_ interpolator (degreeX, sample);
			interpolator.evaluate();
			posCoefficients_ [degreeX] = interpolator.getApproximation().allCoefficientsArePositive();
			posDerivatives_ [degreeX] = interpolator.getApproximation().allDerivativesArePositive();
		}
	}
}
}


