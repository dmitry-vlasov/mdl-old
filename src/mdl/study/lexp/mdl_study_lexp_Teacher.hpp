/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_lexp_Teacher.hpp                               */
/* Description:     lexp teaching function                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace study {
namespace lexp {

class Teacher :
	public object :: Object,
	public Scalar<Teacher> {
public :
	typedef
		form :: evaluation :: lexp :: Fris<allocator :: Heap>
		Fris_;

	Teacher (statement :: Experience*, const value :: Real percent);
	Teacher (statement :: Experience*, const value :: Integer maxSize);
	Teacher (statement :: Experience*);
	virtual ~ Teacher();

	void teachLimited (Time& timeLimit, const value :: Real threshold);
	void teach (const value :: Real threshold, const bool create);
	void teach
	(
		const value :: Real threshold,
		const Sample& sample,
		const bool create
	);
	Fris_* createResult() const;
	value :: Real evalFitness() const;
	const Matrix* getMatrix() const;

	static void init();
	static void release();

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	enum {
		MARTIX_BUILD_PHASE   = 0,
		STOLP_LEARNING_PHASE = 1,
		PHASES_NUM = 2
	};

	statement :: Experience* experience_;

	Matrix* matrix_;
	Stolp*  stolp_;
	value :: Integer size_;

	static value :: Real timeFractions_  [PHASES_NUM];
};

}
}
}


