/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_equation_ValueInf.hpp                               */
/* Description:     possibly infinite value                                  */
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

class ValueInf {
public :
	ValueInf (const bool sign = true);
	ValueInf (const Real);
	ValueInf (const ValueInf&);
	~ ValueInf();

	Real getValue() const;
	bool isInfinite() const;
	bool isPositive() const;

	void operator = (const ValueInf&);
	void operator = (const Real);

	bool operator < (const Real) const;
	bool operator <= (const Real) const;
	bool operator > (const Real) const;
	bool operator >= (const Real) const;
	bool operator == (const Real) const;

private :
	Real value_;
	bool inf_;
	bool sign_;
};

	bool operator < (const Real, const ValueInf&);
	bool operator <= (const Real, const ValueInf&);
	bool operator > (const Real, const ValueInf&);
	bool operator >= (const Real, const ValueInf&);
	bool operator == (const Real, const ValueInf&);
}
}


