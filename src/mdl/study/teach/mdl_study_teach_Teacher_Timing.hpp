/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_teach_Teacher_Timing.hpp                       */
/* Description:     a class with a time estimation for teaching algorithm    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_TEACH_TEACHER_TIMING_HPP_
#define MDL_STUDY_TEACH_TEACHER_TIMING_HPP_

#include "mdl/interface/mdl_interface.hpp"

namespace mdl {
namespace study {
namespace teach {

class Teacher :: Timing :
	public object :: Object,
	public Scalar<Teacher :: Timing> {
public :
	Timing
	(
		Format&,
		const value :: Integer sampleSize,
		const value :: Integer precision,
		const value :: Integer grouping
	);
	virtual ~ Timing();

	Time estimate (const value :: Integer sampleSize);
	Time operator () (const value :: Integer sampleSize);

	void show (const bool full);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	Format format_;
	value :: Integer sampleSize_;
	value :: Integer precision_;
	value :: Integer grouping_;
};

}
}
}

#endif /*MDL_STUDY_TEACH_TEACHER_TIMING_HPP_*/
