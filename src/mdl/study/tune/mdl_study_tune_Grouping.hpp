/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_tune_Grouping.hpp                              */
/* Description:     tuning of grouping for optimization                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_TUNE_GROUPING__HPP_
#define MDL_STUDY_TUNE_GROUPING__HPP_

#include "mdl/interface/mdl_interface.hpp"

namespace mdl {
namespace study {
namespace tune {

class Grouping :
	public object :: Object,
	public Scalar<Grouping> {
public :
	Grouping (Format&, Sample*);
	virtual ~ Grouping();

	value :: Integer tune
	(
		Time& timeLimit,
		const value :: Integer optimalPrecision,
		const value :: Integer maxPrecision
	);
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
		vector :: value :: Integer
		Vector_;
	typedef
		allocator :: Heap
		Allocator_;
	typedef
		vector :: Vector
		<
			vector :: value :: Real,
			storage :: ByPointer,
			Allocator_
		>
		Matrix_;
	typedef
		sampler :: Sampler<Allocator_>
		Sampler_;

	void rememberState();
	void recallState();

	Format format_;
	Format subFormat_;
	Format subSubFormat_;
	teach :: Optimization* teacher_;

	value :: Integer optimalPrecision_;
	value :: Integer optimalGrouping_;

	// memory of a learning context state
	Matrix_ memoryParameters_;
	Vector_ memoryBoundaries_;
};

}
}
}

#endif /*MDL_STUDY_TUNE_GROUPING__HPP_*/
