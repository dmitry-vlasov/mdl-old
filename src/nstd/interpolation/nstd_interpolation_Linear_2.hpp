/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_interpolation_Linear_2.hpp                          */
/* Description:     Linear method of 2 variable interpolation evaluation     */
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
class Linear<2, A> :
	public Object,
	public memory :: storage :: Scalar<Linear<2, A>, A> {
public :
	typedef A Allocator_;
	typedef Sample<2, A> Sample_;
	typedef Polynomial<2, A> Polynomial_;
	typedef Approximation<2, A> Approximation_;

	Linear
	(
		const Integer degreeX,
		const Integer degreeY,
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

	Integer convXY (const Integer, const Integer) const;
	Integer convX (const Integer) const;
	Integer convY (const Integer) const;

	const Integer degreeX_;
	const Integer degreeY_;
	const Integer dimX_;
	const Integer dimY_;

	const Sample_& sample_;
	Approximation_ a_;
	Solver_ solver_;
};

}
}


