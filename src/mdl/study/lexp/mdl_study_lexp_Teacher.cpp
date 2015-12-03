/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_lexp_Teacher.cpp                               */
/* Description:     lexp teaching function                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_LEXP_TEACHER_CPP_
#define MDL_STUDY_LEXP_TEACHER_CPP_

namespace mdl {
namespace study {
namespace lexp {

	/****************************
	 *		Public members
	 ****************************/

	Teacher :: Teacher
	(
		statement :: Experience* experience,
		const value :: Real percent
	) :
	experience_ (experience),
	matrix_
	(
		new Matrix
		(
			experience_->positiveSteps(),
			experience_->negativeSteps(),
			percent
		)
	),
	stolp_
	(
		new Stolp
		(
			matrix_,
			Stolp :: TYPE_MIXED_
		)
	),
	size_ (matrix_->getSize())
	{
		typedef
			form :: evaluation :: lexp :: Factors
			Factors;
		const value :: Real alpha = stolp_->getConfig().getParameter (Stolp :: ALPHA)->getValue();
		const value :: Real beta = stolp_->getConfig().getParameter (Stolp :: BETA)->getValue();
		Factors factors (alpha, beta);
		matrix_->build (factors);
	}
	Teacher :: Teacher
	(
		statement :: Experience* experience,
		const value :: Integer maxSize
	) :
	experience_ (experience),
	matrix_
	(
		new Matrix
		(
			experience_->positiveSteps(),
			experience_->negativeSteps(),
			maxSize
		)
	),
	stolp_
	(
		new Stolp
		(
			matrix_,
			Stolp :: TYPE_MIXED_
		)
	),
	size_ (matrix_->getSize())
	{
		typedef
			form :: evaluation :: lexp :: Factors
			Factors;
		const value :: Real alpha = stolp_->getConfig().getParameter (Stolp :: ALPHA)->getValue();
		const value :: Real beta = stolp_->getConfig().getParameter (Stolp :: BETA)->getValue();
		Factors factors (alpha, beta);
		matrix_->build (factors);
	}
	Teacher :: Teacher (statement :: Experience* experience) :
	experience_ (experience),
	matrix_
	(
		new Matrix
		(
			experience_->positiveSteps(),
			experience_->negativeSteps()
		)
	),
	stolp_
	(
		new Stolp
		(
			matrix_,
			Stolp :: TYPE_MIXED_
		)
	),
	size_ (matrix_->getSize()) {
	}
	Teacher :: ~ Teacher()
	{
		deleteAggregateObject (matrix_);
		deleteAggregateObject (stolp_);
	}

	void
	Teacher :: teachLimited (Time& timeLimit, const value :: Real threshold)
	{
		typedef
			form :: evaluation :: lexp :: Factors
			Factors;
		const value :: Real alpha = stolp_->getConfig().getParameter (Stolp :: ALPHA)->getValue();
		const value :: Real beta = stolp_->getConfig().getParameter (Stolp :: BETA)->getValue();
		Factors factors (alpha, beta);
		Time buildTimeLimit = timeLimit * timeFractions_ [MARTIX_BUILD_PHASE];
		Timer timer;
		timer.start();
		matrix_->build (factors, buildTimeLimit);
		timer.stop();
		size_ = matrix_->getSize();
		timeLimit -= timer.getSeconds();

		Sample totalSample (size_);
		for (value :: Integer i = 0; i < size_; ++ i) {
			totalSample.add (i);
		}

		Time learnTimeLimit = timeLimit; //timeLimit * timeFractions_ [STOLP_LEARNING_PHASE];
		stolp_->config().parameter (Stolp :: MAX_ETALONS)->setValue (threshold);
		stolp_->learn (totalSample, learnTimeLimit);
	}
	void
	Teacher :: teach (const value :: Real threshold, const bool create)
	{
		Sample totalSample (size_);
		for (value :: Integer i = 0; i < size_; ++ i) {
			totalSample.add (i);
		}
		stolp_->config().parameter (Stolp :: MAX_ETALONS)->setValue (threshold);
		stolp_->learn (totalSample);
	}
	void
	Teacher :: teach
	(
		const value :: Real threshold,
		const Sample& sample,
		const bool create
	)
	{
		stolp_->config().parameter (Stolp :: MAX_ETALONS)->setValue (threshold);
		stolp_->learn (sample);
	}
	inline Teacher :: Fris_*
	Teacher :: createResult() const {
		return stolp_->createResult();
	}
	inline value :: Real
	Teacher :: evalFitness() const
	{
		Sample totalSample (size_);
		for (value :: Integer i = 0; i < size_; ++ i) {
			totalSample.add (i);
		}
		return (100 - stolp_->getPercentClassified (totalSample));
	}
	inline const Matrix*
	Teacher :: getMatrix() const {
		return matrix_;
	}

	inline void
	Teacher :: init() {
		Stolp :: init();
	}
	inline void
	Teacher :: release() {
		Stolp :: release();
	}

using manipulator :: endLine;

	// object :: Object implementation
	void
	Teacher :: commitSuicide() {
		delete this;
	}
	Size_t
	Teacher :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (matrix_);
		volume += getAggregateVolume (stolp_);
		return volume;
	}
	Size_t
	Teacher :: getSizeOf() const {
		return sizeof (Teacher);
	}
	void
	Teacher :: show (String& string) const
	{
		string << "experience of ";
		string << " assertion";
		return;

		string << endLine;
		string << "===============================" << endLine;
	}

	/****************************
	 *		Private members
	 ****************************/

	value :: Real Teacher :: timeFractions_ [PHASES_NUM] = {
		0.5,   // MARTIX_BUILD_PHASE   50% of time
		0.5    // STOLP_LEARNING_PHASE 50% of time
	};
}
}
}

#endif /*MDL_STUDY_LEXP_TEACHER_CPP_*/
