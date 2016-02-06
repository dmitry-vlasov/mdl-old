/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_interpolation_Polynomial_1.cpp                      */
/* Description:     the polynomial of one variable class                     */
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

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	Polynomial<1, A> :: Polynomial () :
	degreeX_ (0),
	coefficient_() {
	}
	template<class A>
	Polynomial<1, A> :: Polynomial (const char* str) :
	degreeX_ (0),
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
	Polynomial<1, A> :: Polynomial (const Integer degree) :
	degreeX_ (degree),
	coefficient_ ()
	{
		for (Integer i = 0; i <= degreeX_; ++ i) {
			coefficient_ [i] = 0;
		}
	}
	template<class A>
	Polynomial<1, A> :: Polynomial (const Polynomial& polynomial) :
	degreeX_ (polynomial.degreeX_),
	coefficient_ () {
		for (Integer i = 0; i <= degreeX_; ++ i) {
			coefficient_ [i] = polynomial.coefficient_ [i];
		}
	}
	template<class A>
	Polynomial<1, A> :: ~ Polynomial() {
	}

	template<class A>
	inline Integer
	Polynomial<1, A> :: getDegreeX() const {
		return degreeX_;
	}
	template<class A>
	inline Real
	Polynomial<1, A> :: getCoefficient (const Integer i) const {
		return coefficient_ [i];
	}
	template<class A>
	inline Real&
	Polynomial<1, A> :: coefficient (const Integer i) {
		return coefficient_ [i];
	}

	template<class A>
	Real
	Polynomial<1, A> :: eval (const Real x) const
	{
		Real sum = 0;
		for (Integer i = 0; i <= degreeX_; ++ i) {
			const Real a = pow (x, i);
			sum += coefficient_ [i] * a;
		}
		return sum;
	}

	template<class A>
	void
	Polynomial<1, A> :: operator = (const Polynomial& polynomial)
	{
		degreeX_ = polynomial.degreeX_;
		for (Integer i = 0; i <= degreeX_; ++ i) {
			coefficient_ [i] = polynomial.coefficient_ [i];
		}
	}
	template<class A>
	void
	Polynomial<1, A> :: addVector (const Real vector[], const bool keepPositive)
	{
		for (Integer i = 0; i <= degreeX_; ++ i) {
			coefficient_ [i] += vector [i];
			if (keepPositive && (i > 0) && (coefficient_ [i] < 0)) {
				coefficient_ [i] = 0;
			}
		}
	}
	template<class A>
	void
	Polynomial<1, A> :: subVector (const Real vector[], const bool keepPositive)
	{
		for (Integer i = 0; i <= degreeX_; ++ i) {
			coefficient_ [i] -= vector [i];
			if (keepPositive && (i > 0) && (coefficient_ [i] < 0)) {
				coefficient_ [i] = 0;
			}
		}
	}

	template<class A>
	Polynomial<1, A>*
	Polynomial<1, A> :: derivateX() const
	{
		Polynomial* d = NULL;
		if (degreeX_ == 0) {
			d = new Polynomial();
		} else {
			d = new Polynomial (degreeX_ - 1);
			for (Integer i = 0; i < degreeX_; ++ i) {
				d->coefficient (i) = coefficient_ [i + 1] * (i + 1);
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
	Polynomial<1, A> :: show (S& string) const
	{
		// format of polynomial:
		// p(x)=[-0.00965922]*x^0+[0.00955268*]*x^1+[0.0268]*x^2+[9.55268]*x^3
		// EBNF:  p(x)=[<factor>]^<degree>{+[<factor>]^<degree>}

		string << "p(x)=";
		const Integer greatestDegree = greatestNonZeroDegree();
		if (greatestDegree == Undefined<Integer> :: getValue()){
			string << "[0]*x^0";
		} else {
			for (Integer i = 0; i <= greatestDegree; ++ i) {
				if (coefficient_ [i] == 0) {
					continue;
				}
				string << "[" << coefficient_ [i] << "]*x^" << i;
				if (i < greatestDegree) {
					string << "+";
				}
			}
		}
	}

	// Object implementation
	template<class A>
	void
	Polynomial<1, A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Polynomial<1, A> :: getVolume() const
	{
		Size_t volume = 0;
		return volume;
	}
	template<class A>
	Size_t
	Polynomial<1, A> :: getSizeOf() const {
		return sizeof (Polynomial);
	}
	template<class A>
	void
	Polynomial<1, A> :: show (String<>& string) const {
		show<String<> >(string);
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	void
	Polynomial<1, A> :: parse (char* c, const char* string)
	{
		// format of polynomial:
		// p(x)=[-0.00965922]*x^0+[0.00955268*]*x^1+[0.0268]*x^2+[9.55268]*x^3
		// EBNF:  p(x)=[<factor>]*x^<degree>{+[<factor>]*x^<degree>}

		degreeX_ = 0;
		bool error = false;
		if (parseString (c, "p(x)=")) {
			while (true) {
				Real value = parseCoefficient (c, error);
				if (!parseString (c, "*x^")) {
					error = true;
					break;
				}
				Integer degree = parseDegree (c, error);
				if (coefficient_ [degree] != 0) {
					error = true;
					break;
				} else {
					coefficient_ [degree] = value;
				}
				if (degreeX_ < degree) {
					degreeX_ = degree;
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
	Real
	Polynomial<1, A> :: parseCoefficient (char*& end, bool& error)
	{

		if (*end ++ != '[') {
			error = true;
			return 0;
		}
		char* beg = end;
		while (*end != ']') {
			++ end;
		}
		const char delimiter = *end;
		*end = chars :: NULL_CHAR;
		Real coefficient = 0;
		if (sscanf (beg, "%lf", &coefficient) == 0) {
			error = true;
		}
		*end = delimiter;
		if (delimiter != chars :: NULL_CHAR) {
			++ end;
		}
		return coefficient;
	}
	template<class A>
	Integer
	Polynomial<1, A> :: parseDegree (char*& end, bool& error)
	{
		char* beg = end;
		while (('0' <= *end) && (*end <= '9')) {
			++ end;
		}
		const char delimiter = *end;
		*end = chars :: NULL_CHAR;
		Integer degree = 0;
		if (sscanf (beg, "%d", &degree) == 0) {
			error = true;
		}
		*end = delimiter;
		return degree;
	}

	template<class A>
	bool
	Polynomial<1, A> :: parseString
	(
		char*& c_1,
		const char* c_2
	)
	{
		bool result = true;
		while (true){
			if (*c_1 == chars :: NULL_CHAR) {
				result = false;
				break;
			}
			if (*c_2 == chars :: NULL_CHAR) {
				result = true;
				break;
			}
			if (*c_1 != *c_2) {
				result = false;
				break;
			}
			++ c_1;
			++ c_2;
		}
		return result;
	}

	template<class A>
	void
	Polynomial<1, A> :: parsingError (const char* string)
	{
		std :: cout << std :: endl;
		std :: cout << "incorrect polynomial format: " << string << std :: endl;
		std :: cout << "time should be like: " << std :: endl;
		std :: cout << "\tp(x)=[-0.00965922]*x^0+[0.00955268*]*x^1+[0.0268]*x^2+[9.55268]*x^3" << std :: endl;
	}

	template<class A>
	Integer
	Polynomial<1, A> :: greatestNonZeroDegree() const
	{
		for (Integer i = 0; i <= degreeX_; ++ i) {
			const Integer j = degreeX_ - i;
			if (coefficient_ [j] != 0) {
				return j;
			}
		}
		return Undefined<Integer> :: getValue();
	}
}
}


