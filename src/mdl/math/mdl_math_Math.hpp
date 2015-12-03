/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_math_Math.hpp                                        */
/* Description:     all global containers for mdl language                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_MATH_MATH_HPP_
#define MDL_MATH_MATH_HPP_

namespace mdl {
namespace math {

class Math : public nstd :: Static<Math> {
public :
	static Assertions* assertions();
	static Constants* constants();
	static Defiendums* defiendums();
	static Expressions* expressions();
	static Evaluations* evaluations();
	static Proofs* proofs();
	static Propositions* propositions();
	static Rules* rules();
	static Statistics* statistics();
	static Theories* theories();
	static Types* types();

	static void clear();
	template<class S>
	static void show (S&);

	// nstd :: Static interface
	static void init();
	static void release();
	static void show (String&);
	static Size_t getVolume ();

private :
	static Assertions* assertions_;
	static Constants* constants_;
	static Defiendums* defiendums_;
	static Expressions* expressions_;
	static Evaluations* evaluations_;
	static Proofs* proofs_;
	static Propositions* propositions_;
	static Rules* rules_;
	static Statistics* statistics_;
	static Theories* theories_;
	static Types* types_;

	static String* message_;
};

}
}

#endif /*MDL_MATH_MATH_HPP_*/
