/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_benchmark_Benchmark.cpp                        */
/* Description:     benchmarking algorithm                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_BENCHMARK_BENCHMARK_CPP_
#define MDL_STUDY_BENCHMARK_BENCHMARK_CPP_

namespace mdl {
namespace study {
namespace benchmark {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Benchmark :: Benchmark (Format&  format) :
	format_ (format),
	subFormat_ (format_, true),
	sample_ (new Sample (subFormat_)),
	fris_ (new Fris (subFormat_)),
	optimization_ (new Optimization (subFormat_))
	{
		if (benchmark_ != NULL) {
			std :: cout << std :: endl;
			std :: cout << "doube initialization of benchmarking class" << std :: endl;
			throw std :: exception();
		}
		benchmark_ = this;
	}
	Benchmark :: ~ Benchmark()
	{
		deleteAggregateObject (sample_);
		deleteAggregateObject (fris_);
		deleteAggregateObject (optimization_);
	}

	inline Benchmark*
	Benchmark :: get() {
		return benchmark_;
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: mode;

	void
	Benchmark :: benchmark (Time& timeLimit, const bool write)
	{
		format_.message() << "benchmarking";
		format_.showStart (timeLimit);

		Time limit = timeLimit;

		Time limit_0 = limit * timeFractions_ [SAMPLE];
		limit -= limit_0;
		benchmarkSample (limit_0);
		limit += limit_0;

		Time limit_1 = limit * timeFractions_ [FRIS];
		limit -= limit_1;
		benchmarkFris (limit_1);
		limit += limit_1;

		Time limit_2 = limit * timeFractions_ [OPTIMIZATION];
		limit -= limit_2;
		benchmarkOptimization (limit_2);
		limit += limit_2;

		if (write) {
			writeOptions();
		}
		format_.showFinal();
		timeLimit -= format_.getTimer().getSeconds();

		if (write) {
			writeOptions();
		}
	}
	bool
	Benchmark :: isDone() const
	{
		if (!sample_->isDone()) {
			return false;
		}
		if (!fris_->isDone()) {
			return false;
		}
		if (!optimization_->isDone()) {
			return false;
		}
		return true;
	}

	const Sample*
	Benchmark :: sample() const {
		return sample_;
	}
	const Fris*
	Benchmark :: fris() const {
		return fris_;
	}
	const Optimization*
	Benchmark :: optimization() const {
		return optimization_;
	}

	// object :: Object implementation
	void
	Benchmark :: commitSuicide() {
		delete this;
	}
	Size_t
	Benchmark :: getVolume() const
	{
		Size_t volume = 0;
		volume += format_.getVolume();
		volume += subFormat_.getVolume();
		volume += getAggregateVolume (sample_);
		volume += getAggregateVolume (fris_);
		volume += getAggregateVolume (optimization_);
		return volume;
	}
	Size_t
	Benchmark :: getSizeOf() const {
		return sizeof (Benchmark);
	}
	void
	Benchmark :: show (String&) const {
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Benchmark :: benchmarkSample (Time& timeLimit)
	{
		subFormat_.message() << "benchmarking sample build";
		subFormat_.showStart (timeLimit);
		sample_->benchmark (timeLimit);
		subFormat_.showFinal();
	}
	void
	Benchmark :: benchmarkFris (Time& timeLimit)
	{
		subFormat_.message() << "benchmarking leaf terms";
		subFormat_.showStart (timeLimit);
		fris_->benchmark (timeLimit);
		subFormat_.showFinal();
	}
	void
	Benchmark :: benchmarkOptimization (Time& timeLimit)
	{
		subFormat_.message() << "benchmarking optimization";
		subFormat_.showStart (timeLimit);
		optimization_->benchmark (timeLimit);
		subFormat_.showFinal();
	}

	void
	Benchmark :: writeOptions() const
	{
		if (Config :: getTarget().isUndefined()) {
			return;
		}
		Config :: target().provideDirectory();
		Output output (Config :: getTarget().getString().c_str());
		output.open();

		sample_->writeOptions (output.buffer());
		fris_->writeOptions (output.buffer());
		optimization_->writeOptions (output.buffer());

		output.buffer() << " " << endLine;
		output.close();
	}

	/*********************************
	 *		Private static members
	 *********************************/

	value :: Real Benchmark :: timeFractions_ [STEPS_NUM] =
	{
		0.2, // SAMPLE
		0.2, // FRIS
		0.6  // OPTIMIZATION
	};
	Benchmark* Benchmark :: benchmark_ = NULL;
}
}
}

#endif /*MDL_STUDY_BENCHMARK_BENCHMARK_CPP_*/
