/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_equation_Linear.cpp                                 */
/* Description:     Gauss method of solving linear equations                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_EQUATION_LINEAR_CPP_
#define NSTD_EQUATION_LINEAR_CPP_

namespace nstd {
namespace equation {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	Linear<A> :: Linear
	(
		const Integer dim,
		const Real precision
	) :
	dim_ (dim),
	precision_ (precision),
	matrix_ (dim_),
	rightSide_ (dim_),
	m_ (dim_),
	b_ (dim_),
	x_ (dim_) {
	}
	template<class A>
	Linear<A> :: ~ Linear() {
	}

	template<class A>
	void
	Linear<A> :: solve ()
	{
		init();
		directPass();
		inversePass();
		#ifdef DEBUG_EQUATION_LINEAR
		if (!verify()) {
			std :: cout << "INCORRECT LINEAR EQUATION SOLUTION" << std :: endl;
		}
		#endif
	}
	template<class A>
	inline typename Linear<A> :: Matrix_&
	Linear<A> :: matrix() {
		return matrix_;
	}
	template<class A>
	inline typename Linear<A> :: Vector_&
	Linear<A> :: rightSide() {
		return rightSide_;
	}
	template<class A>
	inline Integer
	Linear<A> :: getDimension() const {
		return dim_;
	}
	template<class A>
	inline const typename Linear<A> :: Vector_&
	Linear<A> :: getSolution () const {
		return x_;
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: iterate;
using manipulator :: tab;

	template<class A>
	template<class S>
	void
	Linear<A> :: show (S& string) const
	{
		string << "matrix:" << endLine;
		for (int i = 0; i < dim_; ++ i) {
			const Vector_* row = matrix_.getValue (i);
			string << tab;
			for (int j = 0; j < dim_; ++ j) {
				const Real a_i_j = row->getValue (j);
				string << a_i_j << "*x_" << j << "(=" << x_[j] << ")";
				if (j + 1 < dim_) {
					string << " + ";
				}
			}
			string << " = " << rightSide_ [i] << endLine;
		}
		string << endLine;

		string << "m:" << endLine;
		for (int i = 0; i < dim_; ++ i) {
			const Vector_* row = m_.getValue (i);
			string << tab;
			for (int j = 0; j < dim_; ++ j) {
				const Real a_i_j = row->getValue (j);
				string << a_i_j << "*x_" << j << "(=" << x_[j] << ")";
				if (j + 1 < dim_) {
					string << " + ";
				}
			}
			string << " = " << b_ [i] << endLine;
		}
		string << endLine;
	}

	// nstd :: Object implementation
	template<class A>
	void
	Linear<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Linear<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += matrix_.getVolume();
		volume += rightSide_.getVolume();

		volume += m_.getVolume();
		volume += b_.getVolume();
		volume += x_.getVolume();
		return volume;
	}
	template<class A>
	Size_t
	Linear<A> :: getSizeOf() const {
		return sizeof (Linear);
	}
	template<class A>
	void
	Linear<A> :: show (String<>& string) const {
		show<String<> >(string);
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	void
	Linear<A> :: init()
	{
		initMatrix();
		initRightSide();
		initX();
	}
	template<class A>
	void
	Linear<A> :: initMatrix()
	{
		for (int i = 0; i < dim_; ++ i) {
			Vector_* rowSource = matrix_.getValue (i);
			Vector_* rowTarget = m_.push();
			for (int j = 0; j < dim_; ++ j) {
				const Real a_i_j = rowSource->getValue (j);
				rowTarget->add (a_i_j);
			}
		}
	}
	template<class A>
	void
	Linear<A> :: initRightSide()
	{
		for (int i = 0; i < dim_; ++ i) {
			const Real b_i = rightSide_.getValue (i);
			b_.add (b_i);
		}
	}
	template<class A>
	void
	Linear<A> :: initX()
	{
		for (int i = 0; i < dim_; ++ i) {
			x_.add (0);
		}
	}

	template<class A>
	void
	Linear<A> :: directPass()
	{
		for (int i = 0; i < dim_ - 1; ++ i) {
			for (int j = i; j < dim_ - 1; ++ j) {
				const double M = - (*m_ [j + 1]) [i] / (*m_ [i])[i];
				for (int k = i; k < dim_; ++ k) {
					(*m_ [j + 1]) [k] += M * ((*m_ [i])[k]);
					const double a = fabs ((*m_ [j + 1]) [k]);
					if (a < precision_) {
						(*m_ [j + 1]) [k] = 0;
					}
				}
				b_ [j + 1] += b_ [i] * M;
			}
		}
	}
	template<class A>
	void
	Linear<A> :: inversePass()
	{
		for (int k = 0; k < dim_; ++ k) {
			const int i = dim_ - k - 1;
			x_ [i] = b_ [i];
			for (int j = dim_ - 1; j > i; -- j) {
				x_ [i] -= x_ [j] * (*m_ [i]) [j];
			}
			x_ [i] /= (*m_ [i]) [i];
		}
	}

	template<class A>
	bool
	Linear<A> :: verify()
	{
		for (int i = 0; i < dim_; ++ i) {
			Real c = 0;
			const Vector_* row = matrix_.getValue (i);
			for (int j = 0; j < dim_; ++ j) {
				const Real a_i_j = row->getValue (j);
				c += a_i_j * x_ [j];
			}
			const Real
				delta = fabs (c - rightSide_ [i]);
			if (delta > 2 * precision_) {
				std :: cout << "deviation = " << delta << std :: endl;
				return false;
			}
		}
		return true;
	}
}
}

#endif /*NSTD_EQUATION_LINEAR_CPP_*/
