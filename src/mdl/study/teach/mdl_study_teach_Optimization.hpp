/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_teach_Optimization.hpp                         */
/* Description:     optimizing parameters                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_TEACH_OPTIMIZATION_HPP_
#define MDL_STUDY_TEACH_OPTIMIZATION_HPP_

#include "mdl/interface/mdl_interface.hpp"

namespace mdl {
namespace study {
namespace teach {

const value :: Real DEFAULT_QUANTUM = 0.2;
const value :: Real DEFAULT_GROUPING = 1;

class Optimization :
	public object :: Object,
	public Scalar<Optimization> {
public :
	typedef
		vector :: value :: Integer
		Vector_;
	typedef
		allocator :: Heap
		Allocator_;
	typedef
		sampler :: Sample<Allocator_>
		Sample_;
	typedef
		sampler :: Sampler<Allocator_>
		Sampler_;

	Optimization (Format&, Sample*);
	virtual ~ Optimization();

	value :: Real teach
	(
		Time& timeLimit,
		const value :: Real      quantum = DEFAULT_QUANTUM,
		const value :: Integer   grouping = DEFAULT_GROUPING,
		const Sample_* sample = NULL
	);

	value :: Real evalFitness
	(
		const value :: Real quantum,
		const value :: Integer grouping = DEFAULT_GROUPING,
		Sampler_ :: Mode_ mode = Sampler_ :: DEFAULT_MODE
	);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	friend class tune :: Grouping;
	friend class tune :: Precision;

	typedef
		form :: evaluation :: function :: WeightedSum :: Description_
		Description_;
	typedef
		form :: evaluation :: function :: WeightedSum :: DescriptionVector_
		DescriptionVector_;

	value :: Real justTeach
	(
		Time& timeLimit,
		const value :: Real      quantum  = DEFAULT_QUANTUM,
		const value :: Integer   grouping = DEFAULT_GROUPING,
		const Sample_* sample = NULL
	);
	value :: Real optimizeGroup
	(
		const value :: Real quantum,
		const value :: Integer group,
		const Sample_* = NULL
	);

	void setParameter
	(
		const value :: Integer group,
		const value :: Integer index,
		const value :: Real parameter
	);
	value :: Real getParameter
	(
		const value :: Integer group,
		const value :: Integer index
	);

	void computeBoundaries (const value :: Integer grouping);
	value :: Integer computeSumRate() const;

	Format format_;
	const value :: Integer maxGrouping_;
	const value :: Integer dimension_;
	const DescriptionVector_* descriptionVector_;
	Vector_ boundaries_;
	Sample* sample_;
};

}
}
}

#endif /*MDL_STUDY_TEACH_OPTIMIZATION_HPP_*/
