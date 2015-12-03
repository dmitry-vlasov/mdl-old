/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_benchmark_Optimization.cpp                     */
/* Description:     time estimation polynomials evaluation                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_BENCHMARK_OPTIMIZATION_CPP_
#define MDL_STUDY_BENCHMARK_OPTIMIZATION_CPP_

namespace mdl {
namespace study {
namespace benchmark {

	/****************************
	 *		Public members
	 ****************************/

	Optimization :: Optimization (Format& format) :
	format_ (format),
	subFormat_ (format_, true),
	timeData1_ (),
	timeData2_ (),
	timePolynomialX_ (NULL),
	timePolynomialXY_ (NULL),
	sizeVector_ (INITIAL_SAMPLE_VECTOR_CAPACITY),
	sampleVector_ (INITIAL_SAMPLE_VECTOR_CAPACITY)
	{
		const nstd :: String<>*
			polynomialString = Config :: getString (optionTimeX_);
		if (polynomialString != NULL) {
			const char* string = polynomialString->c_str();
			timePolynomialX_ = new Polynomial_1_ (string);
		}
		polynomialString = Config :: getString (optionTimeXY_);
		if (polynomialString != NULL) {
			const char* string = polynomialString->c_str();
			timePolynomialXY_ = new Polynomial_2_ (string);
		}
	}
	Optimization :: ~ Optimization()
	{
		deleteAggregateObject (timePolynomialX_);
		deleteAggregateObject (timePolynomialXY_);
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: mode;
using manipulator :: tab;

	void
	Optimization :: benchmark (Time& timeLimit)
	{
		format_.message() << "optimization benchmarking";
		format_.showStart (timeLimit);

		for (int k = 0; (k < SAMPLE_SIZE_MAX) || (k < tune :: PRECISION_MAX); ++ k)
		{
			for (index :: Assertion size = 1; size < k; ++ size) {
				if (!benchmarkSizePrecision (size, k, timeLimit)) {
					break;
				}
			}
			for (index :: Assertion precision = 1; precision <= k; ++ precision) {
				if (!benchmarkSizePrecision (k, precision, timeLimit)) {
					break;
				}
			}
			if (format_.getTimer().getSeconds() > timeLimit) {
				break;
			}
		}
		timePolynomialX_ = timeData1_.interpolate();
		timePolynomialXY_ = timeData2_.interpolate();
		format_.message() << "polynomial(x): " << *timePolynomialX_;
		format_.showMessage();
		format_.message() << "polynomial(x,y): " << endLine;
		timePolynomialXY_->show (format_.message(), false, format_.getDepth() + 1);
		format_.showMessage();
		format_.showFinal();
		timeLimit -= format_.getTimer().getSeconds();
	}
	bool
	Optimization :: isDone() const
	{
		if (timePolynomialX_ == NULL) {
			return false;
		}
		if (timePolynomialXY_ == NULL) {
			return false;
		}
		return true;
	}

	inline const Optimization :: Polynomial_1_*
	Optimization :: getTimePolynomialX() const {
		return timePolynomialX_;
	}
	inline const Optimization :: Polynomial_2_*
	Optimization :: getTimePolynomialXY() const {
		return timePolynomialXY_;
	}

	void
	Optimization :: writeOptions (String& output) const
	{
		String polynomialString (1024);
		option :: String stringOption;
		if (timePolynomialX_ != NULL) {
			timePolynomialX_->show (polynomialString);
			stringOption.name() = optionTimeX_;
			stringOption.value() = polynomialString;
			stringOption.show (output);
			output << " " << endLine;
		}
		polynomialString.clear();

		if (timePolynomialXY_ != NULL) {
			timePolynomialXY_->show (polynomialString);
			stringOption.name() = optionTimeXY_;
			stringOption.value() = polynomialString;
			stringOption.show (output);
			output << " " << endLine;
		}
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
		volume += format_.getVolume();
		volume += subFormat_.getVolume();
		volume += timeData1_.getVolume();
		volume += timeData2_.getVolume();
		volume += getAggregateVolume (timePolynomialX_);
		volume += getAggregateVolume (timePolynomialXY_);
		volume += sizeVector_.getVolume();
		volume += sampleVector_.getVolume();
		return volume;
	}
	Size_t
	Optimization :: getSizeOf() const {
		return sizeof (Optimization);
	}
	void
	Optimization :: show (String& string) const
	{
		string << "root term teaching timings:" << endLine;
		string << timeData1_ << endLine;
		string << endLine;
	}

	/****************************
	 *		Private members
	 ****************************/

	bool
	Optimization :: benchmarkSizePrecision
	(
		const value :: Integer size,
		const value :: Integer precision,
		Time timeLimit
	)
	{
		if (precision > tune :: PRECISION_MAX) {
			return false;
		}
		if (size > SAMPLE_SIZE_MAX) {
			return false;
		}
		const value :: Real quantum = 1 / static_cast<value :: Real>(precision);

		study :: Sample* sample = findSample (size, timeLimit);

		subFormat_.message() << "benchmarking optimization, ";
		subFormat_.message() << "size = " << size << ", ";
		subFormat_.message() << "precision = " << precision << ", ";
		subFormat_.message() << "quantum = " << quantum << ", ";
		subFormat_.showStart();

		teach :: Optimization teacher (subFormat_, sample);
		teacher.teach (timeLimit, quantum);
		subFormat_.showFinal();

		timeData2_.add (size, precision, subFormat_.getTimer().getSeconds());

		if (quantum == teach :: DEFAULT_QUANTUM) {
			timeData1_.add (size, subFormat_.getTimer().getSeconds());
		}
		return true;
	}
	study :: Sample*
	Optimization :: findSample
	(
		const value :: Integer size,
		Time timeLimit
	)
	{
		for (value :: Integer i = 0; i < sizeVector_.getSize(); ++ i) {
			const value :: Integer s = sizeVector_.getValue (i);
			if (size == s) {
				return sampleVector_.getValue (i);
			}
		}
		study :: Sample* sample = new study :: Sample (format_);
		sample->build (Config :: getInteger (Config :: SAMPLE_SIZE), timeLimit);
		sizeVector_.add (size);
		sampleVector_.add (sample);
		return sample;
	}

	/********************************
	 *		Private static members
	 ********************************/

	const char* Optimization :: optionTimeX_ = "optimization_time_polynomial_x";
	const char* Optimization :: optionTimeXY_ = "optimization_time_polynomial_x_y";
}
}
}

#endif /*MDL_STUDY_BENCHMARK_OPTIMIZATION_CPP_*/
