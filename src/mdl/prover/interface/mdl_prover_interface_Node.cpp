/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_interface_Node.cpp                            */
/* Description:     interface for a node of the variant tree                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_INTERFACE_NODE_CPP_
#define MDL_PROVER_INTERFACE_NODE_CPP_

namespace mdl {
namespace prover {
namespace interface {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Node<A> :: Node (Tree_* tree) :
	mapped_ (false),
	forking_ (value :: undefined :: INTEGER),
	globalIndex_ (0),
	levelIndex_ (0),
	tree_ (tree) {
	}
	template<class A>
	inline
	Node<A> :: ~ Node() {
	}

	template<class A>
	value :: Integer
	Node<A> :: countPropHintNodes() const
	{
		typedef
			typename node :: Prop<Allocator_>
			Prop;

		value :: Integer result = 0;
		if (dynamic_cast<const Prop*>(this) != NULL) {
			if (this->isHint()) {
				++ result;
			}
		}
		for (int i = 0; i < this->getUpArity(); ++ i) {
			const Node_* upNode = getUp (i);
			result += upNode->countPropHintNodes();
		}
		return result;
	}

	template<class A>
	void
	Node<A> :: findUnprovedNodes (NodeVector_& nodeVector)
	{
		if (!isHint()) {
			return;
		}
		bool upIsProved = true;
		for (int i = 0; i < this->getUpArity(); ++ i) {
			Node_* upNode = getUp (i);
			if (upNode->isHint() && !upNode->isProved()) {
				upIsProved = false;
				break;
			}
		}
		if (upIsProved) {
			if (!isProved()) {
				nodeVector.add (this);
			}
		} else {
			for (int i = 0; i < this->getUpArity(); ++ i) {
				Node_* upNode = getUp (i);
				upNode->findUnprovedNodes (nodeVector);
			}
		}
	}
	template<class A>
	void
	Node<A> :: findUnprovedHintNodes (NodeVector_& nodeVector)
	{
		if (!isHint()) {
			return;
		}
		bool upIsProved = true;
		for (int i = 0; i < this->getUpArity(); ++ i) {
			Node_* upNode = getUp (i);
			if (!upNode->isProvedWithHint()) {
				upIsProved = false;
				break;
			}
		}
		if (upIsProved) {
			if (!isProvedWithHint()) {
				nodeVector.add (this);
			}
		} else {
			for (int i = 0; i < this->getUpArity(); ++ i) {
				Node_* upNode = getUp (i);
				upNode->findUnprovedHintNodes (nodeVector);
			}
		}
	}
	template<class A>
	bool
	Node<A> :: isProvedWithHint() const
	{
		for (value :: Integer i = 0; i < getEvidences().getSize(); ++ i) {
			const Evidence_* evidence = getEvidences().getValue (i);
			if (evidence->isHint()) {
				return true;
			}
		}
		return false;
	}

using manipulator :: mode;
using manipulator :: endLine;
using manipulator :: tab;

	template<class  A>
	void
	Node<A> :: showTree
	(
		String& string,
		bool onlyHint,
		bool showEvidences,
		int  upToLevel,
		const int indent
	) const
	{
		string << iterate << indent << tab;
		this->show (string);

		if (upToLevel == 0) {
			return;
		}

		const Evidences_&
				evidences = getEvidences();
		if (showEvidences) {
			string << endLine;
			evidences.show (string, indent);
			string << endLine;
		} else {
			string << endLine;
			string << iterate << indent << tab;
			string << "evidences: " << evidences.getSize() << endLine;
		}
		if (getUpArity() == 0) {
			string << iterate << indent << tab;
			string << "()";
		} else {
			string << iterate << indent << tab;
			string << "(" << endLine;
			for (value :: Integer i = 0; i < getUpArity(); ++ i) {
				const Node* upNode = getUp (i);
				if (onlyHint && upNode->getHint() == NULL) {
					continue;
				}
				upNode->showTree
				(
					string,
					onlyHint,
					showEvidences,
					(upToLevel == -1 ? -1 : upToLevel - 1),
					indent + 1
				);
				if (i + 1 < getUpArity()) {
					string << ", ";
				}
				string << endLine;
			}
			string << iterate << indent << tab;
			string << ")";
		}
	}
	template<class  A>
	void
	Node<A> :: dumpTree
	(
		bool onlyHint,
		bool showEvidences,
		int  upToLevel
	) const
	{
		std :: cout << std :: endl;
		String string (1024);
		showTree (string, onlyHint, showEvidences, upToLevel);
		std :: cout << string << std :: endl;
	}
	template<class  A>
	void
	Node<A> :: dumpEvidences () const
	{
		std :: cout << "evidences = {" << std :: endl;
		for (int i = 0; i < getEvidences().getSize(); ++ i) {
			const Evidence_* evidence = getEvidences().getValue (i);
			std :: cout << "\t";
			evidence->dump();
			std :: cout << std :: endl;
		}
		std :: cout << "}" << std :: endl;
	}

	template<class  A>
	inline value :: Real
	Node<A> :: getSubComplexity() const
	{
		typedef
			typename node :: Prop<Allocator_>
			Prop;
		const Prop* prop = dynamic_cast<const Prop*> (this);
		if (prop == NULL) {
			return 0;
		}
		const value :: Real subComplexityInt = prop->substitutionInt_->getComplexity();
		const value :: Real subComplexityExt = prop->substitutionExt_->getComplexity();
		const value :: Real subComplexity =
			(subComplexityInt < subComplexityExt) ? subComplexityExt : subComplexityInt;
		return subComplexity;
	}
	template<class  A>
	inline value :: Real
	Node<A> :: getExpComplexity() const
	{
		const Expression_* expression = getExpression();
		if (expression == NULL) {
			return 0;
		} else {
			return expression->getComplexity();
		}
	}
	template<class A>
	value :: Integer
	Node<A> :: getForking() const {
		return forking_;
	}

	template<class A>
	int
	Node<A> :: getXCoord() const {
		return levelIndex_;
	}
	template<class A>
	int
	Node<A> :: getYCoord() const {
		return getMinHeight();
	}

	template<class A>
	inline int
	Node<A> :: getXGraphCoord() const
	{
		const value :: Integer minHeight = getMinHeight();
		const value :: Integer width = tree_->up().getLevelWidth (minHeight);
		return (getXCoord() - width / 2) * X_SCALE ;
	}
	template<class A>
	inline int
	Node<A> :: getYGraphCoord() const {
		return getYCoord() * Y_SCALE;
	}

	template<class A>
	inline typename Node<A> :: Tree_*
	Node<A> :: getTree() {
		return tree_;
	}
	template<class A>
	inline const typename Node<A> :: Tree_*
	Node<A> :: getTree() const {
		return tree_;
	}
	template<class A>
	inline bool
	Node<A> :: isHint() const {
		return getHint() != NULL;
	}

	template<class A>
	inline value :: Integer
	Node<A> :: getGlobalIndex() const {
		return globalIndex_;
	}
	template<class A>
	inline value :: Integer
	Node<A> :: getLevelIndex() const {
		return levelIndex_;
	}
	template<class A>
	inline void
	Node<A> :: setGlobalIndex (const value :: Integer globalIndex) {
		globalIndex_ = globalIndex;
	}
	template<class A>
	inline void
	Node<A> :: setLevelIndex (const value :: Integer levelIndex) {
		levelIndex_ = levelIndex;
	}

	/****************************
	 *		Protected members
	 ****************************/

	template<class A>
	void
	Node<A> :: setMapped (const bool value) const
	{
		mapped_ = value;
		for (value :: Integer i = 0; i < getUpArity(); ++ i) {
			const Node* node = getUp (i);
			node->setMapped (value);
		}
	}
	template<class A>
	void
	Node<A> :: showGraphInGML
	(
		String& string,
		const value :: Integer index,
		const char* label
	) const
	{
		setMapped (false);
		string << "graph [" << endLine;
		//string << tab << "comment \" ... \"";
		string << tab << "directed 1" << endLine;
		string << tab << "id " << index << endLine;
		string << tab << "label \"" << label << "\"" << endLine;
		string << endLine;
		const Mode mOld (string);
		Mode mNew (mOld);
		mNew.setValue (Mode :: SHOW_IN_GML_GRAPH, false);
		mNew.setValue (Mode :: SHOW_IN_GML, true);
		string << mode << mNew;
		this->show (string);
		string << mode << mOld;
		string << "]" << endLine;
		string << endLine;
		setMapped (false);
	}

	/*********************************
	 *		Overloaded operators
	 *********************************/

	template<class A>
	inline bool
	operator < (const Node<A>& node_1, const Node<A>& node_2)
	{
		if (node_1.getWeight() < node_2.getWeight()) {
			return true;
		} else if (node_1.getWeight() == node_2.getWeight()) {
			return (&node_1 < &node_2);
		} else {
			return false;
		}
	}
	template<class A>
	inline bool
	operator <= (const Node<A>& node_1, const Node<A>& node_2)
	{
		if (node_1.getWeight() <= node_2.getWeight()) {
			return true;
		} else if (node_1.getWeight() == node_2.getWeight()) {
			return (&node_1 <= &node_2);
		} else {
			return false;
		}
	}
	template<class A>
	inline bool
	operator > (const Node<A>& node_1, const Node<A>& node_2) {
		return operator < (node_2, node_1);
	}
	template<class A>
	inline bool
	operator >= (const Node<A>& node_1, const Node<A>& node_2) {
		return operator <= (node_2, node_1);
	}
	template<class A>
	inline bool
	operator == (const Node<A>& node_1, const Node<A>& node_2) {
		return (&node_1 == &node_2);
	}
}
}
}

#endif /*MDL_PROVER_INTERFACE_NODE_CPP_*/
