/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_interpolation_Tuner_1.hpp                           */
/* Description:     the tuner for 1 dim. interpolator class                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_INTERPOLATION_TUNER_1_HPP_
#define NSTD_INTERPOLATION_TUNER_1_HPP_

namespace nstd {
namespace interpolation {

template<class A>
class Tuner<1, A> :
	public Object,
	public memory :: storage :: Scalar<Tuner<1, A>, A> {
public :
	typedef A Allocator_;
	typedef Polynomial<1, A> Polynomial_;
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
		const bool allCoefficientsArePositive = true,
		const bool allDerivativesArePositive = true
	);
	Tuner
	(
		const RealVector_& xVector,
		const RealVector_& yVector,
		const bool allCoefficientsArePositive = true,
		const bool allDerivativesArePositive = true
	);
	virtual ~ Tuner();

	Polynomial_* evalOptimalPolynomial();
	Polynomial_* evalPolynomialOfDegree (const Integer degreeX);
	Real getMse() const;

	void setData
	(
		const RealVector_& xVector,
		const RealVector_& yVector
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
		MAX_DEGREE = 5,
		INITIAL_VECTOR_CAPACITY = 256
	};

	typedef	Sample<1, Allocator_> Sample_;
	typedef Linear<1, Allocator_> Linear_;
	typedef Approximation<1, Allocator_> Approximation_;
	typedef
		typename sampler :: Sampler<Allocator_>
		Sampler_;

	Real findOptimalDegree (Integer& optimaDegreeX) const;
	void crossValidation();

	const bool allCoefficientsArePositive_;
	const bool allDerivativesArePositive_;

	RealVector_ xVector_;
	RealVector_ yVector_;

	Real deviation_ [MAX_DEGREE];
	Bool posCoefficients_ [MAX_DEGREE];
	Bool posDerivatives_ [MAX_DEGREE];

	Real mse_;
};

}
}

#endif /*NSTD_INTERPOLATION_TUNER_1_HPP_*/
