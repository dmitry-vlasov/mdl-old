/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_equation_Linear.hpp                                 */
/* Description:     Gauss method of solving linear equations                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {
namespace equation {

template<class A>
class Linear :
	public Object,
	public memory :: storage :: Scalar<Linear<A>, A> {
public :
	typedef A Allocator_;
	typedef
		container :: Vector
		<
			Real,
			container :: storage :: ByValue,
			Allocator_
		>
		Vector_;
	typedef
		container :: Vector
		<
			Vector_,
			container :: storage :: ByPointer,
			Allocator_
		>
		Matrix_;

	Linear
	(
		const Integer dim,
		const Real precision = 1E-9
	);
	virtual ~ Linear();

	void solve();
	Matrix_& matrix();
	Vector_& rightSide();
	Integer getDimension() const;
	const Vector_& getSolution () const;

	template<class S>
	void show (S&) const;

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String<>&) const;

private :
	void init();
	void initMatrix();
	void initRightSide();
	void initX();

	void directPass();
	void inversePass();
	bool verify();

	const Integer dim_;
	const Real precision_;

	Matrix_ matrix_;
	Vector_ rightSide_;

	Matrix_ m_;
	Vector_ b_;
	Vector_ x_;
};

}
}


