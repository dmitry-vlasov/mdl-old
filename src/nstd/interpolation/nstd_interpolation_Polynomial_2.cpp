/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_interpolation_Polynomial_2.cpp                      */
/* Description:     the polynomial of two variables class                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_INTERPOLATION_POLYNOMIAL_2_CPP_
#define NSTD_INTERPOLATION_POLYNOMIAL_2_CPP_

namespace nstd {
namespace interpolation {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	Polynomial<2, A> :: Polynomial () :
	degreeX_ (0),
	degreeY_ (0),
	coefficient_() {
	}
	template<class A>
	Polynomial<2, A> :: Polynomial (const char* str) :
	degreeX_ (0),
	degreeY_ (0),
	coefficient_()
	{
		const int length = strlen (str);
		char string [length + 1];
		for (int i = 0; i < length; ++ i) {
			string [i] = str [i];
		}
		string [length] = chars :: NULL_CHAR;
		parse (string, str);
	}
	template<class A>
	Polynomial<2, A> :: Polynomial (const Integer degreeX, const Integer degreeY) :
	degreeX_ (degreeX),
	degreeY_ (degreeY),
	coefficient_ () {
	}
	template<class A>
	Polynomial<2, A> :: Polynomial (const Polynomial& polynomial) :
	degreeX_ (polynomial.degreeX_),
	degreeY_ (polynomial.degreeY_),
	coefficient_ ()
	{
		for (Integer i = 0; i <= degreeX_; ++ i) {
			for (Integer j = 0; j <= degreeY_; ++ j) {
				coefficient_ [i][j] = polynomial.coefficient_ [i][j];
			}
		}
	}
	template<class A>
	Polynomial<2, A> :: ~ Polynomial() {
	}

	// conversion between 1 dim and 2 dim representation of coefficients
	template<class A>
	inline Integer
	Polynomial<2, A> :: convXY (const Integer i, const Integer j) const {
		return i * (degreeX_ + 1) + j;
	}
	template<class A>
	inline Integer
	Polynomial<2, A> :: convX (const Integer ij) const {
		return ij / (degreeX_ + 1);
	}
	template<class A>
	inline Integer
	Polynomial<2, A> :: convY (const Integer ij) const {
		return ij % (degreeX_ + 1);
	}

	// 2 dim representation of coefficients
	template<class A>
	inline Integer
	Polynomial<2, A> :: getDegreeX() const {
		return degreeX_;
	}
	template<class A>
	inline Integer
	Polynomial<2, A> :: getDegreeY() const {
		return degreeY_;
	}
	template<class A>
	inline Real
	Polynomial<2, A> :: getCoefficient (const Integer i, const Integer j) const {
		return coefficient_ [i][j];
	}
	template<class A>
	inline Real&
	Polynomial<2, A> :: coefficient (const Integer i, const Integer j) {
		return coefficient_ [i][j];
	}

	// 1 dim representation of coefficients
	template<class A>
	inline Integer
	Polynomial<2, A> :: getDegreeXY() const {
		return degreeX_ * degreeY_;
	}
	template<class A>
	inline Real
	Polynomial<2, A> :: getCoefficient (const Integer ij) const
	{
		const Integer i = convX (ij);
		const Integer j = convY (ij);
		return coefficient_ [i][j];
	}
	template<class A>
	inline Real&
	Polynomial<2, A> :: coefficient (const Integer ij)
	{
		const Integer i = convX (ij);
		const Integer j = convY (ij);
		return coefficient_ [i][j];
	}

	template<class A>
	Real
	Polynomial<2, A> :: eval (const Real x, const Real y) const
	{
		Real sum = 0;
		for (Integer i = 0; i <= degreeX_; ++ i) {
			const Real a = pow (x, i);
			for (Integer j = 0; j <= degreeY_; ++ j) {
				const Real b = pow (y, j);
				sum += coefficient_ [i][j] * a * b;
			}
		}
		return sum;
	}

	template<class A>
	void
	Polynomial<2, A> :: operator = (const Polynomial& polynomial)
	{
		degreeX_ = polynomial.degreeX_;
		degreeY_ = polynomial.degreeY_;
		for (Integer i = 0; i <= degreeX_; ++ i) {
			for (Integer j = 0; j <= degreeY_; ++ j) {
				coefficient_ [i][j] = polynomial.coefficient_ [i][j];
			}
		}
	}

	// works only for 1 dim representation
	template<class A>
	void
	Polynomial<2, A> :: addVector (const Real vector[], const bool keepPositive)
	{
		for (Integer ij = 0; ij <= getDegreeXY(); ++ ij) {
			coefficient (ij) += vector [ij];
			if (keepPositive && (coefficient (ij) < 0)) {
				coefficient (ij) = 0;
			}
		}
	}
	template<class A>
	void
	Polynomial<2, A> :: subVector (const Real vector[], const bool keepPositive)
	{
		for (Integer ij = 0; ij <= getDegreeXY(); ++ ij) {
			coefficient (ij) -= vector [ij];
			if (keepPositive && (coefficient (ij) < 0)) {
				coefficient (ij) = 0;
			}
		}
	}

	template<class A>
	Polynomial<2, A>*
	Polynomial<2, A> :: derivateX() const
	{
		Polynomial* d = NULL;
		if (degreeX_ == 0) {
			d = new Polynomial (0,0);
		} else {
			d = new Polynomial (degreeX_ - 1, degreeY_);
			for (Integer i = 0; i <= degreeX_ - 1; ++ i) {
				for (Integer j = 0; j <= degreeY_; ++ j) {
					d->coefficient (i ,j) = coefficient_ [i + 1][j] * (i + 1);
				}
			}
		}
		return d;
	}
	template<class A>
	Polynomial<2, A>*
	Polynomial<2, A> :: derivateY() const
	{
		Polynomial* d = NULL;
		if (degreeY_ == 0) {
			d = new Polynomial (0,0);
		} else {
			d = new Polynomial (degreeX_, degreeY_ - 1);
			for (Integer i = 0; i <= degreeX_; ++ i) {
				for (Integer j = 0; j < degreeY_ - 1; ++ j) {
					d->coefficient (i ,j) = coefficient_ [j][j + 1] * (j + 1);
				}
			}
		}
		return d;
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: iterate;
using manipulator :: tab;

	template<class A>
	template<class S>
	void
	Polynomial<2, A> :: show
	(
		S& string,
		const bool plain,
		const int indent
	) const
	{
		// format of polynomial:
		// p(x,y)=[-0.00965922]*x^0*y^1+[0.00955268]*x^1*y^2+[0.0268]*x^2*y^3
		// EBNF:  p(x,y)=[<factor>]*x^<degree>*y^<degree>{+[<factor>]*x^<degree>*y^<degree>}

		if (plain) {
			string << "p(x,y)=";
		} else {
			string << iterate << indent << tab;
			string << "p(x,y)=";
			string << endLine;
		}
		for (Integer i = 0; i <= degreeX_; ++ i) {
			if (!plain) {
				string << iterate << indent << tab;
			}
			for (Integer j = 0; j <= degreeY_; ++ j) {
				string << "[" << coefficient_ [i][j] << "]";
				string << "*x^" << i;
				string << "*y^" << j;
				if ((i < degreeX_) || (j < degreeY_)) {
					string << "+";
				}
			}
			if (!plain) {
				string << endLine;
			}
		}
	}

	// Object implementation
	template<class A>
	void
	Polynomial<2, A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Polynomial<2, A> :: getVolume() const
	{
		Size_t volume = 0;
		return volume;
	}
	template<class A>
	Size_t
	Polynomial<2, A> :: getSizeOf() const {
		return sizeof (Polynomial);
	}
	template<class A>
	void
	Polynomial<2, A> :: show (String<>& string) const {
		show<String<> >(string);
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	void
	Polynomial<2, A> :: parse (char* c, const char* string)
	{
		// format of polynomial:
		// p(x,y)=[-0.00965922]*x^0*y^1+[0.00955268]*x^1*y^2+[0.0268]*x^2*y^3
		// EBNF:  p(x,y)=[<factor>]*x^<degree>*y^<degree>{+[<factor>]*x^<degree>*y^<degree>}

		degreeX_ = 0;
		degreeY_ = 0;
		bool error = false;
		if (Polynomial<1, Allocator_> :: parseString (c, "p(x,y)=")) {
			while (true) {
				Real value = Polynomial<1, Allocator_> :: parseCoefficient (c, error);
				if (!Polynomial<1, Allocator_> :: parseString (c, "*x^")) {
					error = true;
					break;
				}
				Integer degreeX = Polynomial<1, Allocator_> :: parseDegree (c, error);
				if (*c != '*') {
					error = true;
					break;
				}
				if (!Polynomial<1, Allocator_> :: parseString (c, "*y^")) {
					error = true;
					break;
				}
				Integer degreeY = Polynomial<1, Allocator_> :: parseDegree (c, error);

				if (coefficient_ [degreeX][degreeY] != 0) {
					error = true;
					break;
				} else {
					coefficient_ [degreeX][degreeY] = value;
				}
				if (degreeX_ < degreeX) {
					degreeX_ = degreeX;
				}
				if (degreeY_ < degreeY) {
					degreeY_ = degreeY;
				}
				if (*c == '+') {
					++ c;
				} else if (*c == chars :: NULL_CHAR) {
					break;
				} else {
					error = true;
					break;
				}
			}
		} else {
			error = true;
		}
		if (error) {
			parsingError (string);
		}
	}

	template<class A>
	void
	Polynomial<2, A> :: parsingError (const char* string)
	{
		std :: cout << std :: endl;
		std :: cout << "incorrect polynomial format: " << string << std :: endl;
		std :: cout << "time should be like: " << std :: endl;
		std :: cout << "\tp(x)=[-0.00965922]*x^0+[0.00955268*]*x^1+[0.0268]*x^2+[9.55268]*x^3" << std :: endl;
	}
}
}

#endif /*NSTD_INTERPOLATION_POLYNOMIAL_2_CPP_*/
