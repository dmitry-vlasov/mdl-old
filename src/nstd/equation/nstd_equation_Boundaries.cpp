/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_equation_Boundaries.cpp                             */
/* Description:     boundaries for equations                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_EQUATION_BOUNDARIES_CPP_
#define NSTD_EQUATION_BOUNDARIES_CPP_

namespace nstd {
namespace equation {

	/****************************
	 *		Public members
	 ****************************/

	Boundaries :: Boundaries (const Integer dimension) :
	dimension_ (dimension),
	intervals_() {
	}
	inline
	Boundaries :: ~ Boundaries() {
	}

	inline const Interval&
	Boundaries :: getInterval (const Integer i) const {
		return intervals_ [i];
	}
	inline Interval&
	Boundaries :: interval (const Integer i) {
		return intervals_ [i];
	}

	/****************************
	 *		Private members
	 ****************************/

}
}

#endif /*NSTD_EQUATION_BOUNDARIES_CPP_*/
