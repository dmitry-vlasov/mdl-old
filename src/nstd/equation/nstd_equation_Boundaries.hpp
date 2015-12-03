/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_equation_Boundaries.hpp                             */
/* Description:     boundaries for equations                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_EQUATION_BOUNDARIES_HPP_
#define NSTD_EQUATION_BOUNDARIES_HPP_

#include "equation/nstd_equation_Interval.hpp"

namespace nstd {
namespace equation {

class Boundaries {
public :
	Boundaries (const Integer dim);
	~ Boundaries();

	const Interval& getInterval (const Integer) const;
	Interval& interval (const Integer);

private :
	enum {
		MAX_DIMENSION = 5
	};
	const Integer dimension_;
	Interval intervals_ [MAX_DIMENSION];
};

}
}

#endif /*NSTD_EQUATION_BOUNDARIES_HPP_*/
