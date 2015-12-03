/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_data_Tree.cpp                                 */
/* Description:     prover tree statistics data                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_DATA_TREE_CPP_
#define MDL_PROVER_DATA_TREE_CPP_

namespace mdl {
namespace prover {
namespace data {

	/****************************
	 *		Public members
	 ****************************/

	Tree :: Tree () :
	up_   (),
	down_ (),
	root_ (),
	totalVolume_          (0),
	premiseTreeVolume_    (0),
	premiseVectorVolume_  (0),
	expressionTreeVolume_ (0),
	variablesVolume_      (0),
	growUpTimer_   (),
	growDownTimer_ () {
	}
	template<class A>
	Tree :: Tree (const typename tree :: Tree<A>& tree) :
	up_   (*tree.up_),
	down_ (*tree.down_),
	root_ (*tree.root_),

	totalVolume_          (tree.getVolume()),
	premiseTreeVolume_    (getAggregateVolume (tree.premiseTree_)),
	premiseVectorVolume_  (getAggregateVolume (tree.premiseVector_)),
	expressionTreeVolume_ (getAggregateVolume (tree.expressionTree_)),
	variablesVolume_      (getAggregateVolume (tree.variables_)),

	growUpTimer_   (),
	growDownTimer_ ()
	{
		growUpTimer_.setDelta (tree.getTimers()->growUp().getCumulative());
		growDownTimer_.setDelta (tree.getTimers()->growDown().getCumulative());
	}
	Tree :: ~ Tree() {
	}

	void
	Tree :: operator += (const Tree& tree)
	{
		up_   += tree.up_;
		down_ += tree.down_;
		root_ += tree.root_;

		totalVolume_          += tree.totalVolume_;
		premiseTreeVolume_    += tree.premiseTreeVolume_;
		premiseVectorVolume_  += tree.premiseVectorVolume_;
		expressionTreeVolume_ += tree.expressionTreeVolume_;
		variablesVolume_      += tree.variablesVolume_;

		growUpTimer_   += tree.growUpTimer_;
		growDownTimer_ += tree.growDownTimer_;
	}
	void
	Tree :: operator /= (const int count)
	{
		up_   /= count;
		down_ /= count;
		root_ /= count;

		totalVolume_          /= count;
		premiseTreeVolume_    /= count;
		premiseVectorVolume_  /= count;
		expressionTreeVolume_ /= count;
		variablesVolume_      /= count;

		growUpTimer_   /= count;
		growDownTimer_ /= count;
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;
using manipulator :: iterate;

	void
	Tree :: showVolume (String& string, const int indent) const
	{
		string << iterate << indent << tab;
		string << "Prover tree volume" << endLine;
		string << iterate << indent << tab;
		string << "------------------" << endLine;
		string << iterate << (indent + 1) << tab;
		string << memory :: UsageMessage (totalVolume_, totalVolume_, "total volume") << endLine;
		string << iterate << (indent + 1) << tab;
		string << memory :: UsageMessage (totalVolume_, premiseTreeVolume_,    "premise tree") << endLine;
		string << iterate << (indent + 1) << tab;
		string << memory :: UsageMessage (totalVolume_, premiseVectorVolume_,  "premise vector") << endLine;
		string << iterate << (indent + 1) << tab;
		string << memory :: UsageMessage (totalVolume_, expressionTreeVolume_, "expression tree") << endLine;
		string << iterate << (indent + 1) << tab;
		string << memory :: UsageMessage (totalVolume_, variablesVolume_,      "variables") << endLine;
		string << iterate << (indent + 1) << tab;
		//string << memory :: UsageMessage (totalVolume_, timersVolume_, "timers") << endLine;
		//string << iterate << (indent + 1) << tab;
		string<< endLine;

		up_.showVolume   (string, indent + 1);
		down_.showVolume (string, indent + 1);
		root_.showVolume (string, indent + 1);
	}
	void
	Tree :: showTiming (String& string, const int indent) const
	{
		string << iterate << indent << tab;
		string << "Proving timings" << endLine;
		string << iterate << indent << tab;
		string << "------------------" << endLine;
		string << iterate << (indent + 1) << tab;
		string << "growing up time = " << growUpTimer_ << endLine;

		string << iterate << (indent + 1) << tab;
		string << "growing down time = " << growDownTimer_ << endLine;

		growUpTimer_.setShowCumulativeTime (true);
		string << iterate << (indent + 1) << tab;
		string << "cumulative growing up time = " << growUpTimer_ << endLine;
		growUpTimer_.setShowCumulativeTime (false);

		growDownTimer_.setShowCumulativeTime (true);
		string << iterate << (indent + 1) << tab;
		string << "cumulative growing down time = " << growDownTimer_ << endLine;
		growDownTimer_.setShowCumulativeTime (false);

		string << iterate << (indent + 1) << tab;
		string << endLine;
	}

	// object :: Object interface
	void
	Tree :: commitSuicide() {
		delete this;
	}
	Size_t
	Tree :: getVolume() const
	{
		Size_t volume = 0;
		volume += up_.getVolume();
		volume += down_.getVolume();
		volume += root_.getVolume();
		return volume;
	}
	Size_t
	Tree :: getSizeOf() const {
		return sizeof (Tree);
	}
	void
	Tree :: show (String& string) const
	{
		showVolume (string);
		showTiming (string);
	}
}
}
}

#endif /*MDL_PROVER_DATA_TREE_CPP_*/
