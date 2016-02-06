/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_math_Expressions.hpp                                 */
/* Description:     global container for expressions                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace math {

class Expressions :
	public object :: Object,
	public Scalar<Expressions> {
public :
	typedef
		expression :: Tree
		<
			const array :: Expression*,
			storage :: ByValue,
			expression :: node :: container :: Counter
		>
		Tree_;

	// types of expressions: from proofs / assertions
	enum Type_ {
		PROOF     = 0,
		ASSERTION = 1,
		ALL       = 2,
		DEFAULT   = PROOF
	};

	Expressions();
	virtual ~ Expressions();
	
	Tree_* getTree (const Type_ type = DEFAULT);
	void add (const array :: Expression*, const Type_ type);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;
	
private :
	Tree_* treeAll_;       // all expressions
	Tree_* treeProof_;     // expressions from proofs
	Tree_* treeAssertion_; // expressions from assertions

	pthread_mutex_t mutex_;
};

}
}


