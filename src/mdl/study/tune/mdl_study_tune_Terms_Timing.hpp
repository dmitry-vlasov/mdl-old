/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_tune_Terms_Timing.hpp                          */
/* Description:     a class with a time estimation for tuning algorithm      */
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

class Terms :: Timing :
	public object :: Object,
	public Scalar<Terms :: Timing> {
public :
	Timing
	(
		Format&,
		const Terms*,
		const value :: Real percent,
		const value :: Real maxThreshold
	);
	virtual ~ Timing();

	Time estimate
	(
		const value :: Real percent,
		const value :: Real maxThreshold
	) const;
	Time operator () (const value :: Real percent) const;

	void show (const bool = false);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	Time estimateOneIteration (const value :: Real percent, const value :: Real threshold) const;
	Time estimateFinalLearningTime (const value :: Real percent, const value :: Real threshold) const;
	void showEstimatedIterationTimes (String&, const value :: Real percent, const value :: Real threshold) const;
	void showEstimatedFinalLearningTimes (String&, const value :: Real percent) const;

	Format format_;
	const Terms* tuner_;
	mutable value :: Real percent_;
	const value :: Real maxThreshold_;
};

}
}
}


