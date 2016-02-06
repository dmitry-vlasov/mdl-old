/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_tune_Tuner.hpp                                 */
/* Description:     a class with a tuning (meta-learning) algorithm          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"

namespace mdl {
namespace study {
namespace tune {

class Tuner :
	public object :: Object,
	public Scalar<Tuner> {
public :
	Tuner (Format& format);
	virtual ~ Tuner();

	void tune (Time& timeLimit);

	value :: Integer getOptimalThreshold() const;
	value :: Integer getOptimalPrecision() const;
	value :: Integer getOptimalGrouping() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	class Timing;
	class Estimating;

	friend class Timing;
	friend class Estimating;

	void buildSample (Time& timeLimit, const value :: Integer sampleSize);
	void tuneLeafs (Time& timeLimit);
	void tuneOptimization (Time& timeLimit);

	void writeOptions() const;

	Format  format_;
	Benchmark* benchmark_;

	Sample* sample_;
	tune :: Terms*     termTuner_;
	tune :: Precision* precisionTuner_;
	tune :: Grouping*  groupingTuner_;

	// tuning parameters
	Estimating* estimating_;
	value :: Integer sampleSize_;
	value :: Integer maxPrecision_;

	// learning parameters
	value :: Integer optimalThreshold_;
	value :: Integer optimalPrecision_;
	value :: Integer optimalGrouping_;

	static value :: Real stepTimeFractions_  [STEPS_NUM];
	static value :: Real phaseTimeFractions_ [PHASES_NUM];
};

}
}
}


