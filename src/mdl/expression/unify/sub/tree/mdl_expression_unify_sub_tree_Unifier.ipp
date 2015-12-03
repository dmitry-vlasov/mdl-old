/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_sub_tree_Unifier.ipp                      */
/* Description:     main unification algorithm. Static class                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_UNIFY_SUB_TREE_UNIFIER_IPP_
#define MDL_EXPRESSION_UNIFY_SUB_TREE_UNIFIER_IPP_

namespace mdl {
namespace expression {
namespace unify {
namespace sub {
namespace tree {

	/****************************
	 *		Public members
	 ****************************/

	template<class U, class T>
	inline
	Unifier<U, T> :: Unifier
	(
		const index :: Arity dimension,
		const Substitution_* substitutionInt,
		Evidences_& evidences,
		const value :: Integer boundary
	) :
	dimension_ (dimension),
	substitutionInt_ (substitutionInt),
	evidences_ (evidences),
	boundary_ (boundary)
	/*flags_ {true, true, true, true, true},
	stop_ {2, -1, -1, -1, -1},
	count_ {0, 0, 0, 0, 0}*/
	{ }

	template<class U, class T>
	inline void
	Unifier<U, T> :: operator () (const Matrix_& matrix)
	{
		units_ = new UnitVector_();
		Unit_ unit (dimension_, matrix);
		unifyNode (unit);
		delete units_;
		units_ = NULL;
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class U, class T>
	void
	Unifier<U, T> :: unifyNode (Unit_ unit)
	{
		while (!unit.isNull()) {
			/*if (Counter :: stop()) {
				unit.dump();
			}*/
			if (unit.isGood()) {
				if (unit.isLambda()) {
					unifyLast (unit);
				} else {
					Memory :: stack().push();
					tryUnit (unit);
					Memory :: stack().pop();
				}
			}
			+ unit;
		}
	}
	template<class U, class T>
	void
	Unifier<U, T> :: tryUnit (Unit_ unit)
	{
		applyUnit (unit);
		if (!unit.fixedAreEqual()) {
			return;
		}
		if (unit.allAreEqual()) {
			unifyNext (unit); return;
		}
		bool replacementIsFound = false;
		for (index :: Arity varIndex = 0; varIndex < unit.getDimension(); ++ varIndex) {
			if (unit.skip (varIndex)) {
				continue;
			}
			const Symbol variable = *unit.getIterator (varIndex);
			if (!variable.isReplaceable()) {
				continue;
			}
			for (index :: Arity termIndex = 0; termIndex < unit.getDimension(); ++ termIndex) {
				if (unit.skip (termIndex)) {
					continue;
				}
				const Symbol symbol = *unit.getIterator (termIndex);
				if (symbol == variable) {
					continue;
				}
				replacementIsFound = tryReplace (unit, varIndex, termIndex);
				if (replacementIsFound) {
					break;
				}
			}
			if (replacementIsFound) {
				break;
			}
		}
	}
	template<class U, class T>
	void
	Unifier<U, T> :: applyUnit (Unit_& unit)
	{
		for (index :: Arity i = 0; i < unit.getDimension(); ++ i) {
			if (unit.skip (i)) {
				continue;
			}
			const Substitution_* const
				substitution = unit.findSubstitution (i);
			if (substitution != NULL) {
				const Term_* const
					term = substitution->getTerm();
				applyTerm (unit, i, term);
			}
		}
	}
	template<class U, class T>
	void
	Unifier<U, T> :: applyTerm
	(
		Unit_& unit,
		const index :: Arity i,
		const Term_* term
	)
	{
		typedef
			Builder
			<
				typename Unit_ :: Term_ :: template Alternative<allocator :: Stack> :: Result_,
				Term_
			>
			Builder;

		Builder builder (term);

		typename Unit_ :: Term_*
			insertion = builder.build()->template castAway<typename Term_ :: Allocator_>();

		insertion->getEnd()->template
			link<expression :: direction :: RIGHT> (unit.iterator (i).getNode()->goRight());
		insertion->getBegin()->template
			link<expression :: direction :: LEFT> (unit.iterator (i).getNode()->goLeft());
		unit.insert (i, insertion);
	}
	template<class U, class T>
	bool
	Unifier<U, T> :: tryReplace
	(

		Unit_ unit,
		const index :: Arity i,
		const index :: Arity j
	)
	{
		const typename Terms_ :: Initial_ :: Node_*
			node = unit.getIterator (j)->getTerms().getInitial().getFirst();
		bool termIsFound = false;
		while (node != NULL)
		{
			const typename Unit_ :: Term_*
				term = node->getValue();
			Memory :: stack().push();
			if (tryTerm (unit, i, j, term)) {
				termIsFound = true;
			}
			Memory :: stack().pop();
			node = node->getNext();
		}
		return termIsFound;
	}
	template<class U, class T>
	bool
	Unifier<U, T> :: tryTerm
	(
		Unit_ unit,
		const index :: Arity i,
		const index :: Arity j,
		const typename Unit_ :: Term_* term
	)
	{
		if (!unit.checkTermType (i, j, term)) {
			return false;
		}
		if (!unit.checkTermAccessible (j, term)) {
			return false;
		}
		if (!unit.checkTermVariables (i, term)) {
			return false;
		}
		typedef
			Builder
			<
				Term_,
				typename Unit_ :: Term_ :: template Alternative<allocator :: Stack> :: Result_
			>
			Builder;

		Builder builder (term);

		Term_* insertion = builder.build();

		const Symbol&
			variable = *unit.getIterator (i);
		Substitution_*
			delta = Substitution_ :: template
				create<allocator :: Stack>(variable, insertion, NULL, true);
		unit.newSubstitution (delta);
		unit.intersectData (j, term);
		applyTerm (unit, i, insertion);

		tryUnit (unit);
		return true;
	}
	template<class U, class T>
	void
	Unifier<U, T> :: unifyNext (Unit_ unit)
	{
		if (unit.isTerminal()) {
			if (unit.isFinal()) {
				unifyLast(unit);
			}
			return;
		}
		++ unit;
		Memory :: stack().push();
		unifyNode (unit);
		Memory :: stack().pop();
	}
	template<class U, class T>
	inline void
	Unifier<U, T> :: unifyLast (Unit_ unit)
	{
		if (!unit.isLastColumn()) {
			//showBranch (unit);
			{
				Unit_ next (unit);
				next.shiftColumn (&unit);
				unifyNode (next);
			}
			//hideBranch (unit);
		} else {
			//showBranch (unit);
			Finalize<Unit_, Types_> finalize
			(
				substitutionInt_,
				evidences_,
				boundary_
			);
			finalize (unit);
			//hideBranch (unit);
		}
	}

	/****************************
	 *		Debug stuff
	 ****************************/

	/*template<class U, class T>
	void
	Unifier<U, T> :: showBranch (Unit_ unit, const value :: Integer i)
	{
		if (!Counter :: stop (1)) {
			return;
		}
		if (i == DEBUG_DIM) {
			return;
		}
		if (unit.getIndex() == i) {
			if ((i == 0) && flags_ [0]) {
				++ count_ [0];
			} else if ((count_ [i - 1] == stop_ [i - 1] && flags_ [i])) {
				++ count_ [i];
			}
			if ((count_ [i] == stop_ [i]) && flags_ [i]) {
				std :: cout << unit;
				if (i == 1) {
					Counter :: set (0, 2);
				}
			}
			if ((stop_ [i] == -1) &&
				((i == 0) || ((count_ [i - 1] == stop_ [i - 1]) && flags_ [i - 1]))) {
				std :: cout << "count " << i << " = " << count_[i] << std :: endl;
				std :: cout << unit;
				Counter :: set (0, 2);
			}
		}
		showBranch (unit, i + 1);
	}
	template<class U, class T>
	void
	Unifier<U, T> :: hideBranch (Unit_ unit, const value :: Integer i)
	{
		if (!Counter :: stop (1)) {
			return;
		}
		if (i == DEBUG_DIM) {
			return;
		}
		if (unit.getIndex() == i) {
			if ((count_ [i] == stop_ [i]) && flags_ [i]) {
				flags_ [i] = false;
				if (i == 4) {
					Counter :: set (1000, 2);
				}
			}
		}
		hideBranch (unit, i + 1);
	}*/

	template<class U, class T>
	typename Unifier<U, T> :: UnitVector_*
	Unifier<U, T> :: units_ = NULL;
}
}
}
}
}

#endif /*MDL_EXPRESSION_UNIFY_SUB_TREE_UNIFIER_IPP_*/

