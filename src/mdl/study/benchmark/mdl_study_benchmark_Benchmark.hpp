/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_benchmark_Benchmark.hpp                        */
/* Description:     benchmarking algorithm                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_BENCHMARK_BENCHMARK_HPP_
#define MDL_STUDY_BENCHMARK_BENCHMARK_HPP_

#include "mdl/interface/mdl_interface.hpp"

namespace mdl {
namespace study {
namespace benchmark {

class Benchmark :
	public object :: Object,
	public Scalar<Benchmark> {
public :
	Benchmark (Format&  format);
	virtual ~ Benchmark();

	static Benchmark* get();

	void benchmark (Time& timeLimit, const bool write);
	bool isDone() const;

	const Sample* sample() const;
	const Fris* fris() const;
	const Optimization* optimization() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	enum Steps {
		SAMPLE       = 0,
		FRIS         = 1,
		OPTIMIZATION = 2,
		STEPS_NUM    = 3
	};

	void benchmarkSample (Time&);
	void benchmarkFris (Time&);
	void benchmarkOptimization (Time&);
	void writeOptions() const;

	Format format_;
	Format subFormat_;

	Sample*       sample_;
	Fris*         fris_;
	Optimization* optimization_;

	static value :: Real timeFractions_ [STEPS_NUM];
	static Benchmark* benchmark_;
};

}
}
}

#endif /*MDL_STUDY_BENCHMARK_BENCHMARK_HPP_*/
