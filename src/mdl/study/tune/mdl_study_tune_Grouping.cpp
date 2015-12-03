/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_tune_Grouping.cpp                              */
/* Description:     tuning of grouping for optimization                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_TUNE_GROUPING_CPP_
#define MDL_STUDY_TUNE_GROUPING_CPP_

namespace mdl {
namespace study {
namespace tune {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Grouping :: Grouping
	(
		Format& format,
		Sample* sample
	) :
	format_ (format),
	subFormat_ (format_),
	subSubFormat_ (subFormat_),
	teacher_ (new teach :: Optimization (subFormat_, sample)),
	optimalPrecision_ (0),
	optimalGrouping_ (0),
	memoryParameters_ (teacher_->maxGrouping_),
	memoryBoundaries_ (teacher_->maxGrouping_)
	{
		subFormat_.setVerbosity (format_.getVerbosity());
		for (value :: Integer i = 0; i < teacher_->maxGrouping_; ++ i) {
			vector :: value :: Real*
				papameterVector = new vector :: value :: Real (teacher_->dimension_);
			for (value :: Integer j = 0; j < teacher_->dimension_; ++ j) {
				papameterVector->add (1);
			}
			memoryParameters_.add (papameterVector);
		}
	}
	Grouping :: ~ Grouping() {
		deleteAggregateObject (teacher_);
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: tab;

	value :: Integer
	Grouping :: tune
	(
		Time& timeLimit,
		const value :: Integer optimalPrecision,
		const value :: Integer maxPrecision
	)
	{
		const value :: Integer maxGrouping = maxPrecision;
		optimalPrecision_ = optimalPrecision;
		format_.message() << "local root learning";
		format_.showStart (timeLimit);
		const value :: Real optimalQuantum = 1 / static_cast<value :: Real>(optimalPrecision_);
		value :: Real optimalFitness = 0;

		rememberState();
		bool initial = true;
		for (value :: Integer grouping = PRECISION_MIN; grouping <= maxGrouping; ++ grouping) {

			subFormat_.message() << "grouping = " << grouping;
			subFormat_.showStart();
			const value :: Real
				fitness = teacher_->evalFitness
				(
					optimalQuantum,
					grouping,
					Sampler_ :: DEFAULT_MODE
					//sampler :: Sampler :: LEAVE_ONE_OUT_MODE
				);
			subFormat_.message() << "fitness = " << fitness;
			subFormat_.showFinal();
			recallState();

			if (initial || (fitness < optimalFitness)) {
				optimalFitness = fitness;
				optimalGrouping_ = grouping;
			}
			initial = false;
			if (format_.getTimer().getSeconds() > timeLimit) {
				break;
			}
		}
		subFormat_.message() << "teaching with grouping = " << optimalGrouping_;
		subFormat_.showStart();
		Time limit = timeLimit - format_.getTimer().getSeconds();
		const value :: Real fitness = teacher_->teach (limit, optimalQuantum, optimalGrouping_);
		subFormat_.message() << "fitness = " << fitness;
		subFormat_.showFinal ();

		format_.message() << "fitness = " << teacher_->sample_->getFitness().eval();
		format_.showFinal();
		timeLimit -= format_.getTimer().getSeconds();
		return optimalGrouping_;
	}
	Time
	Grouping :: estimateTime
	(
		const value :: Integer sampleSize,
		const value :: Integer maxPrecision
	)
	{
		const value :: Integer maxGrouping = maxPrecision;
		Time estimatedTime = 0;
		for (value :: Integer grouping = PRECISION_MIN; grouping <= maxGrouping; ++ grouping) {
			Sampler_ sampler (sampleSize);
			Time iterationTime = 0;
			for (value :: Integer size = 1; size <= sampleSize; ++ size) {
				const value :: Integer iterations = sampler.getIterations (size);
				iterationTime += iterations * Benchmark :: get()->optimization()->getTimePolynomialXY()->eval (size, maxPrecision);
			}
			estimatedTime += grouping * iterationTime;
		}
		return estimatedTime * TIME_RESERVE_FACTOR;
	}
	void
	Grouping :: showEstimatedTimes
	(
		String& string,
		const Format& format,
		const value :: Integer sampleSize,
		const value :: Integer maxPrecision
	)
	{
		const value :: Integer maxGrouping = maxPrecision;
		for (value :: Integer grouping = PRECISION_MIN; grouping <= maxGrouping; ++ grouping) {
			Sampler_ sampler (sampleSize);
			Time iterationTime = 0;
			format.typeIndent (string);
			string << tab << tab << "grouping = " << grouping << ", ";
			for (value :: Integer size = 1; size <= sampleSize; ++ size) {
				const value :: Integer iterations = sampler.getIterations (size);
				iterationTime += iterations * Benchmark :: get()->optimization()->getTimePolynomialXY()->eval (size, maxPrecision);
			}
			//format.typeIndent (string);
			//string << tab << tab;
			string << "time: " << grouping * iterationTime << " s." << endLine;
		}

		/*value :: Real iterationTime = 0;
		sampler :: Sampler sampler (sampleSize);
		for (value :: Integer size = 1; size <= sampleSize; ++ size) {
			const value :: Integer iterations = sampler.getIterations (size);
			iterationTime += iterations * Benchmark :: get()->optimization()->getTimePolynomial()->eval (size);
		}
		format.typeIndent (string);
		string << tab << tab << "sample size = " << sampleSize << endLine;
		for (value :: Integer grouping = PRECISION_MIN; grouping <= maxGrouping; ++ grouping) {
			const value :: Real estimatedTime = grouping * iterationTime * TIME_RESERVE_FACTOR;
			format.typeIndent (string);
			string << tab << tab;
			string << "grp = " << grouping << ", ";
			string << "time: " << estimatedTime << " s." << endLine;
		}*/
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: mode;
using manipulator :: tab;

	// object :: Object implementation
	void
	Grouping :: commitSuicide() {
		delete this;
	}
	Size_t
	Grouping :: getVolume() const
	{
		Size_t volume = 0;
		volume += format_.getVolume();
		volume += subFormat_.getVolume();
		volume += subSubFormat_.getVolume();
		volume += getAggregateVolume (teacher_);
		volume += memoryParameters_.getVolume();
		volume += memoryBoundaries_.getVolume();
		return volume;
	}
	Size_t
	Grouping :: getSizeOf() const {
		return sizeof (Grouping);
	}
	void
	Grouping :: show (String&) const {
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Grouping :: rememberState()
	{
		if (teacher_->boundaries_.getSize() == 0) {
			teacher_->computeBoundaries (1);
		}
		memoryBoundaries_.copy (teacher_->boundaries_);
		const value :: Integer grouping = teacher_->boundaries_.getSize();
		for (value :: Integer i = 0; i < grouping; ++ i) {
			vector :: value :: Real*
				papameterVector = memoryParameters_.getValue (i);
			if (papameterVector == NULL) {
				papameterVector = memoryParameters_.push();
				for (value :: Integer j = 0; j < teacher_->dimension_; ++ j) {
					papameterVector->add (1);
				}
			}
			for (value :: Integer j = 0; j < teacher_->dimension_; ++ j) {
				const value :: Real
					parameter = teacher_->getParameter (i, j);
				papameterVector->getReference (j) = parameter;
			}
		}
	}
	void
	Grouping :: recallState()
	{
		teacher_->boundaries_.copy (memoryBoundaries_);
		const value :: Integer grouping = teacher_->boundaries_.getSize();
		for (value :: Integer i = 0; i < grouping; ++ i) {
			vector :: value :: Real*
				papameterVector = memoryParameters_.getValue (i);
			for (value :: Integer j = 0; j < teacher_->dimension_; ++ j) {
				const value :: Real
					parameter = papameterVector->getValue (j);
				teacher_->setParameter (i, j, parameter);
			}
		}
	}
}
}
}

#endif /*MDL_STUDY_TUNE_GROUPING_CPP_*/
