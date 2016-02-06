/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_lexp_Stolp.cpp                                 */
/* Description:     FRiS-stolp learning algorithm                            */
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
	Stolp :: Stolp
	(
		Matrix* matrix,
		const Type_ type
	) :
	type_ (type),
	fris_ (matrix),
	matrix_ (matrix),
	config_ (NUMBER_OF_PARAMETERS),
	posCount_ (0),
	negCount_ (0),
	positive_ (matrix->getSize()),
	negative_ (matrix->getSize()),
	etalonsPos_ (matrix->getSize()),
	etalonsNeg_ (matrix->getSize()),
	isNone_ (false),
	isTrivial_ (false),
	sign_ (true) {
		initConfig();
	}
	Stolp :: ~ Stolp() {
	}

	Stolp :: Fris_*
	Stolp :: createResult() const
	{
		if (isNone_) {
			return new Fris_ (true);
		} else if (isTrivial_) {
			return new Fris_ (sign_);
		} else if (etalonsPos_.getSize() == 0) {
			return new Fris_(false);
		} else if (etalonsNeg_.getSize() == 0) {
			return new Fris_(true);
		} else {
			const value :: Integer
				size = etalonsPos_.getSize() + etalonsNeg_.getSize();
			Fris_* fris = new Fris_ (size);

			for (value :: Integer i = 0; i < etalonsPos_.getSize(); ++ i) {
				const value :: Integer index = etalonsPos_.getValue (i);
				const Point_* point = matrix_->getPoint (index);
				fris->addPoint (point);
			}
			for (value :: Integer i = 0; i < etalonsNeg_.getSize(); ++ i) {
				const value :: Integer index = etalonsNeg_.getValue (i);
				const Point_* point = matrix_->getPoint (index);
				fris->addPoint (point);
			}
			return fris;
		}
	}
	void
	Stolp :: learn (const Sample& trainingSample, Time timeLimit)
	{
		if (matrix_->getSize() == 0) {
			isNone_ = true;
		} else {
			isNone_ = false;
		}
		if (sampleIsTrivial (trainingSample, sign_)) {
			isTrivial_ = true;
		} else {
			isTrivial_ = false;
		}
		runAlgorithm (trainingSample, timeLimit);
	}
	inline void
	Stolp :: learn (const Sample& trainingSample)
	{
		Time timeLimit = mdl :: Config :: getTimeLimit();
		learn (trainingSample, timeLimit);
	}
	value :: Real
	Stolp :: getPercentClassified (const Sample& trainingSample) const
	{
		if (matrix_->getSize() == 0) {
			return 100;
		}
		bool sign = true;
		if (sampleIsTrivial (trainingSample, sign)) {
			return 100;
		}
		const value :: Real
			classified = evalClassifiedSize (trainingSample);
		const value :: Real
			overall = trainingSample.getSize();
		const value :: Real percentClassified = (classified * 100) / overall;
		return percentClassified;
	}

	value :: Real
	Stolp :: evalFitness (const Sample& trainingSample, const Sample& controlSample)
	{
		if ((matrix_->getSize() == 0) ||
			(controlSample.getSize() == 0)) {
			isNone_ = true;
			return 100;
		} else {
			isNone_ = false;
		}
		const value :: Real controlSampleSize = controlSample.getSize();
		value :: Real classified = 0;
		if (sampleIsTrivial (trainingSample, sign_)) {
			for (value :: Integer i = 0; i < controlSampleSize; ++ i) {
				const Point_* point = matrix_->getPoint (i);
				if (point->getSign() == sign_) {
					++ classified;
				}
			}
			isTrivial_ = true;
			return ((controlSampleSize - classified) * 100) / controlSampleSize;
		} else {
			isTrivial_ = false;
			Time timeLimit = mdl :: Config :: getTimeLimit();

			/*if (Counter :: stop()) {
				std :: cout << std :: endl;
				std :: cout << "trainingSample = {";
				for (int i = 0; i < trainingSample.getSize(); ++ i) {
					std :: cout << trainingSample.getValue (i) << ", ";
				}
				std :: cout << "}" << std :: endl;
				std :: cout << "controlSample = {";
				for (int i = 0; i < controlSample.getSize(); ++ i) {
					std :: cout << controlSample.getValue (i) << ", ";
				}
				std :: cout << "}" << std :: endl;
			}*/
			runAlgorithm (trainingSample, timeLimit);

			/*if (Counter :: stop()) {
				std :: cout << "etalonsPos_.getSize() = " << etalonsPos_.getSize() << std :: endl;
				std :: cout << "etalonsNeg_.getSize() = " << etalonsNeg_.getSize() << std :: endl;

				std :: cout << "etalonsPos_ = " << std :: endl;
				std :: cout << "---------------" << std :: endl;
				for (value :: Integer i = 0; i < etalonsPos_.getSize(); ++ i) {
					const value :: Integer index = etalonsPos_.getValue (i);
					const Point_* y = matrix_->getPoint (index);
					std :: cout << "\t" << index << " (+) " << *y << std :: endl;
				}
				std :: cout << std :: endl;

				std :: cout << "etalonsNeg_ = " << std :: endl;
				std :: cout << "---------------" << std :: endl;
				for (value :: Integer i = 0; i < etalonsNeg_.getSize(); ++ i) {
					const value :: Integer index = etalonsNeg_.getValue (i);
					const Point_* y = matrix_->getPoint (index);
					std :: cout << "\t" << index << " (-) " << *y << std :: endl;
				}
				std :: cout << std :: endl;
			}*/

			classified = evalClassifiedSize (controlSample);

			/*const value :: Real
			maxPercentOfSample = config_.getParameter (MAX_ETALONS)->getValue();
			if (Counter :: stop()) {
				std :: cout << "maxPercentOfSample = " << maxPercentOfSample << std :: endl;
				std :: cout << "classified = " << classified << std :: endl;
				std :: cout << *this << std :: endl;
			}*/
			return ((controlSampleSize - classified) * 100) / controlSampleSize;
		}
	}
	Config&
	Stolp :: config() {
		return config_;
	}
	const Config&
	Stolp :: getConfig() const {
		return config_;
	}
	void
	Stolp :: updateConfig (const Config& configuration)
	{
		const value :: Real prevAlpha = config_.getParameter (ALPHA)->getValue();
		const value :: Real newAlpha = configuration.getParameter (ALPHA)->getValue();

		const value :: Real prevBeta = config_.getParameter (BETA)->getValue();
		const value :: Real newBeta = configuration.getParameter (BETA)->getValue();

		const bool rebuildMatrix = (prevAlpha != newAlpha) || (prevBeta != newBeta);
		config_.copy (configuration);
		if (rebuildMatrix) {
			typedef
				form :: evaluation :: lexp :: Factors
				Factors_;
			Factors_ factors (newAlpha, newBeta);
			matrix_->build (factors);
		}
	}

	void
	Stolp :: init()
	{
		if (descriptionArray_  [ALPHA] == NULL) {
			volumeCounted_ = false;

			// fris lambda parameter
			descriptionArray_ [LAMBDA] = new Description_
				(
					Config_ :: hasRealOption ("fris_lambda_default") ? Config_ :: getReal ("fris_lambda_default") : 0.5,
					Config_ :: hasRealOption ("fris_lambda_min")     ? Config_ :: getReal ("fris_lambda_min")     : 0,
					Config_ :: hasRealOption ("fris_lambda_max")     ? Config_ :: getReal ("fris_lambda_max")     : 1,
					Config_ :: hasRealOption ("fris_lambda_quantum") ? Config_ :: getReal ("fris_lambda_quantum") : 0.25,
					"fris_lambda"
				);
			// max number of etalons (in % to the training sample size)
			descriptionArray_ [MAX_ETALONS] = new Description_
				(
					Config_ :: hasRealOption ("fris_max_etalons_default") ? Config_ :: getReal ("fris_max_etalons_default") : 10,
					Config_ :: hasRealOption ("fris_max_etalons_min")     ? Config_ :: getReal ("fris_max_etalons_min")     : 1,
					Config_ :: hasRealOption ("fris_max_etalons_max")     ? Config_ :: getReal ("fris_max_etalons_max")     : 32,
					Config_ :: hasRealOption ("fris_max_etalons_quantum") ? Config_ :: getReal ("fris_max_etalons_quantum") : 1,
					"fris_max_etalons"
				);
			// "the part of the sample, which is classified and "
			//	"is removed for (in % to the classified part of the sample)"
			descriptionArray_ [CLASSIFIED_TO_REMOVE] = new Description_
				(
					Config_ :: hasRealOption ("fris_to_remove_default") ? Config_ :: getReal ("fris_to_remove_default") : 100,
					Config_ :: hasRealOption ("fris_to_remove_min")     ? Config_ :: getReal ("fris_to_remove_min")     : 80,
					Config_ :: hasRealOption ("fris_to_remove_max")     ? Config_ :: getReal ("fris_to_remove_max")     : 100,
					Config_ :: hasRealOption ("fris_to_remove_quantum") ? Config_ :: getReal ("fris_to_remove_quantum") : 1,
					"fris_to_remove"
				);
			// "balance (weight) factor for the distance function"
			descriptionArray_ [ALPHA] = new Description_
				(
					Config_ :: hasRealOption ("fris_alpha_default") ? Config_ :: getReal ("fris_alpha_default") : 0.5,
					Config_ :: hasRealOption ("fris_alpha_min")     ? Config_ :: getReal ("fris_alpha_min")     : 0,
					Config_ :: hasRealOption ("fris_alpha_max")     ? Config_ :: getReal ("fris_alpha_max")     : 1,
					Config_ :: hasRealOption ("fris_alpha_quantum") ? Config_ :: getReal ("fris_alpha_quantum") : 0.25,
					"fris_alpha"
				);
			// "factor for the locality of the distance function"
			descriptionArray_ [BETA] = new Description_
				(
					Config_ :: hasRealOption ("fris_beta_default") ? Config_ :: getReal ("fris_beta_default") : 0.3,
					Config_ :: hasRealOption ("fris_beta_min")     ? Config_ :: getReal ("fris_beta_min")     : 0.1,
					Config_ :: hasRealOption ("fris_beta_max")     ? Config_ :: getReal ("fris_beta_max")     : 0.8,
					Config_ :: hasRealOption ("fris_beta_quantum") ? Config_ :: getReal ("fris_beta_quantum") : 0.1,
					"fris_beta"
				);
		}
	}
	void
	Stolp :: release()
	{
		if (descriptionArray_ [ALPHA] != NULL) {
			for (value :: Integer i = 0; i < NUMBER_OF_PARAMETERS; ++ i) {
				delete descriptionArray_ [i];
				descriptionArray_ [i] = NULL;
			}
		}
	}

