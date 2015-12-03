/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_teach_Optimization.cpp                         */
/* Description:     optimizing parameters                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_TEACH_OPTIMIZATION_CPP_
#define MDL_STUDY_TEACH_OPTIMIZATION_CPP_

namespace mdl {
namespace study {
namespace teach {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Optimization :: Optimization (Format& format, Sample* sample) :
	format_ (format),
	maxGrouping_
	(
		Config :: tune() ?
		tune :: PRECISION_MAX :
		Config :: getInteger (Config :: GROUPING)
	),
	dimension_ (form :: evaluation :: function :: WeightedSum :: PARAMETER_VECTOR_DIMENSION),
	descriptionVector_ (NULL),
	boundaries_ (maxGrouping_),
	sample_ (sample) {
	}
	Optimization :: ~ Optimization() {
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: mode;
using manipulator :: tab;

	value :: Real
	Optimization :: teach
	(
		Time& timeLimit,
		const value :: Real quantum,
		const value :: Integer grouping,
		const Sample_* sample
	)
	{
		format_.message() << "root teaching";
		format_.showStart (timeLimit);
		const value :: Real
			result = justTeach (timeLimit, quantum, grouping, sample);
		format_.message() << "fitness = " << sample_->getFitness().eval() << "%";
		format_.showFinal();
		return result;
	}

	value :: Real
	Optimization :: evalFitness
	(
		const value :: Real quantum,
		const value :: Integer grouping,
		Sampler_ :: Mode_ mode
	)
	{
		Format subFormat (format_, true);
		format_.message() << "fitness evaluation";
		format_.showStart();
		const value :: Integer testSize = sample_->getPrimary().getSize();
		value :: Real sumFitness = 0;
		Sampler_ sampler (testSize, mode);
		while (sampler.generate()) {
			Sample_& sample = sampler.getSample();
			sample.setMode (Sample_ :: LEARNING);
			Time timeLimit = Config :: getTimeLimit();

			subFormat.message() << "teaching, size = ";
			subFormat.message() << sample.getSize();
			subFormat.showStart();
			const value :: Real
				optimalFitness = justTeach (timeLimit, quantum, grouping, &sample);

			sample.setMode (Sample_ :: CONTROL);
			const value :: Real
				controlFitness = sample_->getFitness().eval (&sample);

			subFormat.message() << "control fitness = " << controlFitness;
			subFormat.showFinal();

			sumFitness += controlFitness;
			sample.setMode (Sample_ :: SAMPLE);
		}
		format_.message() << "fitness = " << sample_->getFitness().eval() << "%";
		format_.showFinal();
		return sumFitness / sampler.getCount();
	}

	// object :: Object implementation
	void
	Optimization :: commitSuicide() {
		delete this;
	}
	Size_t
	Optimization :: getVolume() const
	{
		Size_t volume = 0;
		volume += boundaries_.getVolume();
		volume += format_.getVolume();
		return volume;
	}
	Size_t
	Optimization :: getSizeOf() const {
		return sizeof (Optimization);
	}
	void
	Optimization :: show (String&) const {
	}

	/****************************
	 *		Private members
	 ****************************/

	value :: Real
	Optimization :: justTeach
	(
		Time& timeLimit,
		const value :: Real quantum,
		const value :: Integer grouping,
		const Sample_* sample
	)
	{
		computeBoundaries (grouping);
		value :: Real optimalFitness = 0;
		for (value :: Integer group = 0; group < grouping; ++ group) {
			optimalFitness = optimizeGroup (quantum, group, sample);
		}
		return optimalFitness;
	}
	value :: Real
	Optimization :: optimizeGroup
	(
		const value :: Real quantum,
		const value :: Integer group,
		const Sample_* sample
	)
	{
		//Timer timer;
		descriptionVector_ = form :: evaluation :: function :: WeightedSum :: descriptionVector();
		const value :: Name name = Config :: experience();

		const value :: Real initialFitness = sample_->getFitness().eval (sample);
		value :: Real optimalFitness = initialFitness;
		value :: Real lastFitness = optimalFitness;

		//timer.start();
		//do {
			lastFitness = optimalFitness;
			for (value :: Integer i = 0; i < dimension_; ++ i) {
				const Description_* description = descriptionVector_->getValue (i);

				value :: Real optimalParameter = getParameter (group, i);
				value :: Real currentParameter = description->getMinimumValue();

				while (currentParameter < description->getMaximumValue()) {
					setParameter (group, i, currentParameter);

					const value :: Real currentFitness =
						sample_->getFitness().eval (sample);

					if (currentFitness < optimalFitness) {
						optimalFitness = currentFitness;
						optimalParameter = currentParameter;
					}
					currentParameter += quantum;
				}
				setParameter (group, i, optimalParameter);
			}
		//} while (optimalFitness < lastFitness);
		//timer.stop();
		return optimalFitness;
	}

	void
	Optimization :: setParameter
	(
		const value :: Integer group,
		const value :: Integer index,
		const value :: Real parameter
	)
	{
		const value :: Name name = Config :: experience();
		const value :: Integer lowerBoundary = (group == 0) ? 0 : boundaries_ [group - 1];
		const value :: Integer upperBoundary = boundaries_ [group];

		for (value :: Integer i = lowerBoundary; i < upperBoundary; ++ i) {
			mdl :: Proposition*
				proposition = Math :: propositions()->getDescending (i);
			mdl :: evaluation :: Function*
				function = proposition->getEvaluation (name);
			form :: evaluation :: function :: WeightedSum*
				weightedSum = dynamic_cast<form :: evaluation :: function :: WeightedSum*>(function);
			if (weightedSum != NULL) {
				weightedSum->weightedSum()->weightVector().getReference (index) = parameter;
			}
		}
	}
	value :: Real
	Optimization :: getParameter
	(
		const value :: Integer group,
		const value :: Integer index
	)
	{
		const value :: Name name = Config :: experience();
		const value :: Integer lowerBoundary = (group == 0) ? 0 : boundaries_ [group - 1];
		mdl :: Proposition*
			proposition = Math :: propositions()->getDescending (lowerBoundary);
		mdl :: evaluation :: Function*
			function = proposition->getEvaluation (name);
		form :: evaluation :: function :: WeightedSum*
			weightedSum = dynamic_cast<form :: evaluation :: function :: WeightedSum*>(function);
		if (weightedSum != NULL) {
			 return weightedSum->weightedSum()->weightVector().getValue (index);
		} else {
			return -1;
		}
	}

	void
	Optimization :: computeBoundaries (const value :: Integer grouping)
	{
		boundaries_.clear();
		const value :: Real sumRate = computeSumRate();
		const value :: Real specificRate = sumRate / grouping;
		value :: Real counter = 1;
		value :: Real rate = 0;
		for (value :: Integer i = 0; i < Math :: propositions()->getSize(); ++ i) {
			mdl :: Proposition*
				proposition = Math :: propositions()->getDescending (i);
			rate += proposition->getRate();
			if (rate > specificRate * counter) {
				boundaries_.add (i);
				++ counter;
			}
		}
		boundaries_.add (Math :: propositions()->getSize());
	}
	value :: Integer
	Optimization :: computeSumRate() const
	{
		value :: Integer sumRate = 0;
		for (value :: Integer i = 0; i < Math :: propositions()->getSize(); ++ i) {
			mdl :: Proposition*
				proposition = Math :: propositions()->getDescending (i);
			sumRate += proposition->getRate();
		}
		return sumRate;
	}
}
}
}

#endif /*MDL_STUDY_TEACH_OPTIMIZATION_CPP_*/
