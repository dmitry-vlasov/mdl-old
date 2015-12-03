/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_misc_Counter.cpp                                    */
/* Description:     static counter class                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MISC_COUNTER_CPP_
#define NSTD_MISC_COUNTER_CPP_

namespace nstd {
namespace misc {

	/****************************
	 *		Public members
	 ****************************/

	inline void
	Counter :: switchOn (const Index_ index)
	{
		if (!initialized_) {
			init();
			initialized_ = true;
		}
		const int thread = getThreadIndex();
		isOn_ [index][thread] = true;
		//stopCount_ [index] = 0;
		//startCount_ [index] = Undefined<Index_> :: getValue();
	}
	inline void
	Counter :: switchOff (const Index_ index)
	{
		if (!initialized_) {
			init();
			initialized_ = true;
		}
		const int thread = getThreadIndex();
		isOn_ [index][thread] = false;
		//stopCount_ [index] = Undefined<Index_> :: getValue();
		//startCount_ [index] = 0;
	}
	inline bool
	Counter :: isOn (const Index_ index)
	{
		if (!initialized_) {
			init();
			initialized_ = true;
		}
		const int thread = getThreadIndex();
		return isOn_ [index][thread];
	}
	inline bool
	Counter :: isOff (const Index_ index) {
		return !isOn (index);
	}
	inline bool
	Counter :: stop (const Index_ index)
	{
		if (!initialized_) {
			init();
			initialized_ = true;
		}
		const int thread = getThreadIndex();
		if (!isOn_ [index][thread]) {
			return false;
		}
		return
			(counter_ [index][thread] >= stopCount_ [index][thread]) &&
			(counter_ [index][thread] <= startCount_ [index][thread]);
	}
	inline void
	Counter :: set (const Count_ count, const Index_ index)
	{
		if (!initialized_) {
			init();
			initialized_ = true;
		}
		const int thread = getThreadIndex();
		stopCount_ [index][thread] = count;
	}
	inline void
	Counter :: coset (const Count_ count, const Index_ index)
	{
		if (!initialized_) {
			init();
			initialized_ = true;
		}
		const int thread = getThreadIndex();
		startCount_ [index][thread] = count;
	}
	inline void
	Counter :: force (const Index_ index)
	{
		if (!initialized_) {
			init();
			initialized_ = true;
		}
		const int thread = getThreadIndex();
		stopCount_ [index][thread] = counter_ [index][thread];
	}
	inline void
	Counter :: inc (const Index_ index)
	{
		if (!initialized_) {
			init();
			initialized_ = true;
		}
		const int thread = getThreadIndex();
		++ counter_ [index][thread];
	}
	inline void
	Counter :: dec (const Index_ index)
	{
		if (!initialized_) {
			init();
			initialized_ = true;
		}
		const int thread = getThreadIndex();
		if (counter_ [index][thread] > 0) {
			-- counter_ [index][thread];
		}
	}
	inline Counter :: Count_
	Counter :: get (const Index_ index)
	{
		if (!initialized_) {
			init();
			initialized_ = true;
		}
		const int thread = getThreadIndex();
		return counter_ [index][thread];
	}
	inline void
	Counter :: show (const Index_ index)
	{
		if (!initialized_) {
			init();
			initialized_ = true;
		}
		const int thread = getThreadIndex();
		std :: cout << "counter " << index << " : " << counter_ [index][thread] << std :: endl;
	}
	void
	Counter :: clear()
	{
		for (Index_ j = 0; j < MAX_THREAD_NUMBER; ++ j) {
			for (Index_ i = 0; i < DIMENSION; ++ i) {
				counter_ [i][j] = 0;
				stopCount_ [i][j] = Undefined<Index_> :: getValue();
				startCount_ [i][j] = Undefined<Index_> :: getValue();
				isOn_ [i][j] = true;
			}
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Counter :: init ()
	{
		for (Index_ j = 0; j < MAX_THREAD_NUMBER; ++ j) {
			for (Index_ i = 0; i < DIMENSION; ++ i) {
				counter_ [i][j] = 0;
				stopCount_ [i][j] = Undefined<Index_> :: getValue();
				startCount_ [i][j] = Undefined<Index_> :: getValue();
				isOn_ [i][j] = true;
			}
			threadId_ [j] = Undefined<pthread_t> :: getValue();
		}
	}
	int
	Counter :: getThreadIndex()
	{
		pthread_t threadId = pthread_self();
		for (int i = 0; i < threadCount_; ++ i) {
			if (threadId == threadId_ [i]) {
				return i;
			}
		}
		threadId_ [threadCount_ ++] = threadId;
		return threadCount_ - 1;
	}

	/***********************************
	 *		Private static attributes
	 ***********************************/

	Counter :: Index_
		Counter :: counter_    [DIMENSION][MAX_THREAD_NUMBER];
	Counter :: Index_
		Counter :: stopCount_  [DIMENSION][MAX_THREAD_NUMBER];
	Counter :: Index_
		Counter :: startCount_ [DIMENSION][MAX_THREAD_NUMBER];
	bool
		Counter :: isOn_       [DIMENSION][MAX_THREAD_NUMBER];
	bool
		Counter :: initialized_ = false;

	pthread_t Counter :: threadId_ [MAX_THREAD_NUMBER];
	int Counter :: threadCount_ = 0;
}
}

#endif /*NSTD_MISC_COUNTER_CPP_*/
