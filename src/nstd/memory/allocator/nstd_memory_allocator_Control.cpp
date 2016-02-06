/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_allocator_Control.cpp                        */
/* Description:     the debugging control of the allocation                  */
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
namespace allocator {

	/****************************
	 *		Public members
	 ****************************/

	Control :: Control() :
	interval_() {
	}
	Control :: ~ Control() {
	}

	inline void
	Control :: set (const Interval<> interval) {
		interval_ = interval;
	}
	void
	Control :: checkScalarAllocation (const Interval<> interval, const unit :: Map& map) const
	{
		if (interval_.isRegular()) {
			if (interval_.intersectsWith (interval)) {
				std :: cout << std :: endl;
				std :: cout << "scalar allocated interval:" << std :: endl;
				map.show (std :: cout, interval); std :: cout << std :: endl;
				std :: cout << "intersects with the control interval:" << std :: endl;
				map.show (std :: cout, interval_); std :: cout << std :: endl;
				std :: cout << std :: endl;
			}
		}
	}
	void
	Control :: checkVectorAllocation (const Interval<> interval, const unit :: Map& map) const
	{
		if (interval_.isRegular()) {
			if (interval_.intersectsWith (interval)) {
				std :: cout << std :: endl;
				std :: cout << "vector allocated interval:" << std :: endl;
				map.show (std :: cout, interval); std :: cout << std :: endl;
				std :: cout << "intersects with the control interval:" << std :: endl;
				map.show (std :: cout, interval_); std :: cout << std :: endl;
				std :: cout << std :: endl;
			}
		}
	}
	void
	Control :: checkDisposal (const Interval<> interval, const unit :: Map& map)
	{
		if (interval_.isRegular()) {
			if (interval_ == interval) {
				interval_ = Interval<>();
			} else if (interval_.intersectsWith (interval)) {
				std :: cout << std :: endl;
				std :: cout << "disposed interval:" << std :: endl;
				map.show (std :: cout, interval); std :: cout << std :: endl;
				std :: cout << "intersects with the control interval:" << std :: endl;
				map.show (std :: cout, interval_); std :: cout << std :: endl;
				std :: cout << std :: endl;
			}
		}
	}
}
}
}


