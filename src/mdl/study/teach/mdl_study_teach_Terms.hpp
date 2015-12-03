/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_teach_Terms.hpp                                */
/* Description:     teaching leaf terms                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_TEACH_TERMS_HPP_
#define MDL_STUDY_TEACH_TERMS_HPP_

#include "mdl/interface/mdl_interface.hpp"

namespace mdl {
namespace study {
namespace teach {

class Terms :
	public object :: Object,
	public Scalar<Terms> {
public :
	Terms (Format&, Sample*);
	virtual ~ Terms();

	void teach
	(
		Time& timeLimit,
		const value :: Integer threshold,
		const bool evalFitness = true
	);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	friend class tune :: Terms;

	typedef
		vector :: value :: Integer
		Vector_;
	typedef
		set :: value :: Integer
		Set_;

#ifdef MULTY_THREADED
	friend void* teachAllInThread (void* pointer);
	friend void* teachSampleInThread (void* pointer);
	struct Arguments_ {
		Arguments_() :
		threadIndex_ (0),
		threadCount_ (0),
		threshold_ (0),
		sample_ (NULL),
		subFormat_ (NULL) {
		}
		~ Arguments_ ()
		{
			if (subFormat_ != NULL) {
				delete subFormat_;
			}
		}
		int threadIndex_;
		int threadCount_;
		int threshold_;
		Time timeLimit_;
		Sample* sample_;
		Format* subFormat_;
	};
	void teachMultiThreaded
	(
		void* func (void*),
		Time timeLimit,
		const value :: Integer threshold
	);
#endif

	void teachAll (Time timeLimit, const value :: Integer threshold);
	void teachSample (Time timeLimit, const value :: Integer threshold);

	void teachAllSingleThreaded (Time timeLimit, const value :: Integer threshold);
	void teachSampleSingleThreaded (Time timeLimit, const value :: Integer threshold);

	static void teachProposition
	(
		Time timeLimit,
		mdl :: Proposition*,
		const value :: Integer threshold,
		Format* subFormat
	);
	static void teachTerm
	(
		Time timeLimit,
		mdl :: evaluation :: Term* term,
		statement :: Experience* experience,
		const value :: Integer threshold,
		Format* subFormat
	);

	Format  format_;
	Format  subFormat_;
	Sample* sample_;
};

#ifdef MULTY_THREADED
	void* teachAllInThread (void* pointer);
	void* teachSampleInThread (void* pointer);
#endif

}
}
}

#endif /*MDL_STUDY_TEACH_TERMS_HPP_*/
