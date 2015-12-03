/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_interpolation_Gradient_1.hpp                        */
/* Description:     the gradient method of 1 var interpolation evaluation    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_INTERPOLATION_GRADIENT_1_HPP_
#define NSTD_INTERPOLATION_GRADIENT_1_HPP_

namespace nstd {
namespace interpolation {

template<class A>
class Gradient<1, A>:
	public Object,
	public memory :: storage :: Scalar<Gradient<1, A>, A> {
public :
	typedef A Allocator_;
	typedef Sample<1, A> Sample_;
	typedef Polynomial<1, A> Polynomial_;
	typedef Approximation<1, A> Approximation_;

	Gradient
	(
		const Integer degreeX,
		const Sample_& sample,
		const bool keepPositive = true
	);
	virtual ~ Gradient();

	Polynomial_& evaluate (const Real epsilon = 0);
	const Approximation_& getApproximation() const;

	Integer iterationsRavine() const;
	Integer iterationsFirst() const;
	Integer iterationsSecond() const;

	template<class S>
	void show (S&) const;

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String<>&) const;

private :
	Real ravineMethod();
	Real gradientMethod (const Real epsilon);

	void quickestDescent (const Real gradient[]);
	void constShift (const Real gradient[]);
	void splittingShift (const Real gradient[]);

	const bool keepPositive_;

	const Integer degreeX_;
	const Integer dim_;
	const Sample_& sample_;

	Approximation_ a_zero_;
	Approximation_ a_plus_;
	Approximation_ a_minus_;
	Approximation_ a_prime_;

	Real epsilon_;

	Integer count_0_;
	Integer count_1_;
	Integer count_2_;

	Real stepGradient_;
	Real stepRavine_;
};

}
}

#endif /*NSTD_INTERPOLATION_GRADIENT_1_HPP_*/
