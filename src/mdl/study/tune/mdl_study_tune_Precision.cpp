/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_tune_Precision.cpp                             */
/* Description:     tuning of precision for optimization                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_TUNE_PRECISION_CPP_
#define MDL_STUDY_TUNE_PRECISION_CPP_

namespace mdl {
namespace study {
namespace tune {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Precision :: Precision
	(
		Format& format,
		Sample* sample
	) :
	format_ (format),
	subFormat_ (format_),
	subSubFormat_ (subFormat_),
	teacher_ (new teach :: Optimization (subFormat_, sample)),
	optimalPrecision_ (0) {
	}
	Precision :: ~ Precision() {
		deleteAggregateObject (teacher_);
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: tab;

	value :: Integer
	Precision :: tune (Time& timeLimit, const value :: Integer maxPrecision)
	{
		format_.message() << "global root tuning";
		format_.showStart (timeLimit);
		value :: Real optimalQuantum = 0;
		value :: Real optimalFitness = 0;

		bool initial = true;
		for (
			value :: Integer precision = PRECISION_MIN;
			precision <= maxPrecision;
			precision += PRECISION_STEP
		) {
			const value :: Real quantum = 1 / static_cast<value :: Real>(precision);
			subFormat_.message() << "quantum = " << quantum;
			subFormat_.showStart();

			const value :: Real
				fitness = teacher_->evalFitness
				(
					quantum,
					1,
					//mdl :: Sampler :: LEAVE_ONE_OUT_MODE
					//sampler :: Sampler :: FOLD_NX2_MODE
					Sampler_ :: DEFAULT_MODE
				);

			subFormat_.message() << "fitness = " << fitness;
			subFormat_.showFinal();
			if (initial || (fitness < optimalFitness)) {
				optimalFitness = fitness;
				optimalQuantum = quantum;
				optimalPrecision_ = precision;
			}
			initial = false;
			if (format_.getTimer().getSeconds() > timeLimit) {
				break;
			}
		}
		subFormat_.message() << "teaching with quantum = " << optimalQuantum;
		subFormat_.showStart();
		Time limit = timeLimit - format_.getTimer().getSeconds();
		const value :: Real fitness = teacher_->teach (limit, optimalQuantum, 1);
		subFormat_.message() << "fitness = " << fitness;
		subFormat_.showFinal();

		format_.message() << "fitness = " << teacher_->sample_->getFitness().eval();
		format_.showFinal();
		timeLimit -= format_.getTimer().getSeconds();
		return optimalPrecision_;
	}
	Time
	Precision :: estimateTime
	(
		const value :: Integer sampleSize,
		const value :: Integer maxPrecision
	)
	{
		Time estimatedTime = 0;
		for (value :: Integer precision = PRECISION_MIN; precision <= maxPrecision; ++ precision) {
			Sampler_ sampler (sampleSize);
			Time iterationTime = 0;
			for (value :: Integer size = 1; size <= sampleSize; ++ size) {
				const value :: Integer
					iterations = sampler.getIterations (size);
				const value :: Real
					optimizeTime = Benchmark :: get()->optimization()->getTimePolynomialXY()->eval (size, precision);
				iterationTime += iterations * optimizeTime;
			}
			estimatedTime += iterationTime;
		}
		return estimatedTime * TIME_RESERVE_FACTOR;
	}
	void
	Precision :: showEstimatedTimes
	(
		String& string,
		const Format& format,
		const value :: Integer sampleSize,
		const value :: Integer maxPrecision
	)
	{
		for (value :: Integer precision = PRECISION_MIN; precision <= maxPrecision; ++ precision) {
			Sampler_ sampler (sampleSize);
			Time iterationTime = 0;
			format.typeIndent (string);
			string << tab << tab << "precision = " << precision << ", ";
			for (value :: Integer size = 1; size <= sampleSize; ++ size) {
				const value :: Integer
					iterations = sampler.getIterations (size);
				const value :: Real
					optimizeTime = Benchmark :: get()->optimization()->getTimePolynomialXY()->eval (size, precision);
				iterationTime += iterations * optimizeTime;
			}
			//format.typeIndent (string);
			//string << tab << tab;
			string << "time: " << iterationTime << " s." << endLine;
		}

		/*value :: Real iterationTime = 0;
		sampler :: Sampler sampler (sampleSize);
		for (value :: Integer size = 1; size <= sampleSize; ++ size) {
			const value :: Integer iterations = sampler.getIterations (size);
			iterationTime += iterations * Benchmark :: get()->optimization()->getTimePolynomialXY()->eval (size, maxPrecision);
		}
		format.typeIndent (string);
		string << tab << tab << "sample size = " << sampleSize << endLine;
		for (value :: Integer precision = PRECISION_MIN; precision <= maxPrecision; ++ precision) {
			const value :: Real estimatedTime = iterationTime * TIME_RESERVE_FACTOR;
			format.typeIndent (string);
			string << tab << tab;
			string << "qtm = " << 1/static_cast<value :: Real>(precision) << ", ";
			string << "time: " << estimatedTime << " s." << endLine;
		}*/
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: mode;
using manipulator :: tab;

	// object :: Object implementation
	void
	Precision :: commitSuicide() {
		delete this;
	}
	Size_t
	Precision :: getVolume() const
	{
		Size_t volume = 0;
		volume += format_.getVolume();
		volume += subFormat_.getVolume();
		volume += subSubFormat_.getVolume();
		volume += getAggregateVolume (teacher_);
		return volume;
	}
	Size_t
	Precision :: getSizeOf() const {
		return sizeof (Precision);
	}
	void
	Precision :: show (String&) const {
	}

	/****************************
	 *		Private members
	 ****************************/
}
}
}

#endif /*MDL_STUDY_TUNE_PRECISION_CPP_*/
