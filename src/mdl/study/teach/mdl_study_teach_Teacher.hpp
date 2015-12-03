/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_teach_Teacher.hpp                              */
/* Description:     a class with a global teaching algorithm                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_TEACH_TEACHER_HPP_
#define MDL_STUDY_TEACH_TEACHER_HPP_

#include "mdl/interface/mdl_interface.hpp"

namespace mdl {
namespace study {
namespace teach {

class Teacher :
	public object :: Object,
	public Scalar<Teacher> {
public :
	Teacher (Format& format);
	virtual ~ Teacher();

	void teach (Time& timeLimit);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	class Timing;
	class Estimating;

	friend class Timing;
	friend class Estimating;

	Format format_;
	Benchmark* benchmark_;
	const value :: Integer threshold_;
	const value :: Integer precision_;
	const value :: Integer grouping_;
	value :: Integer sampleSize_;
	Estimating* estimating_;

	static value :: Real stepTimeFractions_  [STEPS_NUM];
	static value :: Real phaseTimeFractions_ [PHASES_NUM];
};

}
}
}

#endif /*MDL_STUDY_TEACH_TEACHER_HPP_*/
