/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_interpolation_Approximation_2.hpp                   */
/* Description:     the 2 var. polynomial approximation to the given data    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "nstd/interpolation/nstd_interpolation_Polynomial_2.hpp"

namespace nstd {
namespace interpolation {

template<class A>
class Approximation<2, A> :
	public Object,
	public memory :: storage :: Scalar<Approximation<2, A>, A> {
public :
	typedef A Allocator_;
	typedef Sample<2, Allocator_> Sample_;
	typedef Polynomial<2, Allocator_> Polynomial_;

	Approximation (const Sample_& sample);
	Approximation
	(
		const Integer degreeX,
		const Integer degreeY,
		const Sample_& sample
	);
	Approximation (const Approximation&);
	virtual ~ Approximation();

	Polynomial_& polynomial();

	// SSE - Sum of Squared Errors
	Real evalSSE() const;
	// MSE — Mean Square Error
	Real evalMSE() const;

	// 1 dim representation
	Real evalDerivativeSSE (const Integer ij) const;
	// 2 dim representation
	Real evalDerivativeSSE (const Integer i, const Integer j) const;

	// 2 dim representation
	Integer getDegreeX() const;
	Integer getDegreeY() const;
	Real getCoefficient (const Integer, const Integer) const;
	Real& coefficient (const Integer, const Integer);

	// 1 dim representation
	Integer getDegreeXY() const;
	Real getCoefficient (const Integer) const;
	Real& coefficient (const Integer);

	bool diagonalCoefficientsArePositive() const;
	bool allCoefficientsArePositive() const;
	bool allDerivativesArePositive (const Integer precision = 1E-9) const;

	void operator = (const Approximation&);

	template<class S>
	void show (S&) const;

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String<>&) const;

private :
	bool allDerivativesArePositive (const char dir, const Integer precision = 1E-9) const;

	Polynomial_ polynomial_;
	const Sample_& sample_;
};

}
}


