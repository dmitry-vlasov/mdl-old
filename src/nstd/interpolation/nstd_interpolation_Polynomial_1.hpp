/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_interpolation_Polynomial_1.hpp                      */
/* Description:     the polynomial of one variable class                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_INTERPOLATION_POLYNOMIAL_1_HPP_
#define NSTD_INTERPOLATION_POLYNOMIAL_1_HPP_

namespace nstd {
namespace interpolation {

template<class A>
class Polynomial<1, A> :
	public Object,
	public memory :: storage :: Scalar<Polynomial<1, A>, A> {
public :
	typedef A Allocator_;
	enum {
		MAX_DEGREE = 8
	};

	Polynomial ();
	Polynomial (const char*);
	Polynomial (const Integer degree);
	Polynomial (const Polynomial&);
	virtual ~ Polynomial();

	Integer getDegreeX() const;
	Real getCoefficient (const Integer) const;
	Real& coefficient (const Integer);

	Real eval (const Real) const;

	void operator = (const Polynomial&);
	void addVector (const Real [], const bool keepPositive = false);
	void subVector (const Real [], const bool keepPositive = false);

	Polynomial* derivateX() const;

	template<class S>
	void show (S&) const;

	// Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String<>&) const;

private :
	template<int, class>
	friend class Polynomial;

	void parse (char*, const char*);
	static Real parseCoefficient (char*& c, bool& error);
	static Integer parseDegree (char*& c, bool& error);
	static bool parseString (char*& c, const char* string);

	void parsingError (const char*);

	Integer greatestNonZeroDegree() const;

	Integer degreeX_;
	Real coefficient_ [MAX_DEGREE];
};

}
}

#endif /*NSTD_INTERPOLATION_POLYNOMIAL_1_HPP_*/
