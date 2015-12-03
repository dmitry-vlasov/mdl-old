/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_unit_Pile.cpp                                */
/* Description:     pile of stacks - holder for multithreading               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MEMORY_UNIT_PILE_CPP_
#define NSTD_MEMORY_UNIT_PILE_CPP_

namespace nstd {
namespace memory {
namespace unit {

	/****************************
	 *		Public members
	 ****************************/

	Pile :: Pile () :
	isCreated_ (false),
	stackVolume_ (DEFAULT_STACK_VOLUME),
	threadId_ (),
	stackPile_ (),
	threadCount_ (0),
	maxThreadCount_ (0)
	{
		for (int i = 0; i < MAX_THREAD_NUMBER; ++ i) {
			threadId_ [i] = Undefined<pthread_t> :: getValue();
		}
	}

	inline void
	Pile :: create (const Size_t volume)
	{
		if (isCreated_) {
			return;
		}
		isCreated_ = true;
		stackVolume_ = volume;
		registerThread();
	}
	void
	Pile :: destroy()
	{
		for (int i = 0; i < MAX_THREAD_NUMBER; ++ i) {
			stackPile_ [i].destroy();
		}
	}
	bool
	Pile :: isCreated() const {
		return isCreated_;
	}

	Stack&
	Pile :: stack()
	{
		pthread_t threadId = pthread_self();
		int index = -1;
		for (int i = 0; i < MAX_THREAD_NUMBER; ++ i) {
			if (threadId == threadId_ [i]) {
				index = i;
				break;
			}
		}
		if (index == -1) {
			return registerThread();
		} else {
			return stackPile_ [index];
		}
	}

	Stack&
	Pile :: registerThread()
	{
		#ifdef MULTY_THREADED
		pthread_mutex_lock (&mutex_);
		#endif
		pthread_t threadId = pthread_self();
		for (int i = 0; i < MAX_THREAD_NUMBER; ++ i) {
			if (threadId == threadId_ [i]) {
				#ifdef MULTY_THREADED
				pthread_mutex_unlock (&mutex_);
				#endif
				throw Exception ("double thread registration");
			}
		}
		int index = -1;
		for (int i = 0; i < MAX_THREAD_NUMBER; ++ i) {
			if (threadId_ [i] == Undefined<pthread_t> :: getValue()) {
				index = i;
				break;
			}
		}
		if (index == -1) {
			#ifdef MULTY_THREADED
			pthread_mutex_unlock (&mutex_);
			#endif
			throw Exception ("threads number exceeds stack holder capacity");
		}
		threadId_ [index] = threadId;
		if (!stackPile_ [index].isCreated()) {
			stackPile_ [index].create (stackVolume_);
		} else {
			stackPile_ [index].clear (false);
		}
		++ threadCount_;
		if (threadCount_ > maxThreadCount_) {
			maxThreadCount_ = threadCount_;
		}
		#ifdef MULTY_THREADED
		pthread_mutex_unlock (&mutex_);
		#endif
		return stackPile_ [index];
	}
	void
	Pile :: releaseThread()
	{
		#ifdef MULTY_THREADED
		pthread_mutex_lock (&mutex_);
		#endif
		pthread_t threadId = pthread_self();
		int index = -1;
		for (int i = 0; i < MAX_THREAD_NUMBER; ++ i) {
			if (threadId == threadId_ [i]) {
				index = i;
				break;
			}
		}
		if (index == -1) {
			std :: cout << "threadID = " << threadId << std :: endl;
			show (std :: cout);
			#ifdef MULTY_THREADED
			pthread_mutex_unlock (&mutex_);
			#endif
			throw Exception ("invalid thread release: thread ID is not found");
		}
		stackPile_ [index].clear (false);
		threadId_ [index] = Undefined<pthread_t> :: getValue();
		-- threadCount_;
		#ifdef MULTY_THREADED
		pthread_mutex_unlock (&mutex_);
		#endif
	}

	void
	Pile :: memorizeState()
	{
		for (int i = 0; i < MAX_THREAD_NUMBER; ++ i) {
			stackPile_ [i].memorizeState();
		}
	}
	void
	Pile :: recallState()
	{
		for (int i = 0; i < MAX_THREAD_NUMBER; ++ i) {
			stackPile_ [i].recallState();
		}
	}

	Size_t
	Pile :: getUsedVolume() const
	{
		Size_t volume = 0;
		for (int i = 0; i < MAX_THREAD_NUMBER; ++ i) {
			volume += stackPile_ [i].getUsedVolume();
		}
		return volume;
	}
	Size_t
	Pile :: getOverallVolume() const
	{
		Size_t volume = 0;
		for (int i = 0; i < MAX_THREAD_NUMBER; ++ i) {
			volume += stackPile_ [i].getOverallVolume();
		}
		return volume;
	}
	Size_t
	Pile :: getAllocatedVolume() const
	{
		Size_t volume = 0;
		for (int i = 0; i < MAX_THREAD_NUMBER; ++ i) {
			volume += stackPile_ [i].getAllocatedVolume();
		}
		return volume;
	}
	Size_t
	Pile :: getDisposedVolume() const
	{
		Size_t volume = 0;
		return volume;
	}
	Size_t
	Pile :: getFreeVolume() const
	{
		Size_t volume = 0;
		for (int i = 0; i < MAX_THREAD_NUMBER; ++ i) {
			volume += stackPile_ [i].getFreeVolume();
		}
		return volume;
	}

	template<class S>
	void
	Pile :: show (S& string) const
	{
		string << "pile of stacks" << chars :: NEW_LINE;
		string << "--------------" << chars :: NEW_LINE;
		if (isCreated()) {
			string << "thread count: " << threadCount_ << chars :: NEW_LINE;
			string << "max thread count: " << maxThreadCount_ << chars :: NEW_LINE;
			string << "-------------------" << chars :: NEW_LINE;
			for (int i = 0; i < MAX_THREAD_NUMBER; ++ i) {
				if (stackPile_ [i].isCreated()) {
					string << "stack = " << i << ", ";
					string << "pthreadID = ";
					if (i == 0) {
						string << "<root>";
					} else if (threadId_ [i] == Undefined<pthread_t> :: getValue()) {
						string << "<undefined>";
					} else {
						string << threadId_ [i];
					}
					string << chars :: NEW_LINE;
					stackPile_ [i].show (string, 1);
					string << chars :: NEW_LINE;
				}
			}
		} else {
			string << "stack memory space was not created." << chars :: NEW_LINE;
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	pthread_mutex_t Pile :: mutex_ = PTHREAD_MUTEX_INITIALIZER;
}
}
}

#endif /*NSTD_MEMORY_UNIT_PILE_CPP_*/
