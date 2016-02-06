/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_tune_Precision.hpp                             */
/* Description:     tuning of precision for optimization                     */
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

class Precision :
	public object :: Object,
	public Scalar<Precision> {
public :
	Precision (Format&, Sample*);
	virtual ~ Precision();

	value :: Integer tune (Time& timeLimit, const value :: Integer maxPrecision);

	static Time estimateTime
	(
		const value :: Integer sampleSize,
		const value :: Integer maxPrecision
	);
	static void showEstimatedTimes
	(
		String& string,
		const Format& format,
		const value :: Integer sampleSize,
		const value :: Integer maxPrecision
	);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	typedef
		allocator :: Heap
		Allocator_;
	typedef
		sampler :: Sampler<Allocator_>
		Sampler_;

	Format format_;
	Format subFormat_;
	Format subSubFormat_;
	teach :: Optimization* teacher_;
	value :: Integer optimalPrecision_;
};

}
}
}


