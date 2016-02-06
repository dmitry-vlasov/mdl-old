/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_interpolation_Polynomial_2.hpp                      */
/* Description:     the polynomial of two variables class                    */
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
class Polynomial<2, A> :
	public Object,
	public memory :: storage :: Scalar<Polynomial<2, A>, A> {
public :
	typedef A Allocator_;
	enum {
		MAX_DEGREE = 5
	};

	Polynomial ();
	Polynomial (const char*);
	Polynomial (const Integer degreeX, const Integer degreeY);
	Polynomial (const Polynomial&);
	virtual ~ Polynomial();

	// conversion between 1 dim and 2 dim representation of coefficients
	Integer convXY (const Integer, const Integer) const;
	Integer convX (const Integer) const;
	Integer convY (const Integer) const;

	// 2 dim representation of coefficients
	Integer getDegreeX() const;
	Integer getDegreeY() const;
	Real getCoefficient (const Integer, const Integer) const;
	Real& coefficient (const Integer, const Integer);

	// 1 dim representation of coefficients
	Integer getDegreeXY() const;
	Real getCoefficient (const Integer) const;
	Real& coefficient (const Integer);

	Real eval (const Real, const Real) const;

	void operator = (const Polynomial&);

	// works only for 1 dim representation
	void addVector (const Real [], const bool keepPositive = false);
	void subVector (const Real [], const bool keepPositive = false);

	Polynomial* derivateX() const;
	Polynomial* derivateY() const;

	template<class S>
	void show
	(
		S&,
		const bool plain = true,
		const int indent = 0
	) const;

	// Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String<>&) const;

private :
	void parse (char*, const char*);
	void parsingError (const char*);

	Integer degreeX_;
	Integer degreeY_;

	Real coefficient_ [MAX_DEGREE][MAX_DEGREE];
};

}
}


