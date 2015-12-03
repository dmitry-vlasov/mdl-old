/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_Space.hpp                                    */
/* Description:     general memory space                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MEMORY_SPACE_HPP_
#define NSTD_MEMORY_SPACE_HPP_

#include "memory/unit/nstd_memory_unit.hpp"

namespace nstd {
namespace memory {

class Space {
public :
	static Size_t getUsedVolume();
	static Size_t getOverallVolume();
	static Size_t getAllocatedVolume();
	static Size_t getDisposedVolume();
	static Size_t getFreeVolume();

	static bool contains (const void* pointer);
	static bool containsInFree (const void* pointer);
	static bool containsInUsed (const void* pointer);
	static const char* whereIs (const void* pointer);

	static const unit :: Heap&  getHeap();
	static const unit :: Stack& getStack();
	static const unit :: Pile&  getPile();
	static const unit :: Boxed& getBoxed();
	static const unit :: Standard& getStandard();

	static unit :: Heap&  heap();
	static unit :: Stack& stack();
	static unit :: Pile&  pile();
	static unit :: Boxed& boxed();
	static unit :: Standard& standard();

	template<class S>
	static void show (S&);

private :
	friend class allocator :: Heap;
	friend class allocator :: Stack;
	friend class allocator :: Boxed;
	friend class allocator :: Standard;

	template<class S>
	static void showSummary (S&);
	template<class S>
	static void showDetails (S&);

	static unit :: Heap  heap_;
	static unit :: Pile  pile_;
	static unit :: Boxed boxed_;
	static unit :: Standard standard_;
};

}
}

#endif /*NSTD_MEMORY_SPACE_HPP_*/
