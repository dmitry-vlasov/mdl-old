/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_benchmark_Sample.cpp                           */
/* Description:     time estimation for sample building                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_BENCHMARK_SAMPLE_CPP_
#define MDL_STUDY_BENCHMARK_SAMPLE_CPP_

namespace mdl {
namespace study {
namespace benchmark {

	/****************************
	 *		Public members
	 ****************************/

	Sample :: Sample (Format& format) :
	format_ (format),
	subFormat_ (format_, true),
	timeData1_ (),
	timePolynomialX_ (NULL)
	{
		const nstd :: String<>*
			polynomialString = Config :: getString (optionTimeX_);
		if (polynomialString != NULL) {
			const char* string = polynomialString->c_str();
			timePolynomialX_ = new Polynomial_1_ (string);
		}
	}
	Sample :: ~ Sample() {
		deleteAggregateObject (timePolynomialX_);
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: mode;
using manipulator :: tab;

	void
	Sample :: benchmark (Time& timeLimit)
	{
		format_.message() << "sample build benchmarking";
		format_.showStart (timeLimit);

		value :: Real step = SAMPLE_SIZE_STEP;
		value :: Integer size = SAMPLE_SIZE_MIN;
		while (true) {
			subFormat_.message() << "benchmarking sample build, size = " << size;
			subFormat_.showStart();
			study :: Sample sample (subFormat_);
			Time limit = timeLimit;
			sample.build (size, limit);
			subFormat_.showFinal();
			timeData1_.add (size, subFormat_.getTimer().getSeconds());

			size += step;
			if (format_.getTimer().getSeconds() * 3 < timeLimit) {
				step *= 1.5;
			}
			if (size > Math :: assertions()->getTheoremNumber()) {
				break;
			}
			if (format_.getTimer().getSeconds() > timeLimit) {
				break;
			}
		}
		timePolynomialX_ = timeData1_.interpolate();

		//timeData1_.show (format_.message());
		//format_.showMessage();

		format_.message() << "polynomial(x): " << *timePolynomialX_;
		format_.showMessage();

		format_.showFinal();
		timeLimit -= format_.getTimer().getSeconds();
	}
	bool
	Sample :: isDone() const {
		return (timePolynomialX_ != NULL);
	}

	const Sample :: Polynomial_1_*
	Sample :: getTimePolynomialX() const {
		return timePolynomialX_;
	}

	void
	Sample :: writeOptions (String& output) const
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
	}

	// object :: Object implementation
	void
	Sample :: commitSuicide() {
		delete this;
	}
	Size_t
	Sample :: getVolume() const
	{
		Size_t volume = 0;
		volume += format_.getVolume();
		volume += subFormat_.getVolume();
		volume += timeData1_.getVolume();
		volume += getAggregateVolume (timePolynomialX_);
		return volume;
	}
	Size_t
	Sample :: getSizeOf() const {
		return sizeof (Sample);
	}
	void
	Sample :: show (String& string) const
	{
		string << "root term teaching timings:" << endLine;
		string << timeData1_ << endLine;
		string << endLine;
	}

	/********************************
	 *		Private static members
	 ********************************/

	const char* Sample :: optionTimeX_ = "sample_time_polynomial_x";
}
}
}

#endif /*MDL_STUDY_BENCHMARK_SAMPLE_CPP_*/
