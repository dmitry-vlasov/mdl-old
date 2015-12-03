/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_tune_Terms.hpp                                 */
/* Description:     teaching terms                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_TUNE_TERMS_HPP_
#define MDL_STUDY_TUNE_TERMS_HPP_

#include "mdl/interface/mdl_interface.hpp"

namespace mdl {
namespace study {
namespace tune {

class Terms :
	public object :: Object,
	public Scalar<Terms> {
public :
	enum {
		THRESHOLD_MIN = 1,       // %
		THRESHOLD_MAX = 100,     // %
		THRESHOLD_CYCLES = 2, // 10,
		THRESHOLD_STEP = 1
	};

	Terms
	(
		Format&,
		Sample*
	);
	virtual ~ Terms();

	value :: Integer tune (Time& timeLimit);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	class Timing;
	class Estimating;
	friend class Timing;

	typedef
		vector :: value :: Integer
		Vector_;

#ifdef MULTY_THREADED
	friend void* tuneInThread (void* pointer);
	struct Arguments_ {
		Arguments_() :
		threadIndex_ (0),
		threadCount_ (0),
		percent_ (0),
		threshold_ (0),
		sample_ (NULL),
		subSubFormat_ (NULL) {
		}
		~ Arguments_ ()
		{
			if (subSubFormat_ != NULL) {
				delete subSubFormat_;
			}
		}
		int threadIndex_;
		int threadCount_;
		double percent_;
		double threshold_;
		Sample* sample_;
		Format* subSubFormat_;
	};
	struct Result_ {
		Result_
		(
			const value :: Real fitness,
			const value :: Integer counter,
			Error* error
		) :
		fitness_ (fitness),
		counter_ (counter),
		error_ (error) {
		}
		value :: Real fitness_;
		value :: Integer counter_;
		Error* error_;
	};
	value :: Real evalFitnessMultyThreaded (const value :: Real threshold);
#endif

	value :: Real evalFitness (const value :: Real threshold);
	value :: Real evalFitnessSingleThreaded (const value :: Real threshold);

	static void evalTermFitness
	(
		mdl :: evaluation :: Term* term,
		statement :: Experience* experience,
		value :: Real percent,
		value :: Real threshold,
		value :: Real& sumFitness,
		value :: Integer& counter
	);

	Format format_;
	Format subFormat_;
	Format subSubFormat_;

	const Sample* sample_;
	teach :: Terms* teacher_;

	// tuning parameters
	Estimating* estimating_;
	value :: Real percent_;
	value :: Real maxThreshold_;

	// learning parameters
	value :: Integer optimalThreshold_;
};

#ifdef MULTY_THREADED
	void* tuneInThread (void* pointer);
#endif

}
}
}

#endif /*MDL_STUDY_TUNE_TERMS_HPP_*/
