/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_misc_Counter.hpp                                    */
/* Description:     static counter class                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MISC_COUNTER_HPP_
#define NSTD_MISC_COUNTER_HPP_

namespace nstd {
namespace misc {

class Counter {
public :
	typedef Size_t Index_;
	typedef Size_t Count_;

	static void switchOn (const Index_ = 0);
	static void switchOff (const Index_ = 0);
	static bool isOn (const Index_ = 0);
	static bool isOff (const Index_ = 0);
	static bool stop (const Index_ = 0);
	static void set (const Count_ = 0, const Index_ = 0);
	static void coset (const Count_ = 0, const Index_ = 0);
	static void force (const Index_ = 0);
	static void inc (const Index_ = 0);
	static void dec (const Index_ = 0);
	static Count_ get (const Index_ = 0);
	static void show (Index_ = 0);
	static void clear();

private :
	enum {
		DIMENSION = 16,
		MAX_THREAD_NUMBER = 64 //nstd :: MAX_THREAD_NUMBER
	};
	static void init();
	static int getThreadIndex();

	static Index_ counter_    [DIMENSION][MAX_THREAD_NUMBER];
	static Index_ stopCount_  [DIMENSION][MAX_THREAD_NUMBER];
	static Index_ startCount_ [DIMENSION][MAX_THREAD_NUMBER];
	static bool isOn_         [DIMENSION][MAX_THREAD_NUMBER];
	static bool initialized_;

	static pthread_t threadId_ [MAX_THREAD_NUMBER];
	static int threadCount_;
};

}
}

#endif /*NSTD_MISC_COUNTER_HPP_*/