using manipulator :: endLine;
using manipulator :: tab;

	// object :: Object implementation
	void
	Stolp :: commitSuicide() {
		delete this;
	}
	Size_t
	Stolp :: getVolume() const
	{
		Size_t volume = 0;
		volume += config_.getVolume();
		volume += positive_.getVolume();
		volume += negative_.getVolume();
		volume += etalonsPos_.getVolume();
		volume += etalonsNeg_.getVolume();
		if (!volumeCounted_ && (descriptionArray_ [ALPHA] != NULL)) {
			for (value :: Integer i = 0; i < NUMBER_OF_PARAMETERS; ++ i) {
				volume += descriptionArray_ [i]->getVolume();
				volume += descriptionArray_ [i]->getSizeOf();
			}
			volumeCounted_ = true;
		}
		return volume;
	}
	Size_t
	Stolp :: getSizeOf() const {
		return sizeof (Stolp);
	}
	void
	Stolp :: show (String& string) const
	{
		if (posCount_ > 0) {
			string << "Positive etalons: " << etalonsPos_.getSize() << " ";
			string << "of " << posCount_ << " = ";
			string << (etalonsPos_.getSize() * 100 / posCount_) << " %"<< endLine;
		}
		if (negCount_ > 0) {
			string << "Negative etalons: " << etalonsNeg_.getSize() << " ";
			string << "of " << negCount_ << " = ";
			string << (etalonsNeg_.getSize() * 100 / negCount_) << " %"<< endLine;
		}
		/*	string << "Number of etalons: " << (etalonsPos_.getSize() + etalonsNeg_.getSize()) << endLine;
			string << "Positive etalons: " << tab;
			for (value :: Integer i = 0; i < etalonsPos_.getSize(); ++ i) {
				const value :: Integer x = etalonsPos_.getValue (i);
				string << x << tab;
			}
			string << endLine;
			string << "Negative etalons:" << tab;
			for (value :: Integer i = 0; i < etalonsNeg_.getSize(); ++ i) {
				const value :: Integer x = etalonsNeg_.getValue (i);
				string << x << tab;
			}
			string << endLine;*/
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Stolp :: runAlgorithm
	(
		const Sample& trainingSample,
		Time timeLimit
	)
	{
		initiate (trainingSample);
		Timer timer;
		timer.start();
		switch (type_) {
		case TYPE_A_ : {
			Sample classified (matrix_->getSize());
			while (positive_.getSize() + negative_.getSize() > 0) {
				iterateEtalonSearch();
				evalClassified (classified);
				positive_.subtract (classified);
				negative_.subtract (classified);
				classified.clear();
				if (timer.getSeconds() > timeLimit) {
					break;
				}
			}
			break;
		}
		case TYPE_B_ : {
			while (evalClassifiedSize() != matrix_->getSize()) {
				iterateEtalonSearch();
				if (timer.getSeconds() > timeLimit) {
					break;
				}
			}
			break;
		}
		case TYPE_MIXED_ : {
			while (continueLearning()) {
				iterateEtalonSearch();
				removeClassified();
				if (timer.getSeconds() > timeLimit) {
					break;
				}
			}
			break;
		}
		}
	}
	value :: Integer
	Stolp :: findEtalon
	(
		const Sample& X,  // current class
		const Sample& Y,  // counter class
		const Sample& etalons
	) const
	{
		value :: Real maxEfficiency = 0;
		bool firstPass = true;
		value :: Integer index = value :: undefined :: INTEGER;
		for (value :: Integer i = 0; i < X.getSize(); ++ i) {
			const value :: Integer ind = X.getValue (i);
			if (etalonsPos_.contains (ind) ||
				etalonsNeg_.contains (ind)) {
				continue;
			}
			const Point_* x = matrix_->getPoint (ind);
			const value :: Real
				defenceCapacity = averageFRiS (ind, X, etalons);
			const value :: Real
				tolerance = averageFRiS (ind, Y, etalons);
			const value :: Real
				efficiency = getLambda() * defenceCapacity + (1 - getLambda()) * tolerance;
			if (firstPass || (efficiency > maxEfficiency)) {
				maxEfficiency = efficiency;
				index = ind;
				firstPass = false;
			}
		}
		return index;
	}
	inline value :: Real
	Stolp :: averageFRiS
	(
		const value :: Integer i,
		const Sample& sample,
		const Sample& etalons
	) const
	{
		value :: Integer count = 0;
		value :: Real sum = 0;
		const Point_* x = matrix_->getPoint (i);
		for (value :: Integer k = 0; k < sample.getSize(); ++ k) {
			const value :: Integer j = sample.getValue (k);
			const Point_* y = matrix_->getPoint (j);
			if (i != j) {
				sum += fris_.evalWithNearestNeibour (i, j, etalons);
				++ count;
			}
		}
		return (count == 0) ? 0 : sum / count;
	}

	void
	Stolp :: initiate()
	{
		positive_.clear();
		negative_.clear();
		etalonsPos_.clear();
		etalonsNeg_.clear();
		for (value :: Integer i = 0; i < matrix_->getSize(); ++ i) {
			const Point_* x = matrix_->getPoint (i);
			if (x->isPositive()) {
				positive_.add (i);
			}
			if (x->isNegative()) {
				negative_.add (i);
			}
		}
		const_cast<value :: Integer&>(posCount_) = positive_.getSize();
		const_cast<value :: Integer&>(negCount_) = negative_.getSize();
		const value :: Integer pos_0 = findEtalon (positive_, negative_, negative_);
		const value :: Integer neg_0 = findEtalon (negative_, positive_, positive_);
		etalonsPos_.add (pos_0);
		etalonsNeg_.add (neg_0);
	}
	void
	Stolp :: initiate (const Sample& sample)
	{
		etalonsPos_.clear();
		etalonsNeg_.clear();
		positive_.clear();
		negative_.clear();
		for (value :: Integer i = 0; i < sample.getSize(); ++ i) {
			const value :: Integer index = sample.getValue (i);
			const Point_* x = matrix_->getPoint (index);
			if (x->isPositive()) {
				positive_.add (index);
			}
			if (x->isNegative()) {
				negative_.add (index);
			}
		}
		const_cast<value :: Integer&>(posCount_) = positive_.getSize();
		const_cast<value :: Integer&>(negCount_) = negative_.getSize();
		const value :: Integer pos_0 = findEtalon (positive_, negative_, negative_);
		const value :: Integer neg_0 = findEtalon (negative_, positive_, positive_);
		etalonsPos_.add (pos_0);
		etalonsNeg_.add (neg_0);
	}
	void
	Stolp :: iterateEtalonSearch()
	{
		if (positive_.getSize() > 0) {
			const value :: Integer pos = findEtalon (positive_, negative_, etalonsNeg_);
			if (pos != value :: undefined :: INTEGER) {
				etalonsPos_.add (pos);
			}
		}
		if (negative_.getSize() > 0) {
			const value :: Integer neg = findEtalon (negative_, positive_, etalonsPos_);
			if (neg != value :: undefined :: INTEGER) {
				etalonsNeg_.add (neg);
			}
		}
	}
	value :: Integer
	Stolp :: evalClassifiedSize() const
	{
		const value :: Integer size = matrix_->getSize();
		Sample classified (size);
		evalClassified (classified);
		return classified.getSize();
	}
	value :: Integer
	Stolp :: evalClassifiedSize (const Sample& controlSample) const
	{
		const value :: Integer maxSize = controlSample.getSize();
		Sample classified (maxSize);
		evalClassified (classified, controlSample);
		return classified.getSize();
	}
	void
	Stolp :: evalClassified (Sample& classified) const
	{
		const value :: Integer size = matrix_->getSize();
		for (value :: Integer i = 0; i < size; ++ i) {
			const Point_* x = matrix_->getPoint (i);
			const bool sign = fris_.classify (i, etalonsPos_, etalonsNeg_);
			if (x->getSign() == sign) {
				classified.add (i);
			}
		}
	}
	void
	Stolp :: evalClassified (Sample& classified, const Sample& controlSample) const
	{
		const value :: Integer size = controlSample.getSize();
		for (value :: Integer i = 0; i < size; ++ i) {
			const value :: Integer index = controlSample.getValue (i);
			const Point_* x = matrix_->getPoint (index);
			const bool sign = fris_.classify (index, etalonsPos_, etalonsNeg_);
			if (x->getSign() == sign) {
				classified.add (index);
				/*if (Counter :: stop (1)) {
					std :: cout << "\t" << index << " (good) = " << *x << std :: endl;
				}*/
			} else {
				/*if (Counter :: stop (1)) {
					std :: cout << "\t" << index << " (BAD) = " << *x << std :: endl;
				}*/
			}
		}
	}
	void
	Stolp :: evalClassified (DotSet_& dotSet) const
	{
		const value :: Integer size = matrix_->getSize();
		for (value :: Integer i = 0; i < size; ++ i) {
			const Point_* x = matrix_->getPoint (i);
			value :: Real frisValue = 0;
			const bool sign = fris_.classify (i, frisValue, etalonsPos_, etalonsNeg_);
			if (x->getSign() == sign) {
				const Dot dot (i, frisValue);
				const value :: Integer c = dotSet.find (dot);
				if (c != value :: undefined :: INTEGER) {
					dotSet.getReference (c).addIndex (i);
				} else {
					dotSet.add (dot);
				}
			}
		}
	}
	bool
	Stolp :: sampleIsTrivial (const Sample& sample, bool& sign) const
	{
		if (sample.isEmpty()) {
			return true;
		}
		const value :: Integer index_0 = sample.getValue (0);
		const Point_* x = matrix_->getPoint (index_0);
		sign = x->getSign();

		for (value :: Integer i = 1; i < sample.getSize(); ++ i) {
			const value :: Integer index = sample.getValue (i);
			const Point_* y = matrix_->getPoint (index);
			if (y->getSign() != sign) {
				return false;
			}
		}
		return true;
	}
	bool
	Stolp :: continueLearning() const
	{
		const value :: Integer
			etalonsCount = etalonsPos_.getSize() + etalonsNeg_.getSize();
		const value :: Integer
			unetalonsCount = positive_.getSize() + negative_.getSize();
		const value :: Integer
			sampleSize = posCount_ + negCount_;

		const value :: Real
			maxPercentOfSample = config_.getParameter (MAX_ETALONS)->getValue();

		const value :: Real
			currentPercentOfSample = static_cast<value :: Real>(etalonsCount * 100) / sampleSize;

		if (currentPercentOfSample >= maxPercentOfSample) {
			return false;
		}
		if (unetalonsCount == 0) {
			return false;
		}
		return true;
	}
	void
	Stolp :: removeClassified()
	{
		const value :: Integer sampleSize = matrix_->getSize();
		DotSet_ classified (sampleSize);
		evalClassified (classified);
		const value :: Integer classifiedSize = classified.getSize();

		const value :: Real
			percentToRemove = config_.getParameter (CLASSIFIED_TO_REMOVE)->getValue();

		const value :: Integer toRemove = classifiedSize * percentToRemove / 100;

		for (value :: Integer i = 0; i < toRemove; ++ i) {
			const value :: Integer j = classified.getSize() - 1 - i;
			const Dot& dot = classified.getReference (j);
			const vector :: Integer* indexes = dot.getIndexes();
			positive_.subtract (*indexes);
			negative_.subtract (*indexes);
		}
	}

	void
	Stolp :: initConfig()
	{
		config_.setParameter (LAMBDA, new Parameter (descriptionArray_ [LAMBDA]));
		config_.setParameter (MAX_ETALONS, new Parameter (descriptionArray_ [MAX_ETALONS]));
		config_.setParameter (CLASSIFIED_TO_REMOVE, new Parameter (descriptionArray_ [CLASSIFIED_TO_REMOVE]));
		config_.setParameter (ALPHA, new Parameter (descriptionArray_ [ALPHA]));
		config_.setParameter (BETA, new Parameter (descriptionArray_ [BETA]));
	}

	inline value :: Real
	Stolp :: getLambda() const {
		return config_.getParameter (LAMBDA)->getValue();
	}

	/************************************
	 *		Private static attributes
	 ************************************/

	Stolp :: Description_*
		Stolp :: descriptionArray_ [NUMBER_OF_PARAMETERS] = {
			NULL, NULL, NULL, NULL, NULL
		};
	bool Stolp :: volumeCounted_ = false;
}
}
}


