/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_benchmark_Fris.cpp                             */
/* Description:     benchmarking FRiS learning                               */
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
namespace benchmark {

	/****************************
	 *		Public members
	 ****************************/

	Fris :: Fris (Format& format) :
	format_ (format),
	subFormat_ (format_, true),
	countVector_ (COUNT_VECTOR_SIZE),

	createData1_ (),
	teachData1_ (),
	teachData2_ (),
	resultData1_ (),
	deleteData1_ (),

	createTimePolynomialX_ (NULL),
	teachTimePolynomialX_ (NULL),
	teachTimePolynomialXY_ (NULL),
	resultTimePolynomialX_ (NULL),
	deleteTimePolynomialX_ (NULL)
	{
		format_.setPrintableSubformat();
		for (value :: Integer i = 0; i < COUNT_VECTOR_SIZE; ++ i) {
			countVector_.add (0);
		}

		const nstd :: String<>*
			polynomialString = Config :: getString (optionCreateTimeX_);
		if (polynomialString != NULL) {
			const char* string = polynomialString->c_str();
			createTimePolynomialX_ = new Polynomial_1_ (string);
		}
		polynomialString = Config :: getString (optionTeachTimeX_);
		if (polynomialString != NULL) {
			const char* string = polynomialString->c_str();
			teachTimePolynomialX_ = new Polynomial_1_ (string);
		}
		polynomialString = Config :: getString (optionTeachTimeXY_);
		if (polynomialString != NULL) {
			const char* string = polynomialString->c_str();
			teachTimePolynomialXY_ = new Polynomial_2_ (string);
		}
		polynomialString = Config :: getString (optionResultTimeX_);
		if (polynomialString != NULL) {
			const char* string = polynomialString->c_str();
			resultTimePolynomialX_ = new Polynomial_1_ (string);
		}
		polynomialString = Config :: getString (optionDeleteTimeX_);
		if (polynomialString != NULL) {
			const char* string = polynomialString->c_str();
			deleteTimePolynomialX_ = new Polynomial_1_ (string);
		}
	}
	Fris :: ~ Fris()
	{
		deleteAggregateObject (createTimePolynomialX_);
		deleteAggregateObject (teachTimePolynomialX_);
		deleteAggregateObject (teachTimePolynomialXY_);
		deleteAggregateObject (resultTimePolynomialX_);
		deleteAggregateObject (deleteTimePolynomialX_);
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: mode;
using manipulator :: tab;

	void
	Fris :: benchmark (Time& timeLimit)
	{
		format_.message() << "FRiS benchmarking";
		format_.showStart (timeLimit);
		lexp :: Teacher :: init();

		Math :: propositions()->sortByExpSize();

		const int maxSize =
				Math :: propositions()->getDescending (0)->getExperience()->getSize();
		const int maxIndex =
				Math :: propositions()->getSize();

		for (int k = 0; ((k <= maxSize) || (k < maxIndex)); ++ k)
		{
			for (index :: Assertion size = 1; size < k; ++ size) {
				if (!benchmarkPair (k, size)) {
					break;
				}
			}
			for (index :: Assertion index = 0; index <= k; ++ index) {
				if (!benchmarkPair (index, k)) {
					break;
				}
			}
			if (format_.getTimer().getSeconds() > timeLimit) {
				break;
			}
		}
		Math :: propositions()->sortByRate();

		createTimePolynomialX_ = createData1_.interpolate();
		teachTimePolynomialX_ = teachData1_.interpolate();
		teachTimePolynomialXY_ = teachData2_.interpolate();
		resultTimePolynomialX_ = resultData1_.interpolate();
		deleteTimePolynomialX_ = deleteData1_.interpolate();

		format_.message() << "fris create polynomial(x): " << *createTimePolynomialX_;
		format_.showMessage();
		format_.message() << "fris teach polynomial(x): " << *teachTimePolynomialX_;
		format_.showMessage();
		format_.message() << "fris teach polynomial(x,y): " << endLine;
		teachTimePolynomialXY_->show (format_.message(), false, format_.getDepth() + 1);
		format_.showMessage();
		format_.message() << "fris result polynomial(x): " << *resultTimePolynomialX_;
		format_.showMessage();
		format_.message() << "fris delete polynomial(x): " << *deleteTimePolynomialX_;
		format_.showMessage();

		format_.showFinal();
		lexp :: Teacher :: release();
		timeLimit -= format_.getTimer().getSeconds();
	}
	bool
	Fris :: isDone() const
	{
		if (createTimePolynomialX_ == NULL) {
			return false;
		}
		if (teachTimePolynomialX_ == NULL) {
			return false;
		}
		if (teachTimePolynomialXY_ == NULL) {
			return false;
		}
		if (resultTimePolynomialX_ == NULL) {
			return false;
		}
		if (deleteTimePolynomialX_ == NULL) {
			return false;
		}
		return true;
	}

	inline const Fris :: Polynomial_1_*
	Fris :: getCreateTimePolynomialX() const {
		return createTimePolynomialX_;
	}
	inline const Fris :: Polynomial_1_*
	Fris :: getTeachTimePolynomialX() const {
		return teachTimePolynomialX_;
	}
	inline const Fris :: Polynomial_2_*
	Fris :: getTeachTimePolynomialXY() const {
		return teachTimePolynomialXY_;
	}
	inline const Fris :: Polynomial_1_*
	Fris :: getResultTimePolynomialX() const {
		return resultTimePolynomialX_;
	}
	inline const Fris :: Polynomial_1_*
	Fris :: getDeleteTimePolynomialX() const {
		return deleteTimePolynomialX_;
	}

	void
	Fris :: writeOptions (String& output) const
	{
		String polynomialString (1024);
		option :: String stringOption;
		if (createTimePolynomialX_ != NULL) {
			createTimePolynomialX_->show (polynomialString);
			stringOption.name() = optionCreateTimeX_;
			stringOption.value() = polynomialString;
			stringOption.show (output);
			output << " " << endLine;
		}
		polynomialString.clear();

		if (teachTimePolynomialX_ != NULL) {
			teachTimePolynomialX_->show (polynomialString);
			stringOption.name() = optionTeachTimeX_;
			stringOption.value() = polynomialString;
			stringOption.show (output);
			output << " " << endLine;
		}
		polynomialString.clear();

		if (teachTimePolynomialXY_ != NULL) {
			teachTimePolynomialXY_->show (polynomialString);
			stringOption.name() = optionTeachTimeXY_;
			stringOption.value() = polynomialString;
			stringOption.show (output);
			output << " " << endLine;
		}
		polynomialString.clear();

		if (resultTimePolynomialX_ != NULL) {
			resultTimePolynomialX_->show (polynomialString);
			stringOption.name() = optionResultTimeX_;
			stringOption.value() = polynomialString;
			stringOption.show (output);
			output << " " << endLine;
		}
		polynomialString.clear();

		if (deleteTimePolynomialX_ != NULL) {
			deleteTimePolynomialX_->show (polynomialString);
			stringOption.name() = optionDeleteTimeX_;
			stringOption.value() = polynomialString;
			stringOption.show (output);
			output << " " << endLine;
		}
		polynomialString.clear();
	}

using manipulator :: endLine;
using manipulator :: tab;

	// object :: Object implementation
	void
	Fris :: commitSuicide() {
		delete this;
	}
	Size_t
	Fris :: getVolume() const
	{
		Size_t volume = 0;
		volume += format_.getVolume();
		volume += subFormat_.getVolume();
		volume += countVector_.getVolume();

		volume += createData1_.getVolume();
		volume += teachData1_.getVolume();
		volume += teachData2_.getVolume();
		volume += resultData1_.getVolume();
		volume += deleteData1_.getVolume();

		volume += getAggregateVolume (createTimePolynomialX_);
		volume += getAggregateVolume (teachTimePolynomialX_);
		volume += getAggregateVolume (teachTimePolynomialXY_);
		volume += getAggregateVolume (resultTimePolynomialX_);
		volume += getAggregateVolume (deleteTimePolynomialX_);
		return volume;
	}
	Size_t
	Fris :: getSizeOf() const {
		return sizeof (Fris);
	}
	void
	Fris :: show (String& string) const
	{
		string << "FRiS teaching timings:" << endLine;
		string << "create " << createData1_;
		string << "teach " << teachData1_;
		string << "teach2 " << teachData2_;
		string << "result " << resultData1_;
		string << "delete " << deleteData1_;
		string << endLine;
	}

	/****************************
	 *		Private members
	 ****************************/

	bool
	Fris :: benchmarkPair
	(
		const index :: Assertion index,
		const value :: Integer size
	)
	{
		if (index + 1 > Math :: propositions()->getSize()) {
			return false;
		}
		if (MAX_COUNT_PER_SIZE < countVector_ [size]) {
			return true;
		} else {
			++ countVector_ [size];
		}
		const value :: Name name = Config :: experience();
		mdl :: Proposition*
			proposition = Math :: propositions()->getDescending (index);
		proposition->getAssertion()->getEvaluation (name);
		statement :: Experience*
			experience = proposition->getExperience();
		const value :: Integer
			experienceSize = experience->getSize();
		if (size > experienceSize) {
			return false;
		}
		subFormat_.message() << "FRiS time for ";
		subFormat_.message() << "(" ;
		proposition->getAssertion()->replicateName (subFormat_.message());
		subFormat_.message() << "), i = " << index << ", ";
		subFormat_.message() << "size = " << size << ", ";
		subFormat_.showStart();
		benchmarkExperience (experience, size);
		subFormat_.showFinal();
		return true;
	}
	void
	Fris :: benchmarkExperience
	(
		statement :: Experience* experience,
		const value :: Integer size
	)
	{
		Timer createTimer;
		createTimer.start();
		lexp :: Teacher* teacher  = new lexp :: Teacher (experience, size);
		createTimer.stop();
		createData1_.add (size, createTimer.getSeconds());

		const value :: Integer threshold = Config :: getInteger (Config :: THRESHOLD);

		Timer teachTimer;
		teachTimer.start();
		teacher->teach (threshold, false);
		teachTimer.stop();
		teachData1_.add (size, teachTimer.getSeconds());

		benchmarkTeaching (teacher, size);

		Timer resultTimer;
		resultTimer.start();
		FrisFunc_* func = teacher->createResult();
		resultTimer.stop();
		resultData1_.add (size, resultTimer.getSeconds());

		func->commitSuicide();

		Timer deleteTimer;
		deleteTimer.start();
		teacher->commitSuicide();
		deleteTimer.stop();
		deleteData1_.add (size, deleteTimer.getSeconds());
	}
	void
	Fris :: benchmarkTeaching
	(
		lexp :: Teacher* teacher,
		const value :: Integer size
	)
	{
		const value :: Real step =
			(tune :: Terms :: THRESHOLD_MAX - tune :: Terms :: THRESHOLD_MIN) / tune :: Terms :: THRESHOLD_CYCLES;
		for (
			value :: Real threshold = tune :: Terms :: THRESHOLD_MIN;
			threshold <= tune :: Terms :: THRESHOLD_MAX;
			threshold += step
			)
		{
			Timer teachTimer;
			teachTimer.start();
			teacher->teach (threshold, false);
			teachTimer.stop();
			teachData2_.add (size, threshold, teachTimer.getSeconds());
		}
	}

	/********************************
	 *		Private static members
	 ********************************/

	const char* Fris :: optionCreateTimeX_ = "fris_create_time_polynomial_x";
	const char* Fris :: optionTeachTimeX_  = "fris_teach_time_polynomial_x";
	const char* Fris :: optionTeachTimeXY_ = "fris_teach_time_polynomial_x_y";
	const char* Fris :: optionResultTimeX_ = "fris_result_time_polynomial_x";
	const char* Fris :: optionDeleteTimeX_ = "fris_delete_time_polynomial_x";
}
}
}


