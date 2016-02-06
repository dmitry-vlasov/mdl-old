/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_tune_Terms_Estimating.hpp                      */
/* Description:     a class for a complex time estimation                    */
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

class Terms :: Estimating :
	public object :: Object,
	public Scalar<Terms :: Estimating> {
public :
	Estimating (Format&, const Terms*);
	virtual ~ Estimating();

	void estimatePercentAndMaxThreshold (const Time timeLimit);
	value :: Real getPercent() const;
	value :: Real getMaxThreshold() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	enum {
		MAX_THRESHOLD_MIN  = 10,   // %
		MAX_THRESHOLD_MAX  = 100, // %
		MAX_THRESHOLD_STEP = 10   // %
	};

	void evaluateDependency (const Time timeLimit);
	value :: Integer evaluateOptimum() const;

	Format format_;
	Format subFormat_;
	const Terms* tuner_;

	vector :: value :: Real percentVector_;
	vector :: value :: Real maxThresholdVector_;
	value :: Real percent_;
	value :: Real maxThreshold_;
};

}
}
}


