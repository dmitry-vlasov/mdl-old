/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_tune_Tuner_Estimating.hpp                      */
/* Description:     a class for a complex time estimation                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_TUNE_TUNER_ESTIMATING_HPP_
#define MDL_STUDY_TUNE_TUNER_ESTIMATING_HPP_

#include "mdl/interface/mdl_interface.hpp"

namespace mdl {
namespace study {
namespace tune {

class Tuner :: Estimating :
	public object :: Object,
	public Scalar<Tuner :: Estimating> {
public :
	Estimating (Format&);
	virtual ~ Estimating();

	bool estimateSizeAndPrecision (const Time timeLimit);
	value :: Integer getSampleSize() const;
	value :: Integer getMaxPrecision() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	enum {
		MAX_PRECISION_MIN  = 3,
		MAX_PRECISION_MAX  = 32,
		MAX_PRECISION_STEP = 1
	};

	void evaluateDependency (const Time timeLimit);
	value :: Integer evaluateOptimum() const;

	Format format_;
	Format subFormat_;

	vector :: value :: Real sizeVector_;
	vector :: value :: Real maxPrecisionVector_;
	value :: Integer sampleSize_;
	value :: Integer maxPrecision_;
};

}
}
}

#endif /*MDL_STUDY_TUNE_TUNER_ESTIMATING_HPP_*/
