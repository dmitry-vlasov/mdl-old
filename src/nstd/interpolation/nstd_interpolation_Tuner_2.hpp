/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_interpolation_Tuner_2.hpp                           */
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

template<class A>
class Tuner<2, A> :
	public Object,
	public memory :: storage :: Scalar<Tuner<2, A>, A> {
public :
	typedef A Allocator_;
	typedef Polynomial<2, A> Polynomial_;
	typedef
		typename container :: Vector
		<
			Real,
			container :: storage :: ByValue,
			Allocator_
		>
		RealVector_;

	Tuner
	(
		const bool diagonalCoefficientsArePositive = true,
		const bool allCoefficientsArePositive = false,
		const bool allDerivativesArePositive = false
	);
	Tuner
	(
		const RealVector_& xVector,
		const RealVector_& yVector,
		const RealVector_& zVector,
		const bool diagonalCoefficientsArePositive = true,
		const bool allCoefficientsArePositive = false,
		const bool allDerivativesArePositive = false
	);
	virtual ~ Tuner();

	Polynomial_* evalOptimalPolynomial();
	Polynomial_* evalPolynomialOfDegree
	(
		const Integer degreeX,
		const Integer degreeY
	);
	Real getMse() const;

	void setData
	(
		const RealVector_& xVector,
		const RealVector_& yVector,
		const RealVector_& zVector
	);

	template<class S>
	void show (S&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String<>&) const;

private :
	enum {
		MAX_DEGREE = 3,
		INITIAL_VECTOR_CAPACITY = 256
	};

	typedef	Sample<2, Allocator_> Sample_;
	typedef Linear<2, Allocator_> Linear_;
	typedef Approximation<2, Allocator_> Approximation_;
	typedef
		typename sampler :: Sampler<Allocator_>
		Sampler_;

	Real findOptimalDegree (Integer& optimalDegreeX, Integer& optimalDegreeY) const;
	void crossValidation();

	const bool diagonalCoefficientsArePositive_;
	const bool allCoefficientsArePositive_;
	const bool allDerivativesArePositive_;

	RealVector_ xVector_;
	RealVector_ yVector_;
	RealVector_ zVector_;

	Real deviation_[MAX_DEGREE][MAX_DEGREE];
	Bool posDiagonalCoefficients_ [MAX_DEGREE][MAX_DEGREE];
	Bool posCoefficients_ [MAX_DEGREE][MAX_DEGREE];
	Bool posDerivatives_ [MAX_DEGREE][MAX_DEGREE];

	Real mse_;
};

}
}


