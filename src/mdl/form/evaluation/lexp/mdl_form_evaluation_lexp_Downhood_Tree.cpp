/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_lexp_Downhood_Tree.cpp               */
/* Description:     a downhood tree of a point in a proof                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace form {
namespace evaluation {
namespace lexp {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	Downhood<A> :: Tree_ :: Tree_
	(
		const mdl :: proof :: Step* step,
		const value :: Integer depth
	) :
	expression_ (new array :: Expression (step->getExpression())),
	down_ (step->getDownArity())
	{
		if (depth + 1 == mdl :: Config :: getDistanceLocalityBoundary()) {
			return;
		}
		for (value :: Integer i = 0; i < step->getDownArity(); ++ i) {
			const mdl :: proof :: Node* node = step->getDown (i);
			const mdl :: proof :: Step*
				downStep = dynamic_cast<const mdl :: proof :: Step*>(node);
			if (downStep == NULL) {
				continue;
			}
			Tree_* downTree = new Tree_ (downStep, depth + 1);
			down_.add (downTree);
		}
	}
	template<class A>
	Downhood<A> :: Tree_ :: Tree_
	(
		const Node_* node,
		const value :: Integer depth
	) :
	expression_ (new array :: Expression (node->getExpression())),
	down_ (node->getDownArity())
	{
		if (depth + 1 == mdl :: Config :: getDistanceLocalityBoundary()) {
			return;
		}
		for (value :: Integer i = 0; i < node->getDownArity(); ++ i) {
			const Node_* n = node->getDown (i);
			for (value :: Integer j = 0; j < n->getDownArity(); ++ j) {
				const Node_* m = n->getDown (j);
					Tree_* downTree = new Tree_ (m, depth + 1);
					down_.add (downTree);
			}
		}
	}
	template<class A>
	Downhood<A> :: Tree_ :: Tree_ (const Tree_* tree) :
	expression_ (new array :: Expression (tree->expression_)),
	down_ (tree->down_.getSize())
	{
		for (value :: Integer i = 0; i < tree->down_.getSize(); ++ i) {
			const Tree_* downTree = tree->down_.getValue (i);
			Tree_* newDownTree = new Tree_ (downTree);
			down_.add (newDownTree);
		}
	}
	template<class A>
	Downhood<A> :: Tree_ :: ~ Tree_() {
		deleteAggregateObject (expression_);
	}

	template<class A>
	value :: Real
	Downhood<A> :: Tree_ :: getDistance
	(
		const Tree_* tree,
		const Factors& factors,
		const value :: Integer depth
	) const
	{
		const value :: Real
			currDist = getDistance (expression_, tree->expression_) * factors.getGamma (depth);
		value :: Real minDist = 0;
		bool firstPass = true;
		for (value :: Integer i = 0; i < down_.getSize(); ++ i) {
			const Tree_* t_1 = down_.getValue (i);
			for (value :: Integer j = 0; j < tree->down_.getSize(); ++ j) {
				const Tree_* t_2 = tree->down_.getValue (j);
				const value :: Real
					dist = t_1->getDistance (t_2, factors, depth + 1);
				if (dist < minDist || firstPass) {
					minDist = dist;
				}
			}
		}
		return minDist + currDist;
	}

	// object :: Object implementation
	template<class A>
	void
	Downhood<A> :: Tree_ :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Downhood<A> :: Tree_ :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (expression_);
		volume += down_.getVolume();
		return volume;
	}
	template<class A>
	Size_t
	Downhood<A> :: Tree_ :: getSizeOf() const {
		return sizeof (Tree_);
	}
	template<class A>
	void
	Downhood<A> :: Tree_ :: show (String& string) const {
 	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	value :: Real
	Downhood<A> :: Tree_ :: getDistance
	(
		const array :: Expression* expression_1,
		const array :: Expression* expression_2
	) const
	{
		Memory :: stack().push();
		value :: Integer minDifference = value :: undefined :: INTEGER;
		expression_1->factorUnifySymmetric (expression_2, minDifference);
		const value :: Real distance =
			(minDifference == value :: undefined :: INTEGER) ?
			value :: LARGE :
			minDifference;
		Memory :: stack().pop();
		return distance;
	}
}
}
}
}


