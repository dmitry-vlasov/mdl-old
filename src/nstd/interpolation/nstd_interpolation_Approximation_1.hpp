/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_interpolation_Approximation_1.hpp                   */
/* Description:     the 1 var. polynomial approximation to the given data    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_INTERPOLATION_APPROXIMATION_1_HPP_
#define NSTD_INTERPOLATION_APPROXIMATION_1_HPP_

#include "nstd/interpolation/nstd_interpolation_Polynomial_1.hpp"

namespace nstd {
namespace interpolation {

template<class A>
class Approximation<1, A> :
	public Object,
	public memory :: storage :: Scalar<Approximation<1, A>, A> {
public :
	typedef A Allocator_;
	typedef Sample<1, Allocator_> Sample_;
	typedef Polynomial<1, Allocator_> Polynomial_;

	Approximation
	(
		const Integer degreeX,
		const Sample_& sample
	);
	Approximation (const Approximation&);
	virtual ~ Approximation();

	Polynomial_& polynomial();

	// SSE - Sum of Squared Errors
	Real evalSSE() const;
	// MSE — Mean Square Error
	Real evalMSE() const;

	Real evalDerivativeSSE (const Integer) const;

	Integer getDegreeX() const;
	Real getCoefficient (const Integer) const;
	Real& coefficient (const Integer);

	bool allCoefficientsArePositive() const;
	bool allDerivativesArePositive (const Integer precision = 1E-9) const;

	void operator = (const Approximation&);;

	template<class S>
	void show (S&) const;

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String<>&) const;

private :
	Polynomial_ polynomial_;
	const Sample_& sample_;
};

}
}

#endif /*NSTD_INTERPOLATION_APPROXIMATION_1_HPP_*/
