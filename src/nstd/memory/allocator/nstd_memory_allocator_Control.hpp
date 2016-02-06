/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_allocator_Control.hpp                        */
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

class Control {
public :
	Control ();
	~ Control();

	void set (const Interval<>);
	void checkScalarAllocation (const Interval<>, const unit :: Map&) const;
	void checkVectorAllocation (const Interval<>, const unit :: Map&) const;
	void checkDisposal (const Interval<>, const unit :: Map&);

private :
	Interval<> interval_;
};

}
}
}


