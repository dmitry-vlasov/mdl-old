/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_teach_Teacher_Timing.cpp                       */
/* Description:     a class with a time estimation for teaching algorithm    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_TEACH_TEACHER_TIMING_CPP_
#define MDL_STUDY_TEACH_TEACHER_TIMING_CPP_

namespace mdl {
namespace study {
namespace teach {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Teacher :: Timing :: Timing
	(
		Format& format,
		const value :: Integer sampleSize,
		const value :: Integer precision,
		const value :: Integer grouping
	) :
	format_ (format, true),
	sampleSize_ (sampleSize),
	precision_ (precision),
	grouping_ (grouping) {
	}
	Teacher :: Timing :: ~ Timing() {
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: tab;

	Time
	Teacher :: Timing :: estimate (const value :: Integer sampleSize)
	{
		Time estimatedTime = 0;
		estimatedTime +=
			Benchmark :: get()->sample()->getTimePolynomialX()->eval (sampleSize) * TIME_RESERVE_FACTOR;
		estimatedTime +=
			Benchmark :: get()->optimization()->getTimePolynomialXY()->eval (sampleSize, precision_) * TIME_RESERVE_FACTOR;
		estimatedTime +=
			grouping_ * Benchmark :: get()->optimization()->getTimePolynomialXY()->eval (sampleSize, precision_) * TIME_RESERVE_FACTOR;
		return estimatedTime;
	}
	inline Time
	Teacher :: Timing :: operator() (const value :: Integer sampleSize)
	{
		sampleSize_ = sampleSize;
		return estimate (sampleSize_);
	}

	void
	Teacher :: Timing :: show (const bool full)
	{
		format_.message() << "time estimation for ";
		format_.message() << "sample size = " << sampleSize_ <<  ", ";
		format_.showMessage();
		format_.message() << "precision = " << precision_ <<  ", ";
		format_.showMessage();
		format_.message() << "grouping = " << grouping_ <<  ", ";
		format_.showMessage();
		format_.message() << "total time estimated:  ";
		format_.message() << estimate (sampleSize_) << " s.";
		format_.showMessage();
		if (full) {
			format_.message() << "--------------------------";
			format_.showMessage();
			format_.message() << tab << "estimated sample time: ";
			format_.message() << Benchmark :: get()->sample()->getTimePolynomialX()->eval (sampleSize_) * TIME_RESERVE_FACTOR << " s.";
			format_.showMessage();

			format_.message() << tab << "estimated precision time: ";
			format_.message() << Benchmark :: get()->optimization()->getTimePolynomialXY()->eval (sampleSize_, precision_) * TIME_RESERVE_FACTOR << " s.";
			format_.showMessage();

			format_.message() << tab << "estimated grouping time:  ";
			format_.message() << grouping_ * Benchmark :: get()->optimization()->getTimePolynomialXY()->eval (sampleSize_, precision_) * TIME_RESERVE_FACTOR << " s.";
			format_.showMessage();
			format_.message() << "--------------------------";
			format_.showMessage();
		}
	}

	// object :: Object implementation
	void
	Teacher :: Timing :: commitSuicide() {
		delete this;
	}
	Size_t
	Teacher :: Timing :: getVolume() const
	{
		Size_t volume = 0;
		volume += format_.getVolume();
		return volume;
	}
	Size_t
	Teacher :: Timing :: getSizeOf() const {
		return sizeof (Timing);
	}
	void
	Teacher :: Timing :: show (String& string) const {
		//show (string, sampleSize_, maxPrecision_, true);
	}

	/****************************
	 *		Private members
	 ****************************/
}
}
}

#endif /*MDL_STUDY_TEACH_TEACHER_TIMING_CPP_*/
