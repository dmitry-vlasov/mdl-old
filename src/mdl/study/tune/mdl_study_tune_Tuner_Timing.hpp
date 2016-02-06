/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_tune_Tuner_Timing.hpp                          */
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

class Tuner :: Timing :
	public object :: Object,
	public Scalar<Tuner :: Timing> {
public :
	Timing
	(
		Format&,
		const value :: Integer sampleSize,
		const value :: Integer maxPrecision
	);
	virtual ~ Timing();

	static Time estimate
	(
		const value :: Integer sampleSize,
		const value :: Integer maxPrecision
	);
	Time operator () (const value :: Integer sampleSize) const;

	void show (const bool full);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	Format format_;
	mutable value :: Integer sampleSize_;
	const value :: Integer maxPrecision_;
};

}
}
}


