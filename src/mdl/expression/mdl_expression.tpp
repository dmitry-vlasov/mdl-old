/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression.tpp                                       */
/* Description:     typedefs for expression module                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace array {

	typedef
		expression :: Array<>
		Expression;
	typedef
		Expression :: Substitution_
		Substitution;
	typedef
		Expression :: Term_
		Term;
}

namespace vector {
	typedef
		vector :: Vector
		<
			const mdl :: array :: Expression*,
			storage :: ByValue,
			allocator :: Heap
		>
		Expression;

	typedef
		vector :: Vector
		<
			mdl :: expression :: Symbol,
			storage :: ByValue,
			allocator :: Heap
		>
		Symbol;
}

namespace set {
	typedef
		set :: Set
		<
			mdl :: expression :: Symbol,
			storage :: ByValue,
			allocator :: Heap
		>
		Symbol;
}

namespace list {

	typedef
		expression :: List<>
		Expression;
	typedef
		Expression :: Substitution_
		Substitution;
	typedef
		Expression :: Term_
		Term;
}

namespace tree {

	typedef
		expression :: Tree
		<
			const mdl :: Rule*,
			storage :: ByValue
		>
		Rule;
	typedef
		expression :: Tree
		<
			const mdl :: Proposition*,
			storage :: ByValue,
			expression :: node :: container :: List
		>
		Proposition;
	typedef
		expression :: Tree
		<
			const mdl :: Term*,
			storage :: ByValue
		>
		Term;
	typedef
		expression :: Tree
		<
			const mdl :: proof :: Step*,
			storage :: ByValue,
			expression :: node :: container :: List
		>
		Expression;
	typedef
		expression :: Tree
		<
			const mdl :: proof :: Node*,
			storage :: ByValue,
			expression :: node :: container :: List
		>
		Premise;
}

namespace stack {

	typedef
		expression :: List<allocator :: Stack>
		Expression;
	typedef
		Expression :: Term_
		Term;
	typedef
		expression :: Substitution<Term>
		Substitution;
}

namespace forest {

	typedef
		expression :: Forest
		<
			const mdl :: Proposition*,
			storage :: ByValue,
			expression :: node :: container :: List
		>
		Proposition;
}

// Debugging stuff

namespace unify {
namespace sub {
namespace tree {

	typedef
		typename expression :: Tree
		<
			const prover :: Evidence<allocator :: Heap>*,
			storage :: ByValue,
			expression :: node :: container :: Set,
			allocator :: Heap
		>
		HeapCell;

	typedef
		typename expression :: Tree
		<
			const prover :: Evidence<allocator :: Boxed>*,
			storage :: ByValue,
			expression :: node :: container :: Set,
			allocator :: Boxed
		>
		BoxedCell;
}
}
}

void dump (const array :: Substitution*);
void dump (const array :: Substitution&);
void dump (const array :: Expression*);
void dump (const array :: Expression&);
void dump (const array :: Term*);
void dump (const array :: Term&);

void dump (const stack :: Substitution*);
void dump (const stack :: Substitution&);
void dump (const stack :: Expression*);
void dump (const stack :: Expression&);
void dump (const stack :: Term*);
void dump (const stack :: Term&);

void dump (const list :: Substitution*);
void dump (const list :: Substitution&);
void dump (const list :: Expression*);
void dump (const list :: Expression&);
void dump (const list :: Term*);
void dump (const list :: Term&);

void dump (const expression :: Array<allocator :: Boxed>*);
void dump (const expression :: Array<allocator :: Boxed>&);
void dump (const expression :: Array<allocator :: Boxed> :: Substitution_*);
void dump (const expression :: Array<allocator :: Boxed> :: Substitution_&);
void dump (const expression :: Array<allocator :: Boxed> :: Term_*);
void dump (const expression :: Array<allocator :: Boxed> :: Term_&);

void dump (const expression :: List<allocator :: Boxed>*);
void dump (const expression :: List<allocator :: Boxed>&);
void dump (const expression :: List<allocator :: Boxed> :: Substitution_*);
void dump (const expression :: List<allocator :: Boxed> :: Substitution_&);
void dump (const expression :: List<allocator :: Boxed> :: Term_*);
void dump (const expression :: List<allocator :: Boxed> :: Term_&);

void dump (const unify :: sub :: tree :: HeapCell*);
void dump (const unify :: sub :: tree :: HeapCell&);
void dump (const unify :: sub :: tree :: HeapCell :: Substitution_*);
void dump (const unify :: sub :: tree :: HeapCell :: Substitution_&);
void dump (const unify :: sub :: tree :: HeapCell :: Term_*);
void dump (const unify :: sub :: tree :: HeapCell :: Term_&);

void dump (const unify :: sub :: tree :: BoxedCell*);
void dump (const unify :: sub :: tree :: BoxedCell&);
void dump (const unify :: sub :: tree :: BoxedCell :: Substitution_*);
void dump (const unify :: sub :: tree :: BoxedCell :: Substitution_&);
void dump (const unify :: sub :: tree :: BoxedCell :: Term_*);
void dump (const unify :: sub :: tree :: BoxedCell :: Term_&);

}


