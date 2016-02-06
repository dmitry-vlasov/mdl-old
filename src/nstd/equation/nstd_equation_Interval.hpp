/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_equation_Interval.hpp                               */
/* Description:     Interval of numeric values                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "equation/nstd_equation_ValueInf.hpp"

namespace nstd {
namespace equation {

class Interval {
public :
	Interval ();
	Interval (const Real, bool high = true);
	Interval (const Real, const Real);
	Interval (const Interval&);
	~ Interval();

	bool contains (const Real) const;

	ValueInf getLow() const;
	ValueInf getHigh() const;
	void operator = (const Interval&);

	void setLow (const Real);
	void setHigh (const Real);

private :
	ValueInf low_;
	ValueInf high_;
};

}
}


