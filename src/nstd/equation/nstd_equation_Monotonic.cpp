/*****************************************************************************/
/* Project name:    nstd - non-standard general library                      */
/* File Name:       nstd_equation_Monotonic.cpp                              */
/* Description:     solving equations for monotonic functions                */
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

	/****************************
	 *		Public members
	 ****************************/

	template<class F>
	inline bool
	Monotonic :: solve (const Real y, Real& x, F f, const Interval interval, const Real precision)
	{
		typedef F Function;
		return solve<Function, Real> (y, x, f, interval, precision);
	}
	template<class F>
	inline bool
	Monotonic :: solve (const Real y, Real& x, F f, const Real precision)
	{
		const Interval interval;
		typedef F Function;
		return solve<Function, Real> (y, x, f, interval, precision);
	}
	template<class F>
	inline bool
	Monotonic :: solve (const Real y, Integer& x, F f, const Interval interval)
	{
		typedef F Function;
		return solve<Function, Integer> (y, x, f, interval, 1);
	}
	template<class F>
	inline bool
	Monotonic :: solve (const Real y, Integer& x, F f)
	{
		const Interval interval;
		typedef F Function;
		return solve<Function, Integer> (y, x, f, interval, 1);
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class F, class N>
	bool
	Monotonic :: solve (const Real y, N& x, F f, const Interval interval, const Real precision)
	{
		typedef N Number;
		Number x_down = 0;
		Number x_up = 1;
		for (int i = 0; i < MAX_DIGIT; ++ i) {
			const Real y_up = f (x_up);
			if (y < y_up) {
				#ifdef DEBUG_EQUATION_MONOTONIC
				std :: cout << "iteration break" << i << ": " << std :: endl;
				std :: cout << "x_down = " << x_down << ", ";
				std :: cout << "x_up = " << x_up << ", ";
				std :: cout << "y_up = " << y_up << std :: endl;
				std :: cout << std :: endl;
				#endif
				break;
			}
			x_down = x_up;
			if (interval.contains (x_up * 2)) {
				x_up *= 2;
			} else {
				x_up = interval.getHigh().getValue();
				x = x_up;
				return true;
			}

			#ifdef DEBUG_EQUATION_MONOTONIC
			std :: cout << "iteration " << i << ": " << std :: endl;
			std :: cout << "x_down = " << x_down << ", ";
			std :: cout << "x_up = " << x_up << ", ";
			std :: cout << "y_up = " << y_up << std :: endl;
			std :: cout << std :: endl;
			#endif
		}

		#ifdef DEBUG_EQUATION_MONOTONIC
		std :: cout << std :: endl;
		std :: cout << "finally" << std :: endl;
		std :: cout << "-------------------------" << std :: endl;
		std :: cout << "x_down = " << x_down << std :: endl;
		std :: cout << "x_up   = " << x_up << std :: endl;
		std :: cout << "-------------------------" << std :: endl;
		#endif

		Real y_up = f (x_up);
		Real y_down = f (x_down);
		int i = 0;
		while (fabs (x_up - x_down) > precision) {
			const Number x_mid = (x_up + x_down) / 2;
			const Real y_mid = f (x_mid);
			if (y < y_mid) {
				y_up = y_mid;
				x_up = x_mid;
			} else {
				y_down = y_mid;
				x_down = x_mid;
			}

			#ifdef DEBUG_EQUATION_MONOTONIC
			std :: cout << "iteration " << i ++ << ": " << std :: endl;
			std :: cout << "x_up = " << x_up << ", ";
			std :: cout << "y_up = " << y_up << std :: endl;
			std :: cout << "x_down = " << x_down <<  ", ";
			std :: cout << "y_down = " << y_up << std :: endl;
			std :: cout << "x_mid = " << x_mid <<  ", ";
			std :: cout << "y_mid = " << y_mid << std :: endl;
			std :: cout << std :: endl;
			#endif
		}

		#ifdef DEBUG_EQUATION_MONOTONIC
		std :: cout << std :: endl;
		std :: cout << "finally" << std :: endl;
		std :: cout << "-------------------------" << std :: endl;
		std :: cout << "x_down = " << x_down << ", ";
		std :: cout << "y_down = " << y_down << std :: endl;
		std :: cout << "-------------------------" << std :: endl;
		#endif

		x = x_down;
		return true;
	}
}
}


