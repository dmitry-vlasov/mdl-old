/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_parse_Unit.ipp                            */
/* Description:     expression parser unit: pair of iterators& substitutiuon */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_PARSE_UNIT_IPP_
#define MDL_EXPRESSION_PARSE_UNIT_IPP_

namespace mdl {
namespace expression {
namespace parse {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Unit :: Unit
	(
		Parser* parser,
		const expr_Iterator_& begin,
		const tree_Iterator_& root,
		const Tree* tree,
		const value :: Integer depth
	) :
	Pair_ (begin,  root),
	parser_ (parser),
	begin_ (begin),
	root_ (root),
	substitution_ (NULL),
	tree_ (tree),
	depth_ (depth) {
	}
	inline
	Unit :: Unit (const Unit& unit) :
	Pair_ (unit),
	parser_ (unit.parser_),
	begin_ (unit.begin_),
	root_ (unit.root_),
	substitution_ (unit.substitution_),
	tree_ (unit.tree_),
	depth_ (unit.depth_) {
	}

	inline bool
	Unit :: isConstant() const {
		return
			(Pair_ :: getSecond() != NULL) &&
			(Pair_ :: getSecond()->isConstant());
	}
	inline bool
	Unit :: isVariable() const {
		return
			(Pair_ :: getSecond() != NULL) &&
			(Pair_ :: getSecond()->isVariable());
	}
	inline typename Unit :: State
	Unit :: getState() const
	{
		const bool
			expressionEnd = Pair_ :: getFirst()->template
				isTerminal<direction :: RIGHT>(parser_->expression_);
		const bool
			treeEnd = Pair_ :: getSecond()->template
				isTerminal<direction :: RIGHT>();

		if (expressionEnd) {
			return treeEnd ? FINAL : DEADLOCK;
		} else {
			return treeEnd ? TERMINAL : TRANSIT;
		}
	}

	inline void
	Unit :: operator ++ () {
		Pair_ :: operator ++();
	}
	inline void
	Unit :: operator + ()
	{
		Pair_ :: operator +();
		root_ = Pair_ :: getSecond();
	}
	inline void
	Unit :: operator - ()
	{
		Pair_ :: operator -();
		root_ = Pair_ :: getSecond();
	}

	inline const Symbol&
	Unit :: getTreeSymbol() const {
		return *Pair_ :: getSecond();
	}
	inline const mdl :: Type*
	Unit :: getTreeType() const {
		return Pair_ :: getSecond()->getType();
	}
	inline const mdl :: Type*
	Unit :: getExprType() const {
		return Pair_ :: getFirst()->getType();
	}
	inline const mdl :: Rule*
	Unit :: getTreeRule() const
	{
		return
			Config :: prove() ?
			NULL :
			Pair_ :: getSecond()->getData().getValue();
	}

	inline expr_Iterator_
	Unit :: getBegin() const {
		return begin_;
	}
	inline expr_Iterator_
	Unit :: getEnd() const {
		return Pair_ :: getFirst();
	}
	inline const Tree*
	Unit :: getTree() const {
		return tree_;
	}
	inline void
	Unit :: setEnd (const expr_Iterator_ end) {
		Pair_ :: first() = end;
	}
	inline void
	Unit :: setTree (const Tree* tree) {
		tree_ = tree;
	}

	inline const Substitution_*
	Unit :: getSubstitution() const {
		return substitution_;
	}
	inline void
	Unit :: newSubstitution (const Term_* term)
	{
		if (isVariable()) {
			substitution_ =
			Config :: prove() ? NULL :
			const_cast<Substitution_*>
			(
				Substitution_ :: template create <allocator :: Stack>
				(
					getTreeSymbol(),
					term,
					substitution_
				)->
				template castAway<allocator :: Heap>()
			);
		}
	}

	inline const Tree*
	Unit :: newRuleTerm (const mdl :: Type* type)
	{
		const Term_* term = Term_ :: template create<allocator :: Stack>
		(
			getBegin(), getEnd(),
			type,
			getTreeRule(),
			substitution_
		);
		tree_ = new Tree
		(
			term,
			getBegin()->template isTerminal<direction :: LEFT>(parser_->expression_),
			getEnd()->template isTerminal<direction :: RIGHT>(parser_->expression_),
			tree_
		);
		return tree_;
	}
	inline const Tree*
	Unit :: newVarTerm (const mdl :: Type* type)
	{
		const Term_*
			term = Term_ :: template create<allocator :: Stack> (getEnd(), type);
		newSubstitution (term);
		tree_ = new Tree (term, false, false, tree_);
		return tree_;
	}

