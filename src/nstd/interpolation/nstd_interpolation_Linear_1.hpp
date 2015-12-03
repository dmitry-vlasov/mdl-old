/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_interpolation_Linear_1.hpp                          */
/* Description:     Linear method of 1 variable interpolation evaluation     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_INTERPOLATION_LINEAR_1_HPP_
#define NSTD_INTERPOLATION_LINEAR_1_HPP_

namespace nstd {
namespace interpolation {

template<class A>
class Linear<1, A> :
	public Object,
	public memory :: storage :: Scalar<Linear<1, A>, A> {
public :
	typedef A Allocator_;
	typedef Sample<1, A> Sample_;
	typedef Polynomial<1, A> Polynomial_;
	typedef Approximation<1, A> Approximation_;

	Linear
	(
		const Integer degree,
		const Sample_& sample,
		const Real precision = 1E-9
	);
	virtual ~ Linear();

	const Polynomial_& evaluate();
	const Approximation_& getApproximation() const;

	template<class S>
	void show (S&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String<>&) const;

private :
	typedef
		typename equation :: Linear<Allocator_>
		Solver_;

	void initMatrix();
	void initRightSide();

	const Sample_& sample_;
	Approximation_ a_;
	Solver_ solver_;
};

}
}

#endif /*NSTD_INTERPOLATION_LINEAR_1_HPP_*/
