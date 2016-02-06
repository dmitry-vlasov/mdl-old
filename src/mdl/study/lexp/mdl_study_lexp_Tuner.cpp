/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_lexp_Tuner.cpp                                 */
/* Description:     tuner for the learning algorithms                        */
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

	/****************************
	 *		Public members
	 ****************************/

	inline
	Tuner :: Tuner
	(
		statement :: Experience* experience,
		const value :: Real percent,
		Format* format
	) :
	format_ ((format == NULL) ? NULL : new Format (*format, true)),
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
	Tuner :: ~ Tuner()
	{
		deleteAggregateObject (format_);
		deleteAggregateObject (matrix_);
		deleteAggregateObject (stolp_);
	}

	value :: Real
	Tuner :: tune (const value :: Real threshold)
	{
		value :: Real fitnessSum = 0;
		Sampler_ sampler (size_);
		if (size_ <= 1) {
			return 0;
		} else {
			bool first = true;
			while (sampler.generate()) {
				Sample_& sample = sampler.getSample();
				sample.setMode (Sample_ :: LEARNING);
				const value :: Integer
					trainingSize = sample.getSize();
				Sample trainingSample (sample.getSize());
				for (value :: Integer i = 0; i < sample.getSize(); ++ i) {
					trainingSample.add (sample.getIndex (i));
				}
				sample.setMode (Sample_ :: CONTROL);
				Sample controlSample (sample.getSize());
				for (value :: Integer i = 0; i < sample.getSize(); ++ i) {
					controlSample.add (sample.getIndex (i));
				}

				/*if (Counter :: stop() && first) {
					Counter :: set (0,1);
				}*/

				stolp_->config().parameter (Stolp :: MAX_ETALONS)->setValue (threshold);
				const value :: Real fitness = stolp_->evalFitness (trainingSample, controlSample);
				/*if (Counter :: stop() && first && format_ != NULL) {
					format_->message() << "pos = " << stolp_->etalonsPos_.getSize() << ", ";
					format_->message() << "neg = " << stolp_->etalonsNeg_.getSize() << ", ";
					format_->message() << "fitness = " << fitness;
					format_->showMessage();
				}*/

				fitnessSum += fitness;
				first = false;
			}
			return fitnessSum / sampler.getCount();
		}
	}
	value :: Real
	Tuner :: estimateTime
	(
		const value :: Integer size,
		const value :: Real threshold
	)
	{
		Sampler_ sampler (size);
		if (size <= 1) {
			return 0;
		} else {
			value :: Real overallTime = 0;
			while (sampler.generate()) {
				Sample_& sample = sampler.getSample();
				sample.setMode (Sample_ :: LEARNING);
				const value :: Integer
					size = sample.getSize();
				//const value :: Real
				//	time = Benchmark :: get()->fris()->getTeachTimePolynomial()->eval (size);
				const value :: Real
					time = Benchmark :: get()->fris()->getTeachTimePolynomialXY()->eval (size, threshold);
				overallTime += time;
			}
			return overallTime;
		}
	}
	const Matrix*
	Tuner :: getMatrix() const {
		return matrix_;
	}

	inline void
	Tuner :: init() {
		Stolp :: init();
	}
	inline void
	Tuner :: release() {
		Stolp :: release();
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Object implementation

	void
	Tuner :: commitSuicide() {
		delete this;
	}
	Size_t
	Tuner :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (format_);
		volume += getAggregateVolume (matrix_);
		volume += getAggregateVolume (stolp_);
		return volume;
	}
	Size_t
	Tuner :: getSizeOf() const {
		return sizeof (Tuner);
	}
	void
	Tuner :: show (String& string) const {
	}
}
}
}


