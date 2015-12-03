/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_lexp_Uphood.cpp                      */
/* Description:     an uphood of a point in a proof                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_EVALUATION_LEXP_UPHOOD_CPP_
#define MDL_FORM_EVALUATION_LEXP_UPHOOD_CPP_

namespace mdl {
namespace form {
namespace evaluation {
namespace lexp {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Uphood<A> :: Uphood (const mdl :: proof :: Step* step) :
	step_ (step),
	node_ (NULL),
	tree_ (new Tree_()) {
		build();
	}
	template<class A>
	inline
	Uphood<A> :: Uphood (const Node_* node) :
	step_ (NULL),
	node_ (node),
	tree_ (new Tree_()) {
	}
	template<class A>
	inline
	Uphood<A> :: Uphood (const Uphood& uphood) :
	step_ (uphood.step_),
	node_ (uphood.node_),
	tree_ (new Tree_()) {
	}
	template<class A>
	Uphood<A> :: ~ Uphood() {
		deleteAggregateObject (tree_);
	}

	template<class A>
	value :: Real
	Uphood<A> :: getDistance (const Uphood& uphood) const
	{
		Memory :: stack().push();
		value :: Integer minDiffernence = value :: undefined :: INTEGER;
		tree_->factorUnifySymmetric (uphood.tree_, minDiffernence);
		const value :: Real distance =
			(minDiffernence == value :: undefined :: INTEGER) ?
			value :: LARGE :
			minDiffernence;
		Memory :: stack().pop();
		return distance;
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Object implementation
	template<class A>
	void
	Uphood<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Uphood<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (tree_);
		return volume;
	}
	template<class A>
	Size_t
	Uphood<A> :: getSizeOf() const {
		return sizeof (Uphood);
	}
	template<class A>
	void
	Uphood<A> :: show (String& string) const {
 	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	void
	Uphood<A> :: build()
	{
		if (step_ != NULL) {
			build (step_);
		} else if (node_ != NULL) {
			build (node_);
		}
	}
	template<class A>
	void
	Uphood<A> :: build
	(
		const mdl :: proof :: Step* step,
		const value :: Integer depth
	)
	{
		tree_->addBranch (step->getExpression(), depth);
		if (depth + 1 == mdl :: Config :: getDistanceLocalityBoundary()) {
			return;
		}
		for (value :: Integer i = 0; i < step->getUpArity(); ++ i) {
			const mdl :: proof :: Node* node = step->getUp (i);
			const mdl :: proof :: Step*
				upStep = dynamic_cast<const mdl :: proof :: Step*>(node);
			if (upStep == NULL) {
				continue;
			}
			build (upStep, depth + 1);
		}
	}
	template<class A>
	void
	Uphood<A> :: build
	(
		const Node_* node,
		const value :: Integer depth
	)
	{
		if (depth == mdl :: Config :: getDistanceLocalityBoundary()) {
			return;
		}
		typedef
			typename Node_ :: Tree_
			Tree;
		typedef
			typename Tree :: PremiseVector_
			PremiseVector;

		const Tree* tree = node->getTree();
		const PremiseVector* premiseVector = tree->getPremiseVector();

		for (value :: Integer i = 0; i < premiseVector->getSize(); ++ i) {
			const mdl :: proof :: Node* node = premiseVector->getValue (i);
			tree_->addBranch (node->getExpression(), depth);
		}
	}
}
}
}
}

#endif /*MDL_FORM_EVALUATION_LEXP_UPHOOD_CPP_*/
