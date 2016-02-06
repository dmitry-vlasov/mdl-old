/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_Unit.cpp                                     */
/* Description:     displays memory volume in proper units                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {
namespace memory {

	/****************************
	 *		Public members
	 ****************************/

	template<class S>
	void
	Unit :: show (S& s, const Ptrdiff_t volume)
	{
		const Unit_ measureUnit = calculate (volume);
		const double normalizedVolume =
			static_cast<const double> (volume) / measureUnit;
		s << normalizedVolume << chars :: SPACE << unit (measureUnit);
	}
	template<>
	void
	Unit :: show<std :: ostream> (std :: ostream& s, const Ptrdiff_t volume)
	{
		const Unit_ measureUnit = calculate (volume);
		const double normalizedVolume =
			static_cast<const double> (volume) / measureUnit;
		s << std :: setprecision (3) << normalizedVolume << chars :: SPACE << unit (measureUnit);
	}
	inline const char*
	Unit :: unit (const Unit_ unit)
	{
		switch (unit) {
		case BYTE     : return "b";
		case KILOBYTE : return "kb";
		case MEGABYTE : return "mb";
		case GIGABYTE : return "gb";
		default       : return "";
		}
	}
	Unit :: Unit_
	Unit :: calculate (const Ptrdiff_t volume)
	{
		const Size_t vol = (volume < 0) ? -volume : volume;
		if (vol < KILOBYTE) {
			return BYTE;
		}
		if (vol < MEGABYTE) {
			return KILOBYTE;
		}
		if (vol < GIGABYTE) {
			return MEGABYTE;
		}
		return GIGABYTE;
	}
}
}