	inline value :: Integer
	Unit :: getExpressionLength() const
	{
		value :: Integer length = 1;
		for (expr_Iterator_ iterator = getEnd(); iterator != getBegin(); -- iterator) {
			++ length;
		}
		return length;
	}
	inline value :: Integer
	Unit :: getTreeLength() const
	{
		value :: Integer length = 1;
		const tree_Iterator_ end (root_);
		if (end.isNull()) {
			return 0;
		}
		for (tree_Iterator_ iterator = Pair_ :: getSecond(); iterator != end; -- iterator) {
			if (iterator.isNull()) {
				-- length;
				break;
			}
			++ length;
		}
		return length;
	}
	inline value :: Integer
	Unit :: getDepth() const {
		return depth_;
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	inline void
	Unit :: show (String& string) const
	{
		string << "unit." << endLine;
		string << "-------" << endLine;
		string << "expression: " << endLine;
		string << tab << "length: " << getExpressionLength() << endLine;
		string << tab;
		showExpression (string); string << endLine;
		string << endLine;
		string << "tree: " << endLine;
		string << tab <<"length: " << getTreeLength() << endLine;
		string << tab << "root: " << endLine;
		if (root_ == NULL) {
			string << tab << "NULL" << endLine;
		} else {
			//root_->showTree (string); string << endLine;
			string << tab << "branch:" << endLine;
			string << tab;
			showTreeBranch (string); string << endLine;
		}

		string << tab << "expression iterator value:" << endLine;
		if (Pair_ :: getFirst().isNull()) {
			string << tab << "NULL" << endLine;
		} else {
			string << tab << *Pair_ :: getFirst() << endLine;
		}
		string << endLine;
		string << tab << "tree iterator value:" << endLine;
		if (Pair_ :: getSecond().isNull()) {
			string << tab << "NULL" << endLine;
		} else {
			string << tab;
			Pair_ :: getSecond()->showSymbol (string);
			string << endLine;
		}
		string << endLine;
		/*string << tab << "show tree back:" << endLine;
		if (Pair_ :: getSecond().isNull()) {
			string << tab << "NULL" << endLine;
		} else {
			string << tab;
			Pair_ :: getSecond()->showBack (string);
			string << endLine;
		}
		string << endLine;*/
		/*string << tab << "end tree:" << endLine;
		if (Pair_ :: getSecond().isNull()) {
			string << tab << "NULL" << endLine;
		} else {
			string << *Pair_ :: getSecond()->showBack (string);
			string << endLine;
		}*/
		string << endLine;
		string << tab << "substitution:" << endLine;
		if (substitution_ != NULL) {
			string << tab;
			substitution_->show (string);
		} else {
			string << tab << "NULL";
		}
	}
	inline void
	Unit :: dump() const
	{
		enum {
			INITIAL_STRING_CAPACITY = 64
		};
		String string (INITIAL_STRING_CAPACITY);
		show (string);
		std :: cout << string;
	}

	inline String&
	operator << (String& string, const Unit& unit)
	{
		unit.show (string);
		return string;
	}

	inline std :: ostream&
	operator << (std :: ostream& os, const Unit& unit)
	{
		enum {
			INITIAL_STRING_CAPACITY = 64
		};
		String string (INITIAL_STRING_CAPACITY);
		unit.show (string);
		os << string;
		return os;
	}

	/****************************
	 *		Private members
	 ****************************/

using manipulator :: space;

	void
	Unit :: showExpression (String& string) const
	{
		const value :: Integer length = getExpressionLength();
		Symbol buffer [length];

		expr_Iterator_ iterator = getEnd();
		for (value :: Integer i = 0; i < length; ++ i) {
			buffer [i] = *iterator;
			-- iterator;
		}
		for (value :: Integer i = 0; i < length; ++ i) {
			string << buffer [length - i - 1] << space;
		}
	}
	void
	Unit :: showTreeBranch (String& string) const
	{
		const value :: Integer length = getTreeLength();
		Symbol buffer [length];

		tree_Iterator_ iterator = Pair_ :: getSecond();
		for (value :: Integer i = 0; i < length; ++ i) {
			buffer [i] = *iterator;
			-- iterator;
		}
		for (value :: Integer i = 0; i < length; ++ i) {
			string << buffer [length - i - 1] << space;
		}
	}
}
}
}

#endif /*MDL_EXPRESSION_PARSE_UNIT_IPP_*/
