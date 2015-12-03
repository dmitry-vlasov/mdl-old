/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_unit_PointerStack.cpp                        */
/* Description:     stack of pointers                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MEMORY_UNIT_POINTER_STACK_CPP_
#define NSTD_MEMORY_UNIT_POINTER_STACK_CPP_

namespace nstd {
namespace memory {
namespace unit {

	/****************************
	 *		Public members
	 ****************************/

	inline
	PointerStack :: PointerStack () : 
	memIndex_ (-1),
	topIndex_ (-1),
	maxIndex_ (0),
	stack_ () {
	}

	void
	PointerStack :: push (Byte_t* pointer) throw (exception :: StackOverflow)
	{
		topIndex_ ++;
		if (topIndex_ >= CAPACITY) {
			throw exception :: StackOverflow ();
		}
		stack_ [topIndex_] = pointer;
	}

	Byte_t*
	PointerStack :: pop() throw (exception :: EmptyStackPop) 
	{
		if (topIndex_ == -1) {
			throw exception :: EmptyStackPop ();
		}
		if (topIndex_ > maxIndex_) {
			maxIndex_ = topIndex_;
		}
		if (topIndex_ == memIndex_) {
			-- memIndex_;
		}
		return stack_ [topIndex_ --];
	}
	Byte_t*
	PointerStack :: get() throw (exception :: EmptyStackPop)
	{
		if (topIndex_ == -1) {
			throw exception :: EmptyStackPop ();
		}
		return stack_ [topIndex_];
	}

	inline void
	PointerStack :: memorizeState() {
		memIndex_ = topIndex_;
	}
	inline void
	PointerStack :: recallState() {
		topIndex_ = memIndex_;
	}

	inline bool
	PointerStack :: isEmpty() const {
		return (topIndex_ == -1);
	}
	inline void
	PointerStack :: clear () {
		topIndex_ = -1;
	}
	inline PointerStack :: Index_
	PointerStack :: getMaxDepth() const {
		return maxIndex_ + 1;
	}
	inline PointerStack :: Index_
	PointerStack :: getDepth() const {
		return topIndex_ + 1;
	}

	template<class S>
	void
	PointerStack :: show (S& string, const int indent) const
	{
		chars :: shift (string, indent);
		string << "pointer stack:" << chars :: NEW_LINE;
		if (isEmpty()) {
			chars :: shift (string, indent);
			string << "is empty" << chars :: NEW_LINE;
		} else {
			chars :: shift (string, indent);
			string << "current stack depth: " << (topIndex_ + 1) << chars :: NEW_LINE;
		}
		chars :: shift (string, indent);
		string << "max stack depth:" << maxIndex_ + 1 << chars :: NEW_LINE;
		string << chars :: NEW_LINE;
		/*
		const double percentMaxVolume = static_cast<double> (maxSpaceVolume_) * 100 / spaceVolume_;
		string << "max top used: \t\t\t" << maxSpaceVolume_ / 1024 << " kb \t\t";
		string << "(" << maxSpaceVolume_ << ") \t\t";
		string << " = " << percentMaxVolume << " %";
		string << endl;

		const double percentMaxMemUsed = static_cast<double> (maxTotalVolume_) * 100 / spaceVolume_;
		string << "max mem used: \t\t" << maxTotalVolume_ / 1024 << " kb \t\t";
		string << "(" << maxTotalVolume_ << ") \t\t";
		string << " = " << percentMaxMemUsed << " %";
		string << endl;
		*/
	}
}
}
}

#endif /*NSTD_MEMORY_UNIT_POINTER_STACK_CPP_*/
