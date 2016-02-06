/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_unit_PointerStack.hpp                        */
/* Description:     stack of pointers                                        */
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
namespace unit {

class PointerStack {
public :
	typedef int Index_;

	PointerStack ();

	void push (Byte_t*) throw (exception :: StackOverflow);
	Byte_t* pop() throw (exception :: EmptyStackPop);
	Byte_t* get() throw (exception :: EmptyStackPop);

	void memorizeState();
	void recallState();

	bool isEmpty() const;
	void clear();
	Index_ getMaxDepth() const;
	Index_ getDepth() const;

	template<class S>
	void show (S&, const int indent = 1) const;

private :
	enum {
		CAPACITY = size :: KILOBYTE * 64
	};

	Index_ memIndex_; // Memorized index of the stack top
	Index_ topIndex_; // Current index of the stack top
	Index_ maxIndex_;
	Byte_t* stack_ [CAPACITY];
};

}
}
}


