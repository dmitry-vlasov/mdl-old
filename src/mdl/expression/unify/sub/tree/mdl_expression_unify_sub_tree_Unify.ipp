/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_sub_tree_Unify.ipp                  */
/* Description:     wrapper for the multy Unifier class                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace expression {
namespace unify {
namespace sub {
namespace tree {

	/****************************
	 *		Public members
	 ****************************/

	template<class T, class A>
	Unify<T, A> :: Unify
	(
		const index :: Arity arity,
		Evidences_& evidences,
		const Substitution_* subInt
	) :
	arity_ (arity),
	subInt_ (subInt),
	evidences_ (evidences),

	matrix_ (),
	variables_ (),
	boundary_ (0) {
	}

	template<class T, class A>
	inline void
	Unify<T, A> :: operator() (const Input_& evidenceMatrix)
	{
		initVariables (evidenceMatrix);
		if (variables_.getSize() == 0) {
			unifyTrivial (evidenceMatrix);
		} else {
			initMatrix (evidenceMatrix);
			Unifier_ unifier (arity_, subInt_, evidences_, boundary_);
			unifier (matrix_);
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class T, class A>
	inline void
	Unify<T, A> :: unifyTrivial (const Input_& evidenceMatrix)
	{
		Memory :: stack().push();
		typedef
			Multyindex<const Evidences_, const Evidence_>
			_Multyindex;
		typedef
			typename _Multyindex :: Matrix_
			_Matrix;
		_Matrix matrix (arity_);
		for (index :: Arity i = 0; i < arity_; ++ i) {
			const Evidences_* evidences = evidenceMatrix.getValue (i);
			matrix.getReference (i) = evidences;
		}
		_Multyindex multyindex (arity_, matrix);
		while (true) {
			Evidence_* evidenceUp [arity_];
			for (index :: Arity i = 0; i < arity_; ++ i) {
				evidenceUp [i] = multyindex.getValue (i);
			}
			sub :: template Finaly<Substitution_, Types_> :: finalize
			(
				subInt_,
				evidences_,
				evidenceUp,
				arity_
			);
			if (++ multyindex) {
				break;
			}
		}
		Memory :: stack().pop();
	}
	template<class T, class A>
	inline void
	Unify<T, A> :: initVariables (const Input_& evidenceMatrix)
	{
		for (index :: Arity i = 0; i < evidenceMatrix.getSize(); ++ i) {
			const Evidences_*
				evidences = evidenceMatrix.getValue (i);
			for (value :: Integer j = 0; j < evidences->getSize(); ++ j) {
				const Evidence_* const
					evidence = evidences->getValue (j);
				const typename Types_ :: Substitution_*
					substitution = evidence->getSubstitution();
				while (substitution != NULL) {
					const Symbol& variable = substitution->getVariable();
					if (!variables_.contains (variable)) {
						variables_.add (variable);
					}
					substitution = substitution->getNext();
				}
			}
		}
		boundary_ = variables_.getSize();
	}
	template<class T, class A>
	void
	Unify<T, A> :: initMatrix (const Input_& evidenceMatrix)
	{
		for (index :: Arity i = 0; i < variables_.getSize(); ++ i) {
			const Symbol& variable = variables_.getReference (i);
			Vector_* column = new Vector_ (arity_);
			matrix_.add (column);
			for (index :: Arity j = 0; j < arity_; ++ j) {
				Cell_* cell = new Cell_();
				column->add (cell);
				const Evidences_* evidences =
					evidenceMatrix.getValue (j);
				fillCell (evidences, i, variable, cell);
			}
		}
	}
	template<class T, class A>
	void
	Unify<T, A> :: fillCell
	(
		const Evidences_* evidences,
		const index :: Arity i, // variable (column)
		const Symbol& variable,
		Cell_* cell
	)
	{
		for (value :: Integer k = 0; k < evidences->getSize(); ++ k) {
			const Evidence_* const
				evidence = evidences->getValue (k);
			const typename Types_ :: Substitution_*
				substitution = evidence->getSubstitution();
			while (substitution != NULL) {
				const Symbol& var = substitution->getVariable();
				if (var == variable) {
					const typename Types_ :: Term_* const term = substitution->getTerm();
					typename Cell_ :: Iterator_ end = cell->addBranch (term, evidence, true);
					while (true) {
						end->getData().addValue (evidence);
						if (end->template isTerminal<expression :: direction :: LEFT>()) {
							break;
						} else {
							-- end;
						}
					}
					break;
				}
				substitution = substitution->getNext();
			}
			if (substitution == NULL) {
				typedef
					typename expression :: List<Allocator_>  :: Term_
					Term;
				typename Term :: Node_*
					node = new typename Term :: Node_ (Symbol :: getLambda());

				typename Term :: Iterator_
					begin (node);
				const Term*
					term_1 = new Term (begin);
				term_1->addSelf (true);

				typename Cell_ :: Iterator_ end = cell->addBranch
				(
					term_1->template castAway<typename Types_ :: Allocator_>(),
					evidence,
					true
				);
				++ end;
				end->setLambda();
				end->getData().addValue (evidence);
				const typename Cell_ :: Term_*
					term_2 = new typename Cell_ :: Term_ (end);
				term_2->addSelf (true);
			}
		}
	}

using manipulator :: endLine;

	template<class T, class A>
	void
	Unify<T, A> :: show (String& string) const
	{
		for (index :: Arity i = 0; i < matrix_.getSize(); ++ i) {
			const Symbol& variable = variables_.getReference (i);
			const Vector_* column = matrix_.getValue (i);
			string << "variable " << variable << " : " << endLine;
			string << "-----------------------------" << endLine;
			for (index :: Arity j = 0; j < column->getSize(); ++ j) {
				string << "hypothesis " << j << " : " << endLine;
				string << "********************" << endLine;
				const Cell_* cell = column->getValue (j);
				string << *cell << endLine;
				string << "********************" << endLine;
				string << endLine;
				string << endLine;
			}
			string << endLine;
		}
	}
	template<class T, class A>
	void
	Unify<T, A> :: show() const
	{
		String string (1024);
		show (string);
		std :: cout << string << std :: endl;
	}
}
}
}
}
}


