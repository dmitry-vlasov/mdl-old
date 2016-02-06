/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_lexp_Stolp.hpp                                 */
/* Description:     FRiS-Stolp learning algorithm                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/study/lexp/mdl_study_lexp_Fris.hpp"
#include "mdl/study/lexp/mdl_study_lexp_Config.hpp"
#include "mdl/study/lexp/mdl_study_lexp_Dot.hpp"

namespace mdl {
namespace study {
namespace lexp {

class Stolp :
	public object :: Object,
	public Scalar<Stolp> {
public :
	typedef
		typename form :: evaluation :: lexp :: Fris<allocator :: Heap>
		Fris_;

	enum Type_ {
		TYPE_A_ = 0,
		TYPE_B_ = 1,
		TYPE_MIXED_ = 2,
		DEFAULT_TYPE_ = TYPE_A_
	};

	enum Parameters_ {
		ALPHA                = 3,
		BETA                 = 4,
		LAMBDA               = 0,
		CLASSIFIED_TO_REMOVE = 1, // in % to the classified part of the sample
		MAX_ETALONS          = 2, // in % to the training sample size
		NUMBER_OF_PARAMETERS = 5
	};

	Stolp
	(
		Matrix* matrix,
		const Type_ = DEFAULT_TYPE_
	);
	virtual ~ Stolp();

	Fris_* createResult() const;
	void learn (const Sample& trainingSample, Time timeLimit);
	void learn (const Sample& trainingSample);
	value :: Real getPercentClassified (const Sample& trainingSample) const;

	value :: Real evalFitness (const Sample& trainingSample, const Sample& controlSample);
	Config& config();
	const Config& getConfig() const;
	void updateConfig (const Config&);

	static void init();
	static void release();

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	friend class Tuner;

	typedef
		parameter :: array :: Description
		DescriptionArray_;
	typedef
		parameter :: Description
		Description_;
	typedef
		form :: evaluation :: lexp :: Point<allocator :: Heap>
		Point_;
	typedef
		mdl :: set :: Set
		<
			Dot,
			storage :: ByValue,
			allocator :: Heap
		>
		DotSet_;
	typedef
		mdl :: auxiliary :: config :: Config
		Config_;

	void runAlgorithm (const Sample& trainingSample, Time timeLimit);
	value :: Integer findEtalon
	(
		const Sample&,
		const Sample&,
		const Sample&
	) const;
	value :: Real averageFRiS
	(
		const value :: Integer,
		const Sample&,
		const Sample&
	) const;
	void initiate();
	void initiate (const Sample&);
	void iterateEtalonSearch();
	value :: Integer evalClassifiedSize() const;
	value :: Integer evalClassifiedSize (const Sample&) const;
	void evalClassified (Sample&) const;
	void evalClassified (Sample&, const Sample&) const;
	void evalClassified (DotSet_& dotSet) const;
	bool sampleIsTrivial (const Sample&, bool& sign) const;
	bool continueLearning() const;
	void removeClassified();
	void initConfig();

	value :: Real percentOfClassified (const Sample&) const;

	value :: Real getLambda() const;

	const Type_ type_;

	Fris    fris_;
	Matrix* matrix_;
	Config  config_;

	const value :: Integer posCount_;
	const value :: Integer negCount_;

	Sample positive_;
	Sample negative_;
	Sample etalonsPos_;
	Sample etalonsNeg_;

	bool isNone_;
	bool isTrivial_;
	bool sign_;

	static Description_* descriptionArray_ [NUMBER_OF_PARAMETERS];
	static bool volumeCounted_;
};

}
}
}


