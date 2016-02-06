/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_math_Evaluations.hpp                                 */
/* Description:     global container for evaluations                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/math/mdl_math_Container.hpp"

namespace mdl {
namespace math {

class Evaluations :
	public object :: Object,
	public Scalar<Evaluations> {
public :
	Evaluations ();
	virtual ~ Evaluations();
	
	index :: Assertion getSize() const;
	mdl :: Evaluation* get (const index :: Assertion);
	index :: Assertion add (mdl :: Evaluation*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;
	
private :
	typedef
		vector :: Vector
		<
			Evaluation*,
			storage :: ByValue,
			allocator :: Heap
		>
		EvaluationVector_;

	enum {
		INITIAL_EVALUATION_VECTOR_CAPACITY = size :: KILOBYTE * 64
	};

	EvaluationVector_ evaluationVector_;
	pthread_mutex_t mutex_;
};

}
}


