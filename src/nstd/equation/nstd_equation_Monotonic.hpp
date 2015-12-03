/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_equation_Monotonic.hpp                              */
/* Description:     solving equations for monotonic functions                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_EQUATION_MONOTONIC_HPP_
#define NSTD_EQUATION_MONOTONIC_HPP_

namespace nstd {
namespace equation {

class Monotonic {
public :
	struct Boundaries {

	};

	// solves an equation f (x) = y for monotonic increasing function f on reals
	// returns true iff the solution up to demanded precision was found
	template<class F>
	static bool solve
	(
		const Real y,
		Real& x,
		F f,
		const Interval,
		const Real precision = 1E-9
	);
	template<class F>
	static bool solve
	(
		const Real y,
		Real& x,
		F f,
		const Real precision = 1E-9
	);

	// solves a pair of inequalities:
	//     f (x) <= y,
	//     f (x + 1) > y
	// for monotonic increasing function f on integers
	// returns true iff the solution up to demanded precision was found
	template<class F>
	static bool solve
	(
		const Real y,
		Integer& x,
		F f,
		const Interval
	);
	template<class F>
	static bool solve
	(
		const Real y,
		Integer& x,
		F f
	);

private :
	enum {
		MAX_DIGIT = 30
	};

	template<class F, class N>
	static bool solve
	(
		const Real y,
		N& x,
		F f,
		const Interval,
		const Real precision
	);
};

}
}

#endif /*NSTD_EQUATION_MONOTONIC_HPP_*/
