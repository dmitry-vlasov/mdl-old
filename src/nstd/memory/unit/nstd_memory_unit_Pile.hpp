/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_unit_Pile.hpp                                */
/* Description:     pile of stacks - holder for multithreading               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MEMORY_UNIT_PILE_HPP_
#define NSTD_MEMORY_UNIT_PILE_HPP_

#include "memory/unit/nstd_memory_unit_Stack.hpp"

namespace nstd {
namespace memory {
namespace unit {

class Pile {
public :
	Pile();

	void create (const Size_t);
 	void destroy();
 	bool isCreated() const;

	Stack& stack();

	Stack& registerThread();
	void releaseThread();

	void memorizeState();
	void recallState();

	Size_t getUsedVolume() const;
	Size_t getOverallVolume() const;
	Size_t getAllocatedVolume() const;
	Size_t getDisposedVolume() const;
	Size_t getFreeVolume() const;

	template<class S>
	void show (S&) const;

private :
	enum {
		DEFAULT_STACK_VOLUME = 4 * size :: MEGABYTE,
		MAX_THREAD_NUMBER    = nstd :: MAX_THREAD_NUMBER
	};
	bool isCreated_;
	Size_t stackVolume_;
	pthread_t threadId_ [MAX_THREAD_NUMBER];
	unit :: Stack stackPile_ [MAX_THREAD_NUMBER];
	int threadCount_;
	int maxThreadCount_;
	static pthread_mutex_t mutex_;
};

}
}
}

#endif /*NSTD_MEMORY_UNIT_PILE_HPP_*/
